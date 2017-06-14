cmake_minimum_required(VERSION 3.7)
project(uml_viewer_01)

set(CMAKE_C_STANDARD 99)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lobjc -framework AppKit -framework Cocoa -framework OpenGL")

set(SOURCE_FILES main.c objc_helpers.h)
add_executable(uml_viewer_01 ${SOURCE_FILES})
