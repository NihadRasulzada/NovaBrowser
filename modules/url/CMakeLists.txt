file(GLOB_RECURSE URL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE URL_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/url/*.hpp"
)

add_library(browser_url STATIC
    ${URL_SOURCES}
    ${URL_HEADERS}
)

target_include_directories(browser_url PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)