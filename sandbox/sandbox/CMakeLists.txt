cmake_minimum_required(VERSION 3.10)

SET(BINARY sandbox)

SET(INC_PATH ${CMAKE_CURRENT_SOURCE_DIR})
FILE(GLOB SRCS "src/*.cpp")

ADD_LIBRARY(${BINARY} STATIC ${SRCS} inc/child.h)

TARGET_INCLUDE_DIRECTORIES(${BINARY} PUBLIC
        ${INC_PATH}
        )

TARGET_LINK_LIBRARIES(
        ${BINARY} PUBLIC
        pthread
        rt
)

ADD_SUBDIRECTORY(tests)