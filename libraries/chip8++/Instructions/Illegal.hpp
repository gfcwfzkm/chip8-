#ifndef _CHIP8_INSTRUCTIONS_ILLEGAL_HPP_
#define _CHIP8_INSTRUCTIONS_ILLEGAL_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Illegal Instruction
	 * 
	 * This class represents an illegal instruction. It should never be executed.
	 */
	class IllegalInstruction : 	public Instruction, public std::enable_shared_from_this<IllegalInstruction>
	{
		uint16_t instruction;
		uint16_t address;
	public:
		/**
		 * @brief Should never be executed, returns false
		 * 
		 * This instruction should never be executed, it is used to represent an illegal instruction.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (false) : Notify the CPU that the instruction is illegal
		 */
		bool Execute(CPU *cpu) override { 
			address = cpu->GetPC() - 2;
			return false;
		};

		/**
		 * @brief Returns the mnemonic for the illegal instruction
		 * 
		 * @return std::string (ILLEGAL) : Returns the mnemonic for the illegal instruction
		 */
		std::string GetMnemonic() override {
			return std::format("ILLEGAL: 0x{:04X}", instruction);
		}

		/**
		 * @brief Returns the description for the illegal instruction
		 * 
		 * @return std::string (Illegal Instruction) : Returns the description for the illegal instruction
		 */
		std::string GetDescription() override {
			return std::format("Illegal Instruction with opcode 0x{:#04X}", instruction);
		}

		/**
		 * @brief Returns the opcode and mask for the illegal instruction
		 * 
		 * @return InstructionInfo_t (0,0) : Returns the opcode and mask for the illegal instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0, 0};
		}

		/**
		 * @brief Returns the description text for emulation abortion
		 * 
		 * @return std::string : Returns the error report for the instruction
		 */
		std::string GetAbortReason() override {
			return std::format("Illegal instruction with opcode 0x{:04X} at address 0x{:04X}", instruction, address);
		}

		/**
		 * @brief Updates the illegal instruction
		 * 
		 * This function updates the illegal instruction with the opcode provided and
		 * returns the updated illegal instruction.
		 * 
		 * @param opcode 	Opcode to update the illegal instruction with
		 * @return Instruction* : Returns the updated illegal instruction
		 */
		std::shared_ptr<Instruction> Update(uint16_t opcode) override {
			instruction = opcode;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_ILLEGAL_HPP_ */