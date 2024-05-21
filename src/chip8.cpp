
#include "chip8.hpp"

using namespace CHIP8Demo;

Chip8Test::Chip8Test()
{
	std::shared_ptr<CHIP8::Display> display = std::make_shared<Display>();
	std::shared_ptr<CHIP8::Keypad> keypad = std::make_shared<Keyboard>();

	cpu = new CHIP8::CPU(keypad, display);

	cpu->GetDisplay()->Update();
}

void Chip8Test::loadRom(const std::string &filename)
{
	cpu->GetMemory()->LoadRomFile(filename);
}

void Chip8Test::playRom()
{
	bool running = true;
	auto lastTimerUpdate = std::chrono::steady_clock::now();
	const auto timerUpdateTime = std::chrono::microseconds(1'000'000 / 60);
	std::expected<bool, std::string> CycleStatus;
	while (true)
	{
		CycleStatus = cpu->RunCycle();

		if (!CycleStatus || CycleStatus.value() == false)
		{
			break;
		}

		cpu->GetKeypad()->UpdateKeys();

		if (cpu->GetDisplay()->IsUpdateRequired())
		{
			std::static_pointer_cast<Display>(cpu->GetDisplay())->setBeep(cpu->GetTimers()->GetBeeperState());
			
			cpu->GetDisplay()->Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(15));
		}

		if (std::chrono::steady_clock::now() - lastTimerUpdate > timerUpdateTime)
		{
			cpu->GetTimers()->DecrementTimers();
			lastTimerUpdate = std::chrono::steady_clock::now();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}

	std::cout << std::endl << "Emulation aborted! Reason:" << std::endl;
	if (!CycleStatus)
	{
		std::cout << "\x1A CPU Exception: \x1A " << CycleStatus.error() << std::endl;
	}
	else if (CycleStatus.value() == false)
	{
		std::cout << "\x1A " << cpu->GetInstructionError() << std::endl;
	}
	else
	{
		std::cout << "Unknown error" << std::endl;
	}
}