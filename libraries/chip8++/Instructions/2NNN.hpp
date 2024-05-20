#ifndef _CHIP8_INSTRUCTIONS_2NNN_HPP_
#define _CHIP8_INSTRUCTIONS_2NNN_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Call subroutine at NNN
	 * 
	 * This class represents the instruction to call a subroutine at NNN.
	 */
	class I2NNN : 
		public Instruction,
		public std::enable_shared_from_this<I2NNN>
	{
		uint16_t address;
	public:
		/**
		 * @brief Execute the instruction to call a subroutine at NNN
		 * 
		 * This function calls a subroutine at NNN.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			cpu->PushStack(cpu->GetPC());
			cpu->SetPC(address);
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the call a subroutine at NNN instruction
		 * 
		 * @return std::string (CALL NNN) : Returns the mnemonic for the call a subroutine at NNN instruction
		 */
		std::string GetMnemonic() override {
			return std::format("CALL {:X}", address);
		}

		/**
		 * @brief Returns the description for the call a subroutine at NNN instruction
		 * 
		 * @return std::string (Call subroutine at NNN) : Returns the description for the call a subroutine at NNN instruction
		 */
		std::string GetDescription() override {
			return std::format("Call subroutine at {:X}", address);
		}

		/**
		 * @brief Returns the opcode and mask for the call a subroutine at NNN instruction
		 * 
		 * @return InstructionInfo_t (0x2000, 0xF000) : Returns the opcode and mask for the call a subroutine at NNN instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x2000, 0xF000};
		}

		/**
		 * @brief Update the instruction with the opcode
		 * 
		 * This function updates the instruction with the opcode.
		 * 
		 * @param opcode 	Opcode to update the instruction with
		 * @return Instruction* : Returns the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override
		{
			address = opcode & 0x0FFF;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_2NNN_HPP_ */