#ifndef _CHIP8_INSTRUCTIONS_00EE_HPP_
#define _CHIP8_INSTRUCTIONS_00EE_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Return from a subroutine
	 * 
	 * This class represents the instruction to return from a subroutine.
	 */
	class I00EE : 
		public Instruction,
		public std::enable_shared_from_this<I00EE>
	{
	public:
		/**
		 * @brief Execute the instruction to return from a subroutine
		 * 
		 * This function returns from a subroutine.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			cpu->SetPC(cpu->PopStack());
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the return from a subroutine instruction
		 * 
		 * @return std::string (RET) : Returns the mnemonic for the return from a subroutine instruction
		 */
		std::string GetMnemonic() override {
			return "RET";
		}

		/**
		 * @brief Returns the description for the return from a subroutine instruction
		 * 
		 * @return std::string (Return from a subroutine) : Returns the description for the return from a subroutine instruction
		 */
		std::string GetDescription() override {
			return "Return from a subroutine";
		}

		/**
		 * @brief Returns the opcode and mask for the return from a subroutine instruction
		 * 
		 * @return InstructionInfo_t (0x00EE, 0xFFFF) : Returns the opcode and mask for the return from a subroutine instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x00EE, 0xFFFF};
		}

		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override
		{
			(void)opcode;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_00EE_HPP_ */