file(GLOB_RECURSE PLATFORM_LINUX_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE PLATFORM_LINUX_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/linux/*.hpp"
)

add_library(browser_platform_linux STATIC
    ${PLATFORM_LINUX_SOURCES}
    ${PLATFORM_LINUX_HEADERS}
)

target_include_directories(browser_platform_linux
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
