BUILD_DIR := build
CMAKE     := cmake
GENERATOR := "Unix Makefiles"
BUILD_TYPE ?= Debug

.PHONY: all configure build run clean rebuild test compiledb

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

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

clean:
	rm -rf $(BUILD_DIR) compile_commands.json

rebuild: clean build

compiledb: configure
	@echo "compile_commands.json regenerated and symlinked"
