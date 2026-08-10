file(GLOB_RECURSE URL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE URL_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/network/*.hpp"
)

add_library(browser_network STATIC
    ${URL_SOURCES}
    ${URL_HEADERS} "src/DnsResolver.cpp" "src/Connection.cpp" "src/NetworkRuntime.cpp")

target_include_directories(browser_network PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (WIN32)
    target_link_libraries(browser_network PRIVATE ws2_32)
endif()