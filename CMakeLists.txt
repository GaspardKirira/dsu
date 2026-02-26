cmake_minimum_required(VERSION 3.20)
project(dsu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(dsu INTERFACE)
add_library(dsu::dsu ALIAS dsu)

target_include_directories(dsu INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if (MSVC)
  target_compile_options(dsu INTERFACE /W4 /permissive-)
else()
  target_compile_options(dsu INTERFACE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
enable_testing()

add_executable(dsu_basic_test tests/test_basic.cpp)
target_link_libraries(dsu_basic_test PRIVATE dsu::dsu)
add_test(NAME dsu.basic COMMAND dsu_basic_test)
