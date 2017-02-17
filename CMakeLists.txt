cmake_minimum_required(VERSION 3.5)
project(test1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lobjc -framework AppKit -framework Cocoa")

set(SOURCE_FILES
    main.c)

add_executable(test1 ${SOURCE_FILES})