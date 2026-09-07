file(GLOB_RECURSE BROWSER_UI_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE BROWSER_UI_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ui/*.hpp"
)

add_library(browser_ui STATIC
    ${BROWSER_UI_SOURCES}
    ${BROWSER_UI_HEADERS}
)

target_include_directories(browser_ui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(browser_ui
    PUBLIC
        framework_ui
)
