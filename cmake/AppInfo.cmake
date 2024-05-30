##
##  AppInfo.cmake
##

## Define the used C and C++ standards for the whole project
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

## Define application/project name, app version and icon
set(APP_NAME "Chip8pp")
set(APP_VERSION 0.0.1)

# Compiler options - enable warnings + extra warnings
add_compile_options(-Wall)

# If we're using Gnu, use -Wextra (done so we can easily use MSVC without it complaining)
if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_C_COMPILER_ID MATCHES "GNU"))
    add_compile_options(-Wextra)
endif()

## Source and header files of our project
set(SOURCE_FILES
    src/mainApp.cpp
    src/ch8_platform_specific.h
	src/chip8.cpp src/chip8.hpp 
)
