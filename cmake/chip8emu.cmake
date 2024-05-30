# CHIP-8 Emulator CMake configuration
# This file includes all CHIP-8 instructions
# This file is autogenerated by a python script
# Do not modify this file manually

## Define the path to the library
set(LIB_PATH libraries/chip8++)

include_directories(${CMAKE_SOURCE_DIR}/${LIB_PATH})

set(LIB_PATH_FILES
	${LIB_PATH}/base_system/memory.hpp 
	${LIB_PATH}/base_system/timers.hpp 
	${LIB_PATH}/base_system/keypad.hpp 
	${LIB_PATH}/base_system/display.hpp 
	${LIB_PATH}/base_system/quirks.hpp
	${LIB_PATH}/base_system/cpu.hpp ${LIB_PATH}/base_system/cpu.cpp
	${LIB_PATH}/base_system/Instructions/Instruction.hpp
	${LIB_PATH}/base_system/Instructions/Illegal.hpp
	${LIB_PATH}/base_system/Instructions/InstructionList.hpp
	${LIB_PATH}/base_system/Instructions/00E0.hpp
	${LIB_PATH}/base_system/Instructions/00EE.hpp
	${LIB_PATH}/base_system/Instructions/1NNN.hpp
	${LIB_PATH}/base_system/Instructions/2NNN.hpp
	${LIB_PATH}/base_system/Instructions/3XKK.hpp
	${LIB_PATH}/base_system/Instructions/4XKK.hpp
	${LIB_PATH}/base_system/Instructions/5XY0.hpp
	${LIB_PATH}/base_system/Instructions/6XKK.hpp
	${LIB_PATH}/base_system/Instructions/7XKK.hpp
	${LIB_PATH}/base_system/Instructions/8XY0.hpp
	${LIB_PATH}/base_system/Instructions/8XY1.hpp
	${LIB_PATH}/base_system/Instructions/8XY2.hpp
	${LIB_PATH}/base_system/Instructions/8XY3.hpp
	${LIB_PATH}/base_system/Instructions/8XY4.hpp
	${LIB_PATH}/base_system/Instructions/8XY5.hpp
	${LIB_PATH}/base_system/Instructions/8XY6.hpp
	${LIB_PATH}/base_system/Instructions/8XY7.hpp
	${LIB_PATH}/base_system/Instructions/8XYE.hpp
	${LIB_PATH}/base_system/Instructions/9XY0.hpp
	${LIB_PATH}/base_system/Instructions/ANNN.hpp
	${LIB_PATH}/base_system/Instructions/BNNN.hpp
	${LIB_PATH}/base_system/Instructions/CXKK.hpp
	${LIB_PATH}/base_system/Instructions/DXYN.hpp
	${LIB_PATH}/base_system/Instructions/EX9E.hpp
	${LIB_PATH}/base_system/Instructions/EXA1.hpp
	${LIB_PATH}/base_system/Instructions/FX07.hpp
	${LIB_PATH}/base_system/Instructions/FX0A.hpp
	${LIB_PATH}/base_system/Instructions/FX15.hpp
	${LIB_PATH}/base_system/Instructions/FX18.hpp
	${LIB_PATH}/base_system/Instructions/FX1E.hpp
	${LIB_PATH}/base_system/Instructions/FX29.hpp
	${LIB_PATH}/base_system/Instructions/FX33.hpp
	${LIB_PATH}/base_system/Instructions/FX55.hpp
	${LIB_PATH}/base_system/Instructions/FX65.hpp
	${LIB_PATH}/extensions/SCHIP8/display.hpp
	${LIB_PATH}/extensions/SCHIP8/Instructions/00CN.hpp
	${LIB_PATH}/extensions/SCHIP8/Instructions/00FB.hpp
	${LIB_PATH}/extensions/SCHIP8/Instructions/00FC.hpp
	${LIB_PATH}/extensions/SCHIP8/Instructions/00FD.hpp
	${LIB_PATH}/extensions/SCHIP8/Instructions/00FE.hpp
	${LIB_PATH}/extensions/SCHIP8/Instructions/00FF.hpp
	${LIB_PATH}/extensions/SCHIP8/Instructions/DXYN.hpp	
	${LIB_PATH}/extensions/SCHIP8/Instructions/FX30.hpp
	${LIB_PATH}/extensions/SCHIP8/Instructions/FX75.hpp
	${LIB_PATH}/extensions/SCHIP8/Instructions/FX85.hpp
)
add_library(chip8lib ${LIB_PATH_FILES})

