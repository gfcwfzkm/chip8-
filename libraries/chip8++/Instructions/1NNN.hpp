#ifndef _CHIP8_INSTRUCTIONS_1NNN_HPP_
#define _CHIP8_INSTRUCTIONS_1NNN_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Jump to address NNN
	 * 
	 * This class represents the instruction to jump to address NNN.
	 */
	class I1NNN : 
		public Instruction,
		public std::enable_shared_from_this<I1NNN>
	{
		uint16_t address = 0;
		bool endlessJump = false;
	public:
		/**
		 * @brief Execute the instruction to jump to address NNN
		 * 
		 * This function sets the program counter to NNN.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override
		{
			if (cpu->getQuirks().CatchEndlessJump)
			{
				if (address == (cpu->getPC() - 2))
				{
					return false;
				}
			}
			
			cpu->setPC(address);
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the jump to address NNN instruction
		 * 
		 * @return std::string (JP addr) : Returns the mnemonic for the jump to address NNN instruction
		 */
		std::string GetMnemonic() override
		{
			return std::format("JP {:03X}", address);
		}

		/**
		 * @brief Returns the description for the jump to address NNN instruction
		 * 
		 * @return std::string (Jump to address NNN) : Returns the description for the jump to address NNN instruction
		 */
		std::string GetDescription() override
		{
			return std::format("Jump to address {:03X}", address);
		}

		/**
		 * @brief Returns the opcode and mask for the jump to address NNN instruction
		 * 
		 * @return InstructionInfo_t (0x1000, 0xF000) : Returns the opcode and mask for the jump to address NNN instruction
		 */
		InstructionInfo_t GetInfo() override
		{
			return {0x1000, 0xF000};
		}

		std::string GetAbortReason() override
		{
			return std::format("While-Loop detected and emulation aborted due to enabled Quirk flag (Address 0x{:03X})", address);
		}

		/**
		 * @brief Updates the jump to address NNN instruction
		 * 
		 * @param opcode 	New opcode
		 * @return Instruction* : Returns the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override
		{
			address = opcode & 0x0FFF;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_1NNN_HPP_ */