#include <iostream>
#include "chip8.hpp"

int main(int argc, char *argv[]) 
{
	// Check if a ROM file path was provided
	if (argc > 1)
	{
		CHIP8Demo::Chip8Test emu;

		// Load the ROM file
		auto result = emu.loadRom(argv[1]);

		// Check if the ROM file was loaded successfully
		if (result.has_value())
		{
			std::cout << "Error: " << result.value() << std::endl;
			return 1;
		}
		else 
		{
			// Clear the screen
			std::cout << "\x1B[2J\x1B[H";
			// Play the ROM file
			emu.playRom();
			return 0;
		}
	}
	else
	{
		// Print usage information
		std::cout << "Usage: " << argv[0] << " <path to rom file>" << std::endl;
	}
	return 0;
}
