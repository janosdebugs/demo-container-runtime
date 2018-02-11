cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

find_path(SECCOMP NAMES "linux/seccomp.h")
if(NOT SECCOMP)
  message(FATAL_ERROR "Couldn't find linux/seccomp.h. Please install seccomp header files..")
endif()

add_executable(demo_seccomp bash-in-seccomp.cpp)
target_link_libraries(demo_seccomp seccomp)