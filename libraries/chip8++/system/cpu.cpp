#include "cpu.hpp"
#include "InstructionDecoder.hpp"
#include "Instructions/Illegal.hpp"
#include "Instructions/InstructionList.hpp"
#include <memory>

using namespace CHIP8;

CPU::CPU(std::shared_ptr<Keypad> keypad, std::shared_ptr<Display> display, std::shared_ptr<InstructionDecoder> decoder,
	std::shared_ptr<Memory> memory, std::shared_ptr<Timers> timers)
 : memory(memory), keypad(keypad), display(display), timers(timers)
{
	if (decoder == nullptr)
	{
		decoder = std::make_shared<InstructionDecoder>(std::make_shared<Instructions::IllegalInstruction>());
		for (int i = 0; i < Instructions::InstructionList::INSTRUCTION_COUNT; i++)
		{
			std::shared_ptr<Instructions::Instruction> instr = Instructions::InstructionList::GetInstruction(i);
			decoder->RegisterInstruction(instr);
		}
	}

	this->decoder = decoder;
	Reset();
}

void CPU::Reset(bool fullSystemReset)
{
	V.fill({0});
	Stack.fill({0});
	SP = 0;
	I = 0;
	PC = 0x200;

	if (fullSystemReset)
	{
		memory->Reset();
		display->Clear();
	}
}

std::expected<bool, std::string> CPU::RunCycle()
{
	bool successfulInstruction;
	auto opcode = memory->GetWord(PC);

	if (!opcode)
	{
		return std::unexpected(std::format("CHIP8: Memory access error!\x1A {}", opcode.error()));
	}

	std::shared_ptr<Instructions::Instruction> instruction = decoder->DecodeInstruction(opcode.value());

	if (instruction == nullptr)
	{
		return std::unexpected(std::format("CHIP8: Nullptr instruction at address 0x{:04X}", PC));
	}
	
	PC += 2;
	successfulInstruction = instruction->Execute(this);
	if (!successfulInstruction)	InstructionError = instruction->GetAbortReason();
	return successfulInstruction;
}

void CPU::SetRegister(uint8_t reg, uint8_t value)
{
	V.at(reg) = value;
}

uint8_t CPU::GetRegister(uint8_t reg)
{
	return V.at(reg);
}

void CPU::SetIndex(uint16_t value)
{
	I = value;
}

uint16_t CPU::GetIndex()
{
	return I;
}

void CPU::SetPC(uint16_t value)
{
	PC = value;
}

uint16_t CPU::GetPC()
{
	return PC;
}

void CPU::PushStack(uint16_t value)
{
	if (SP >= STACKDEPTH) {
		throw std::overflow_error("CHIP8: Stack overflow");
	}
	Stack.at(SP++) = value;
}

uint16_t CPU::PopStack()
{
	if (SP == 0) {
		throw std::underflow_error("CHIP8: Stack underflow");
	}
	return Stack.at(--SP);
}

std::shared_ptr<Display> CPU::GetDisplay()
{
	return display;
}

std::shared_ptr<Keypad> CPU::GetKeypad()
{
	return keypad;
}

std::shared_ptr<Memory> CPU::GetMemory()
{
	return memory;
}

std::shared_ptr<InstructionDecoder> CPU::GetDecoder()
{
	return decoder;
}

Quirks &CPU::GetQuirks()
{
	return quirks;
}

const std::string &CPU::GetInstructionError()
{
	return InstructionError;
}

std::shared_ptr<Timers> CPU::GetTimers()
{
	return timers;
}