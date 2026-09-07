add_library(platform_abstraction INTERFACE)

target_include_directories(platform_abstraction
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
