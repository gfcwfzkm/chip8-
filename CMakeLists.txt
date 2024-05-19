##
##  CMakeLists.txt
##  Minimal C/C++ CMAKE Project
##
##  Created by Pascal Gesell on 21.02.2024
##

cmake_minimum_required(VERSION 3.22)

## Allow submodules to be used, which are stored in the cmake folder
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

## All of the Application specific information is stored in the AppInfo.cmake file
include(AppInfo)
include(chip8emu)

## Make sure no spaces are in the project name
string(REPLACE " " "_" PROJ_NAME ${APP_NAME})
## Set the project name
project(${PROJ_NAME})
## Set the Application name
set(TARGET_NAME ${PROJ_NAME})

## Include all of our directory paths
set(CMAKE_INCLUDE_CURRENT_DIR ON)

## Set the source files we want to build
add_executable(${TARGET_NAME} ${SOURCE_FILES})

## Linking the chip 8 library
target_link_libraries(${TARGET_NAME} chip8lib)

## Set the build directory
set(BUILD_DIR ${PROJECT_SOURCE_DIR}/build)