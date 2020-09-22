cmake_minimum_required(VERSION 3.10)
set(This Sandbox)

project(${This}
    LANGUAGES CXX
    VERSION 0.0.1
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

set(Headers
    ${CMAKE_SOURCE_DIR}/inc/opt.h
)

set(Sources
    ${CMAKE_SOURCE_DIR}/src/opt.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)