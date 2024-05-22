
#include "chip8.hpp"

using namespace CHIP8Demo;

Chip8Test::Chip8Test()
{
	display = std::make_shared<Display>();
	keyboard = std::make_shared<Keyboard>();

	cpu = new CHIP8::CPU(keyboard, display);

	cpu->GetDisplay()->Update();
}

void Chip8Test::loadRom(const std::string &filename)
{
	cpu->GetMemory()->LoadRomFile(filename);
}

void Chip8Test::playRom()
{
	auto lastTimerUpdate = std::chrono::steady_clock::now();
	const auto timerUpdateTime = std::chrono::microseconds(1'000'000 / 60);
	std::expected<bool, std::string> CycleStatus;

	while (true)
	{
		CycleStatus = cpu->RunCycle();

		if (!CycleStatus)
		{
			std::cout << std::endl << "Emulator aborted! Reason:" << std::endl;
			std::cout << CH8_ARROW " CPU Exception: " CH8_ARROW " " << CycleStatus.error() << std::endl;
			break;
		}
		else if (CycleStatus.value() == false)
		{
			auto lastInstruction = cpu->GetCurrentInstruction();
			std::cout << std::endl << "Emulator halted by instruction " <<
				lastInstruction->GetMnemonic() << " "  CH8_ARROW " " <<
				lastInstruction->GetAbortReason() << std::endl;

			if (lastInstruction->GetAbortReason().find("Quirk") != std::string::npos)
			{
				break;
			}

			std::cout << "Continue emulation (Keypad C) or abort (Keypad A)? ";

			enum Keyboard::Key key = Keyboard::Key::KEY_INVALID;
			while (key != Keyboard::Key::KEY_A && key != Keyboard::Key::KEY_C)
			{
				key = keyboard->WaitForKeyPress();
			}

			std::cout << std::format("{}",(key == Keyboard::Key::KEY_A) ? "A" : "C");

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

		keyboard->UpdateKeys();

		if (cpu->GetDisplay()->IsUpdateRequired())
		{
			display->Update(cpu->GetTimers()->GetBeeperState());
			std::this_thread::sleep_for(std::chrono::milliseconds(15));
		}

		if (std::chrono::steady_clock::now() - lastTimerUpdate > timerUpdateTime)
		{
			cpu->GetTimers()->DecrementTimers();
			lastTimerUpdate = std::chrono::steady_clock::now();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}
}