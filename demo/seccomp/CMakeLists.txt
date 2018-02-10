cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)

find_path(SECCOMP NAMES "linux/seccomp.h")
if(NOT SECCOMP)
  message(FATAL_ERROR "Couldn't find linux/seccomp.h. Please install seccomp header files..")
endif()

add_executable(demo_seccomp bash-in-seccomp.cpp ../../runtime/plugin/SeparationPlugin.cpp ../../runtime/plugin/SeparationPlugin.h ../../runtime/runtime.cpp ../../runtime/plugin/PidNamespaceSeparationPlugin.cpp ../../runtime/plugin/PidNamespaceSeparationPlugin.h ../../runtime/plugin/SeparationFailedException.cpp ../../runtime/plugin/SeparationFailedException.h ../../runtime/plugin/UtsNamespaceSeparationPlugin.cpp ../../runtime/plugin/UtsNamespaceSeparationPlugin.h ../../runtime/plugin/NetNamespaceSeparationPlugin.cpp ../../runtime/plugin/NetNamespaceSeparationPlugin.h ../../runtime/plugin/SeparationProcessor.cpp ../../runtime/plugin/SeparationProcessor.h)
target_link_libraries(demo_seccomp seccomp)