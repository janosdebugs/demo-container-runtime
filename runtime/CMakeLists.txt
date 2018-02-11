cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

find_path(SECCOMP NAMES "linux/seccomp.h")
if(NOT SECCOMP)
    message(FATAL_ERROR "Couldn't find linux/seccomp.h. Please install seccomp header files..")
endif()

file(GLOB demo_runtime_src
    "*.h"
    "*.cpp"
    "plugin/*.h"
    "plugin/*.cpp"
)
add_executable(demo_runtime ${demo_runtime_src})
target_link_libraries(demo_runtime seccomp)
