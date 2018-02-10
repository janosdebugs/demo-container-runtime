cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)

find_path(SECCOMP NAMES "linux/seccomp.h")
if(NOT SECCOMP)
  message(FATAL_ERROR "Couldn't find linux/seccomp.h. Please install seccomp header files..")
endif()

add_executable(demo_runtime runtime.cpp plugin/SeparationPlugin.cpp plugin/SeparationPlugin.h)
target_link_libraries(demo_runtime seccomp)
