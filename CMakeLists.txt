cmake_minimum_required(VERSION 3.28)

project(NovaBrowser)

set(CMAKE_CXX_STANDARD 23)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(third_party/googletest)
add_subdirectory(modules)
add_subdirectory(app)