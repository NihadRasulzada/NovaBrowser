file(GLOB_RECURSE FRAMEWORK_UI_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE FRAMEWORK_UI_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ui/*.hpp"
)

add_library(framework_ui STATIC
    ${FRAMEWORK_UI_SOURCES}
    ${FRAMEWORK_UI_HEADERS}
)

target_include_directories(framework_ui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
