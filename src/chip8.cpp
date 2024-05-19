
#include "chip8.hpp"

using namespace CHIP8Demo;

Chip8Test::Chip8Test()
{
	std::shared_ptr<CHIP8::Display> display = std::make_shared<Display>();
	std::shared_ptr<CHIP8::Keypad> keypad = std::make_shared<Keyboard>();

	cpu = new CHIP8::CPU(keypad, display);

	cpu->getDisplay()->Update();
}

void Chip8Test::loadRom(const std::string &filename)
{
	cpu->getMemory()->LoadRomFile(filename);
}

void Chip8Test::playRom()
{
	bool running = true;
	auto lastTimerUpdate = std::chrono::steady_clock::now();
	const auto timerUpdateTime = std::chrono::microseconds(1'000'000 / 60);

	auto perfStart = std::chrono::steady_clock::now();
	while (running)
	{
		running = cpu->RunCycle();

		cpu->getKeypad()->updateKeys();

		if (cpu->getDisplay()->GetUpdateRequired())
		{
			std::static_pointer_cast<Display>(cpu->getDisplay())->setBeep(cpu->getTimers()->getBeeperState());
			
			cpu->getDisplay()->Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(15));
		}

		if (std::chrono::steady_clock::now() - lastTimerUpdate > timerUpdateTime)
		{
			cpu->getTimers()->decrementTimers();
			lastTimerUpdate = std::chrono::steady_clock::now();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}
	auto perfEnd = std::chrono::steady_clock::now();

	std::cout << std::endl << "Emulation aborted! Reason:" << std::endl << "\x1A " << cpu->GetInstructionError() << std::endl;
	std::cout << "Emulation took " << std::chrono::duration_cast<std::chrono::microseconds>(perfEnd - perfStart).count() << "\xE6s" << std::endl;
}