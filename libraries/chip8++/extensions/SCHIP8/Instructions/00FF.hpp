// Enable extended screen mode for full-screen graphics.
#ifndef SCHIP8_INSTRUCTIONS_00FF_HPP
#define SCHIP8_INSTRUCTIONS_00FF_HPP

#include "extensions/SCHIP8/display.hpp"
#include "base_system/Instructions/Instruction.hpp"

namespace CHIP8::SCHIP8::Instructions
{
	class I00FF :
		public CHIP8::Instructions::Instruction,
		public std::enable_shared_from_this<I00FF>
	{
	public:
		bool Execute(CHIP8::CPU *cpu) override {
			auto display = std::dynamic_pointer_cast<SCHIP8Display>(cpu->GetDisplay());
			display->SetHighRes(true);
			return true;
		}

		std::string GetMnemonic() override {
			return "HRS";
		}

		std::string GetDescription() override {
			return "Enable extended screen mode for full-screen graphics";
		}

		InstructionInfo_t GetInfo() override {
			return {0x00FF, 0xFFFF};
		}

		std::shared_ptr<CHIP8::Instructions::Instruction> Update(uint16_t opcode) {
			(void)opcode;
		}
	};
}


#endif /* SCHIP8_INSTRUCTIONS_00FF_HPP */