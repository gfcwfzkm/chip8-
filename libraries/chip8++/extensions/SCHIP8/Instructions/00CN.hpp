// Scroll display N lines down
#ifndef SCHIP8_INSTRUCTIONS_00CN_HPP
#define SCHIP8_INSTRUCTIONS_00CN_HPP

#include "extensions/SCHIP8/display.hpp"
#include "base_system/Instructions/Instruction.hpp"

namespace CHIP8::SCHIP8::Instructions
{
	/**
	 * @brief Scroll display N lines down
	 * 
	 * This class represents the instruction to scroll the display N lines down.
	 */
	class I00CN :
		public CHIP8::Instructions::Instruction,
		public std::enable_shared_from_this<I00CN>
	{
		uint8_t LinesToScroll;
	public:
		/**
		 * @brief Execute the instruction to scroll the display N lines down
		 * 
		 * This function scrolls the display N lines down.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			auto display = std::dynamic_pointer_cast<SCHIP8Display>(cpu->GetDisplay());
			display->ScrollDown(LinesToScroll);
			return true;
		}

		/**
		 * @brief Returns the mnemonic for the scroll display N lines down instruction
		 * 
		 * @return std::string (DSV N) : Returns the mnemonic for the scroll display N lines down instruction
		 */
		std::string GetMnemonic() override {
			return std::format("DSV {}", LinesToScroll);
		}

		/**
		 * @brief Returns the description for the scroll display N lines down instruction
		 * 
		 * @return std::string (Scroll display N lines down) : Returns the description for the scroll display N lines down instruction
		 */
		std::string GetDescription() override {
			return std::format("Scroll the display by {} lines downwards", LinesToScroll);
		}

		/**
		 * @brief Returns the opcode and mask for the scroll display N lines down instruction
		 * 
		 * @return InstructionInfo_t (0x00C0, 0xFFF0) : Returns the opcode and mask for the scroll display N lines down instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x00C0, 0xFFF0};
		}

		/**
		 * @brief Update the instruction with the opcode
		 * 
		 * This function updates the instruction with the opcode.
		 * 
		 * @param opcode The opcode
		 * @return std::shared_ptr<CHIP8::Instructions::Instruction> : Returns the instruction
		 */
		std::shared_ptr<CHIP8::Instructions::Instruction> Update(uint16_t opcode) {
			LinesToScroll = opcode & 0x000F;
		}
	};
}

#endif /* SCHIP8_INSTRUCTIONS_00CN_HPP */