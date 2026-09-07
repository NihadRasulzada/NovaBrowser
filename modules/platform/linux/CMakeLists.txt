find_package(X11 REQUIRED)

add_library(platform_linux STATIC
    desktop/Application.cpp
    desktop/Window.cpp
)

target_link_libraries(platform_linux
    PUBLIC
        platform_abstraction
        X11::X11
)
