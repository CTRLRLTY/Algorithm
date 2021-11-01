cmake_minimum_required(VERSION 3.10)

project(Main)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Main PreemptiveSJF.cxx)
