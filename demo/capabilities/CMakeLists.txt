cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

find_path(LIBCAP NAMES "cap-ng.h")
if(NOT LIBCAP)
  message(FATAL_ERROR "Couldn't find cap-ng.h. Please install libcap-ng header files.")
endif()

add_executable(demo_cap bash-with-no-caps.cpp)
target_link_libraries(demo_cap cap-ng)