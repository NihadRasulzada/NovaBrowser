file(GLOB_RECURSE URL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE URL_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/rendering/*.hpp"
)

add_library(browser_rendering STATIC
    ${URL_SOURCES}
    ${URL_HEADERS})

target_include_directories(browser_rendering PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
