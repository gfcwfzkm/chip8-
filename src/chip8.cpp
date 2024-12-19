
#include "chip8.hpp"

using namespace CHIP8Demo;

Chip8Test::Chip8Test()
 : display(std::make_shared<Display>()), keyboard(std::make_shared<Keyboard>()), cpu(CHIP8::CPU(keyboard, display))
{
	//display = std::make_shared<Display>();		// Create our inherited Display object
	//keyboard = std::make_shared<Keyboard>();	// Create our inherited Keyboard object

	//// Create our CHIP8 CPU object with the keyboard and display objects
	//cpu = new CHIP8::CPU(keyboard, display);	

	// Clear the screen
	cpu.GetDisplay()->Update();
}

std::expected<void, std::string> Chip8Test::loadRom(const std::string &filename)
{
	// Load the ROM file
	auto romResult = cpu.GetMemory()->LoadRomFile(filename);
	if (!romResult)
	{
		// Return an error message if the ROM file could not be loaded
		return std::unexpected("Error loading ROM file: " + romResult.error());
	}
	// Return success
	return std::expected<void, std::string>();
}

void Chip8Test::playRom()
{
	// Timer update time constant
	const auto timerUpdateTime = std::chrono::microseconds(1'000'000 / 60);
	// Last timer update time
	auto lastTimerUpdate = std::chrono::steady_clock::now();
	// Cycle status containing the result of the cycle execution
	std::expected<bool, std::string> CycleStatus;

	// Run the emulator
	while (true)
	{
		// Execute a cycle
		CycleStatus = cpu.RunCycle();

		// Check if the cycle was successful
		if (!CycleStatus)
		{
			// Print the error message and break the loop
			// as a CPU exception occurred
			std::cout << std::endl << "Emulator aborted! Reason:\n" << CH8_ARROW
				" CPU Exception: " CH8_ARROW " " << CycleStatus.error() << std::endl;
			break;
		}
		else if (CycleStatus.value() == false)
		{
			// If the bool is false, an instruction returned an error
			// Print the error message
			auto lastInstruction = cpu.GetCurrentInstruction();
			std::cout << std::endl << "Emulator halted by instruction " <<
				lastInstruction->GetMnemonic() << " "  CH8_ARROW " " <<
				lastInstruction->GetAbortReason() << std::endl;

			// Check if the error was caused by the loop quirk - that one is allowed to 
			// directly abort the emulation
			if (lastInstruction->GetAbortReason().find("Quirk") != std::string::npos)
			{
				break;
			}

			// Ask the user if they want to continue or abort the emulation
			std::cout << "Continue emulation (Keypad C) or abort (Keypad A)? ";

			enum Keyboard::Key key = Keyboard::Key::KEY_INVALID;

			// Wait for the user to press either A or C
			while (key != Keyboard::Key::KEY_A && key != Keyboard::Key::KEY_C)
			{
				key = keyboard->WaitForKeyPress();
			}

			// Print the key pressed
			std::cout << std::format("{}",(key == Keyboard::Key::KEY_A) ? "A" : "C");

			// Check if the user wants to abort the emulation
			if (key == Keyboard::Key::KEY_A)
			{
				break;
			}
			else if (key == Keyboard::Key::KEY_C)
			{
				// Erase the the current line, move one line up, erase it as well,
				// move once more one line up
				std::cout << "\33[2K \33[A \33[2K \33[A";
				// We want to be at the same position as if a display refresh
				// just happend
			}
		}

		// Update the keyboard by reading in key presses
		keyboard->UpdateKeys();

		// Check if the display needs to be updated
		if (cpu.GetDisplay()->IsUpdateRequired())
		{
			// Update the display
			display->Update(cpu.GetTimers()->GetBeeperState());
			std::this_thread::sleep_for(std::chrono::milliseconds(15));
		}

		// Update the timers
		if (std::chrono::steady_clock::now() - lastTimerUpdate > timerUpdateTime)
		{
			cpu.GetTimers()->DecrementTimers();
			lastTimerUpdate = std::chrono::steady_clock::now();
		}

		// Sleep for a short time to prevent the CPU from running too fast
		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}
}