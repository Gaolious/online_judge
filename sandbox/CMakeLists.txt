cmake_minimum_required(VERSION 3.10)

SET(CMAKE_BUILD_TYPE DEBUG)

##############################################################
# project
##############################################################
project(sb CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ENABLE_TESTING()

ADD_SUBDIRECTORY(sandbox)

ADD_EXECUTABLE(${PROJECT_NAME} src/main.cpp)
TARGET_LINK_LIBRARIES(
        ${PROJECT_NAME} PUBLIC
        sandbox
)

##############################################################
# for testing
##############################################################
ADD_EXECUTABLE(sample_mem sample/mem.cpp)
ADD_EXECUTABLE(sample_sleep sample/sleep.cpp)
ADD_EXECUTABLE(sample_sig_fault sample/signal_seg_fault.cpp)
ADD_EXECUTABLE(sample_div_0 sample/signal_div0.cpp)
