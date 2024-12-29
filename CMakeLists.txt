##
##  CMakeLists.txt
##

cmake_minimum_required(VERSION 3.22)

project("Chip8 C++ Library" VERSION 1.0)

## SCHIP Support is toggable!
option(USE_SCHIP "Add experimental SCHIP8 implementation" OFF)
option(BUILD_CLI "Build the CLI application" OFF)

## Compiler options - enable warnings + extra warnings
add_compile_options(-Wall)

## If we're using Gnu, use -Wextra (done so we can easily use MSVC without it complaining)
if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_C_COMPILER_ID MATCHES "GNU"))
    add_compile_options(-Wextra)
endif()



## Using relative modern C++ features, so make them a requirement
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

## Locations of the files
set(BASE_CHIP8PP_PATH ${PROJECT_SOURCE_DIR}/lib/chip8++/base_system)
set(EXT_SCHIP8_PATH ${PROJECT_SOURCE_DIR}/lib/chip8++/extensions/SCHIP8)
set(DEMO_PATH ${PROJECT_SOURCE_DIR}/demo)

## Add the corresponding folder to be included
include_directories(${BASE_CHIP8PP_PATH})
if (USE_SCHIP)
    include_directories(${EXT_SCHIP8_PATH})
endif()

## Set the source files for the demo application
#file(GLOB DEMO_SOURCES "${DEMO_PATH}/*.cpp")
#file(GLOB DEMO_HEADERS "${DEMO_PATH}/*.hpp")

## Set the source files for the library
file(GLOB BASE_HEADERS "${BASE_CHIP8PP_PATH}/*.hpp")
file(GLOB BASE_SOURCES "${BASE_CHIP8PP_PATH}/*.cpp")

set(HEADERS ${BASE_HEADERS}) #${DEMO_HEADERS})
set(SOURCES ${BASE_SOURCES}) #${DEMO_SOURCES})

if (USE_SCHIP)
	file(GLOB SCHIP8_HEADERS "${EXT_SCHIP8_PATH}/*.hpp")
	file(GLOB SCHIP8_SOURCES "${EXT_SCHIP8_PATH}/*.cpp")
	set(HEADERS ${HEADERS} ${SCHIP8_HEADERS})
	set(SOURCES ${SOURCES} ${SCHIP8_SOURCES})
endif()


## We make a application executable
#add_executable(chip8pp ${SOURCES} ${HEADERS})
#if(WIN32)
#	if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_C_COMPILER_ID MATCHES "GNU"))
#		set(BUILD_SHARED_LIBS OFF)
#		set_target_properties(chip8pp PROPERTIES LINK_SEARCH_START_STATIC 1)
#		set_target_properties(chip8pp PROPERTIES LINK_SEARCH_END_STATIC 1)
#		#set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#		#Static Libs
#		#Set Linker flags
#		target_link_options(chip8pp PRIVATE -static-libgcc -static-libstdc++ -static -fno-rtti)
#		message("Hi")
#	endif()
#endif()


## Set the source files we want to build
add_library(chip8pp SHARED)
target_sources(chip8pp
	PRIVATE
		${SOURCES}
)
if (USE_SCHIP)
target_include_directories(chip8pp
	PUBLIC
		${BASE_CHIP8PP_PATH}
		${EXT_SCHIP8_PATH}
		$<BUILD_INTERFACE:${BASE_CHIP8PP_PATH}>
		$<BUILD_INTERFACE:${EXT_SCHIP8_PATH}>
 		$<INSTALL_INTERFACE:include>
)
else()
target_include_directories(chip8pp
	PUBLIC
		${BASE_CHIP8PP_PATH}
		$<BUILD_INTERFACE:${BASE_CHIP8PP_PATH}>
 		$<INSTALL_INTERFACE:include>
)
endif()

add_library(chip8ppStatic STATIC)
target_sources(chip8ppStatic
	PRIVATE
		${SOURCES}
)
if (USE_SCHIP)
target_include_directories(chip8ppStatic
	PUBLIC
		${BASE_CHIP8PP_PATH}
		${EXT_SCHIP8_PATH}
		$<BUILD_INTERFACE:${BASE_CHIP8PP_PATH}>
		$<BUILD_INTERFACE:${EXT_SCHIP8_PATH}>
 		$<INSTALL_INTERFACE:include>
)
else()
target_include_directories(chip8ppStatic
	PUBLIC
		${BASE_CHIP8PP_PATH}
		$<BUILD_INTERFACE:${BASE_CHIP8PP_PATH}>
 		$<INSTALL_INTERFACE:include>
)
endif()

## Optionally build the cli application
if (BUILD_CLI)
	add_subdirectory(${PROJECT_SOURCE_DIR}/demo)
endif()