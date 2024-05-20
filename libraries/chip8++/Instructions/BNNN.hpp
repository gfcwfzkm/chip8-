#ifndef _CHIP8_INSTRUCTIONS_BNNN_HPP_
#define _CHIP8_INSTRUCTIONS_BNNN_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Jump to address NNN + V0
	 * 
	 * This class represents the instruction to jump to address NNN + V0.
	 */
	class IBNNN : 
		public Instruction,
		public std::enable_shared_from_this<IBNNN>
	{
		uint8_t registerX;
		uint16_t address;
	public:
		/**
		 * @brief Execute the instruction to jump to address NNN + V0
		 * 
		 * This function jumps to the address NNN + V0.
		 * 
		 * If the quirk-flag Jump is set, the address is calculated as NNN + VX,
		 * otherwise the address is calculated as NNN + V0.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			if (cpu->GetQuirks().Jump)
			{
				cpu->SetPC(address + cpu->GetRegister(registerX));
			}
			else
			{
				cpu->SetPC(address + cpu->GetRegister(0));
			}
			
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the jump to address NNN + V0 instruction
		 * 
		 * @return std::string (JP V0, NNN) : Returns the mnemonic for the jump to address NNN + V0 instruction
		 */
		std::string GetMnemonic() override {
			return std::format("JP V0, {:#X}", address);
		}

		/**
		 * @brief Returns the description for the jump to address NNN + V0 instruction
		 * 
		 * @return std::string (Jump to address NNN + V0) : Returns the description for the jump to address NNN + V0 instruction
		 */
		std::string GetDescription() override {
			return std::format("Jump to address {:#X} + V0", address);
		}

		/**
		 * @brief Returns the opcode and mask for the jump to address NNN + V0 instruction
		 * 
		 * @return InstructionInfo_t (0xB000, 0xF000) : Returns the opcode and mask for the jump to address NNN + V0 instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xB000, 0xF000};
		}

		/**
		 * @brief Update the instruction with the provided opcode
		 * 
		 * This function updates the instruction with the provided opcode.
		 * 
		 * @param opcode 	Opcode to update the instruction with
		 * @return Instruction* : Returns the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			address = opcode & 0x0FFF;
			registerX = (opcode & 0x0F00) >> 8;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_BNNN_HPP_ */