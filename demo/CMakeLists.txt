cmake_minimum_required(VERSION 3.10)

project(chip8pp_demo)

## Set the source files for the demo application
file(GLOB DEMO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB DEMO_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

## Add the executable for the demo application
add_executable(chip8pp_demo ${DEMO_SOURCES} ${DEMO_HEADERS})

## Link the demo application with the chip8pp library
target_link_libraries(chip8pp_demo chip8ppStatic -static)