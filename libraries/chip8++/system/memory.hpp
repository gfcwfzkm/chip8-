#ifndef _CHIP8_MEMORY_HPP_
#define _CHIP8_MEMORY_HPP_

#include <cstdint>
#include <array>
#include <string>
#include <fstream>
#include <ios>

namespace CHIP8
{
	/**
	 * @brief Memory
	 * 
	 * This class represents the memory of the CHIP-8 system.
	 */
	class Memory
	{
		/** @brief Memory Size
		 * 
		 * This constant represents the size of the memory.
		 */
		static constexpr size_t MEMORY_SIZE				= 4096;

		/** @brief Default ROM start address
		 * 
		 * This constant represents the start address of the default ROM.
		 */
		static constexpr size_t DEFAULT_ROM_START		= 0x200;

		/** @brief Default font start address
		 * 
		 * This constant represents the start address of the default CHIP-8 font.
		 */
		static constexpr size_t DEFAULT_FONT_START		= 0x50;

		/** @brief Default CHIP-8 font
		 * 
		 * This array stores the default CHIP-8 font.
		 */
		static constexpr std::array<uint8_t, 80> DEFAULT_FONT = 
		{
			0xF0, 0x90, 0x90, 0x90, 0xF0,	// 0
			0x20, 0x60, 0x20, 0x20, 0x70,	// 1
			0xF0, 0x10, 0xF0, 0x80, 0xF0,	// 2
			0xF0, 0x10, 0xF0, 0x10, 0xF0,	// 3
			0x90, 0x90, 0xF0, 0x10, 0x10,	// 4
			0xF0, 0x80, 0xF0, 0x10, 0xF0,	// 5
			0xF0, 0x80, 0xF0, 0x90, 0xF0,	// 6
			0xF0, 0x10, 0x20, 0x40, 0x40,	// 7
			0xF0, 0x90, 0xF0, 0x90, 0xF0,	// 8
			0xF0, 0x90, 0xF0, 0x10, 0xF0,	// 9
			0xF0, 0x90, 0xF0, 0x90, 0x90,	// A
			0xE0, 0x90, 0xE0, 0x90, 0xE0,	// B
			0xF0, 0x80, 0x80, 0x80, 0xF0,	// C
			0xE0, 0x90, 0x90, 0x90, 0xE0,	// D
			0xF0, 0x80, 0xF0, 0x80, 0xF0,	// E
			0xF0, 0x80, 0xF0, 0x80, 0x80 	// F
		};

		/** @brief Memory
		 * 
		 * This array stores the memory of the CHIP-8 system.
		 */
		std::array<uint8_t, MEMORY_SIZE> memory;
		
		/**
		 * @brief Load the default font into memory
		 * 
		 * This function loads the default font into memory.
		 */
		void LoadFont() {
			std::copy(DEFAULT_FONT.begin(), DEFAULT_FONT.end(), 
				std::next(memory.begin(), DEFAULT_FONT_START));
		};
	public:
		/**
		 * @brief Construct a new Memory object
		 * 
		 * This constructor initializes the memory with the default font.
		 */
		Memory() : memory({0}) {
			LoadFont();
		};

		/**
		 * @brief Reset the memory
		 * 
		 * This function resets the memory to its initial state.
		 */
		void Reset() {
			memory.fill({0});
			LoadFont();
		};

		/**
		 * @brief Set a byte in memory
		 * 
		 * This function sets a byte in memory at the specified address.
		 * 
		 * @param address : Address to set the byte
		 * @param value : Value to set
		 */
		uint8_t GetByte(uint16_t address) {
			if (address > MEMORY_SIZE - 1)
			{
				throw std::out_of_range("Memory out of bounds");
			}

			return memory.at(address & (MEMORY_SIZE - 1));
		};

		/**
		 * @brief Set a byte in memory
		 * 
		 * This function sets a byte in memory at the specified address.
		 * 
		 * @param address : Address to set the byte
		 * @param value : Value to set
		 */
		void SetByte(uint16_t address, uint8_t value) {
			if (address > MEMORY_SIZE - 1)
			{
				throw std::out_of_range("Memory out of bounds");
			}

			memory.at(address & (MEMORY_SIZE - 1)) = value;
		};

		/**
		 * @brief Set a word in memory
		 * 
		 * This function sets a word in memory at the specified address.
		 * 
		 * @param address : Address to set the word
		 * @param value : Value to set
		 */
		uint16_t GetWord(uint16_t address) {
			if (address > MEMORY_SIZE - 2)
			{
				throw std::out_of_range("Memory out of bounds");
			}
			
			return (memory.at(address & (MEMORY_SIZE - 1)) << 8) | memory.at((address + 1) & (MEMORY_SIZE - 1));
		};

		/**
		 * @brief Load a ROM file into memory
		 * 
		 * This function loads a ROM file into memory starting at the default ROM start address.
		 * 
		 * @param romPath : Path to the ROM file
		 */
		void LoadRomFile(const std::string &romPath) {
			std::ifstream file(romPath, std::ios::binary | std::ios::ate);
			if (file.is_open())
			{
				std::ifstream::pos_type pos = file.tellg();
				if (size_t(pos) <= MEMORY_SIZE - DEFAULT_ROM_START)
				{
					file.seekg(0, std::ios::beg);
					file.read(reinterpret_cast<char*>(&memory[DEFAULT_ROM_START]), pos);
				}
				else
				{
					throw std::runtime_error("ROM too large for memory");
				}
			}
			else
			{
				throw std::runtime_error("Failed to open ROM file");
			}
			file.close();
		};

		/**
		 * @brief Get the starting address of the font
		 * 
		 * This function returns the starting address of the font.
		 * 
		 * @return uint16_t : Starting address of the font 
		 */
		uint16_t GetFontStart(void) {
			return DEFAULT_FONT_START;
		};
	};
}

#endif /* _MEMORY_HPP_ */