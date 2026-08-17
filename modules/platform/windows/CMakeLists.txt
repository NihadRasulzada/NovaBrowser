file(GLOB_RECURSE URL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE URL_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/windows/*.hpp"
)

add_library(browser_platform_windows STATIC
    ${URL_SOURCES}
    ${URL_HEADERS})

target_include_directories(browser_platform_windows PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)