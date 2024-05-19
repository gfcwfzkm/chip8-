#include <iostream>
#include "chip8.hpp"

int main(int argc, char *argv[]) 
{
	std::cout << "\x1B[2J\x1B[H";
	if (argc > 1)
	{
		CHIP8Demo::Chip8Test emu(argv[1]);
		try
		{
			emu.playRom();
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error playing ROM: " << e.what() << std::endl;
			return 1;
		}
		catch(...)
		{
			std::cerr << "Unknown error playing ROM" << std::endl;
			return 1;
		}
		return 0;
	}
	else
	{
		std::cout << "Usage: " << argv[0] << " <rom file>" << std::endl;
	}
	
	// suppress unused variable warning
	(void)argv;
	(void)argc;

	return 0;
}
