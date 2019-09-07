# This is only here for code-completion in the CLion IDE.
cmake_minimum_required(VERSION 3.14)
project(nvman C)

include_directories($ENV{VBCC}/NDK39/Include/include_h)
include_directories($ENV{VBCC}/targets/m68k-amigaos/include)

set(CMAKE_C_STANDARD 99)
add_executable(nvman nvman.c)
