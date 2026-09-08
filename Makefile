BUILD_DIR := build
CMAKE     := cmake
GENERATOR := "Unix Makefiles"
BUILD_TYPE ?= Debug

.PHONY: all configure build run hot-run monitor clean rebuild test compiledb

all: build

configure:
	$(CMAKE) -S . -B $(BUILD_DIR) -G $(GENERATOR) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	@rm -f compile_commands.json
	@ln -s $(BUILD_DIR)/compile_commands.json compile_commands.json

build: configure
	$(CMAKE) --build $(BUILD_DIR) -j$(shell nproc)

run: build
	./$(BUILD_DIR)/app/browser_app

hot-run: build
	@echo "Starting NovaBrowser hot-run..."
	@while true; do \
		./$(BUILD_DIR)/app/browser_app & \
		PID=$$!; \
		echo "NovaBrowser started (PID: $$PID)"; \
		inotifywait -r -e modify,create,delete,move \
			modules app CMakeLists.txt; \
		echo "Change detected. Restarting..."; \
		kill $$PID 2>/dev/null || true; \
		wait $$PID 2>/dev/null || true; \
		$(CMAKE) --build $(BUILD_DIR) -j$(shell nproc); \
	done

monitor: build
	@echo "Starting NovaBrowser..."
	@./$(BUILD_DIR)/app/browser_app & \
	PID=$$!; \
	echo "NovaBrowser started (PID: $$PID)"; \
	echo ""; \
	echo "=============================================="; \
	echo "              NovaBrowser Monitor"; \
	echo "=============================================="; \
	echo ""; \
	printf "%-8s %-8s %-8s %-12s %-12s %-12s\n" \
		"PID" "CPU" "MEM" "RAM" "VSZ" "UPTIME"; \
	echo "------------------------------------------------------------"; \
	trap 'kill $$PID 2>/dev/null || true; exit 0' INT TERM; \
	while kill -0 $$PID 2>/dev/null; do \
		ps -p $$PID -o pid=,pcpu=,pmem=,rss=,vsz=,etime= | \
		awk '{printf "%-8s %-8s %-8s %-12.2f MB %-10.2f MB %-12s\n", \
		$$1, $$2"%", $$3"%", $$4/1024, $$5/1024, $$6}'; \
		sleep 1; \
	done; \
	echo ""; \
	echo "NovaBrowser stopped."

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

clean:
	rm -rf $(BUILD_DIR) compile_commands.json

rebuild: clean build

compiledb: configure
	@echo "compile_commands.json regenerated and symlinked"
