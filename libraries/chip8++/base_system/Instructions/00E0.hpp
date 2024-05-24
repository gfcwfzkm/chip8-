#ifndef _CHIP8_INSTRUCTIONS_00E0_HPP_
#define _CHIP8_INSTRUCTIONS_00E0_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Clear the display
	 * 
	 * This class represents the instruction to clear the display.
	 */
	class I00E0 : 
		public Instruction,
		public std::enable_shared_from_this<I00E0>
	{
	public:
		/**
		 * @brief Execute the instruction to clear the display
		 * 
		 * This function clears the display by setting all the pixels to 0.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			cpu->GetDisplay()->Clear();
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the clear display instruction
		 * 
		 * @return std::string (CLS) : Returns the mnemonic for the clear display instruction
		 */
		std::string GetMnemonic() override {
			return "CLR";
		}

		/**
		 * @brief Returns the description for the clear display instruction
		 * 
		 * @return std::string (Clear the display) : Returns the description for the clear display instruction
		 */
		std::string GetDescription() override {
			return "Clear the display";
		}

		/**
		 * @brief Returns the opcode and mask for the clear display instruction
		 * 
		 * @return InstructionInfo_t (0x00E0, 0xFFFF) : Returns the opcode and mask for the clear display instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x00E0, 0xFFFF};
		}

		/**
		 * @brief Updates the clear display instruction
		 * 
		 * This function updates the clear display instruction with the opcode provided and
		 * returns the updated clear display instruction.
		 * 
		 * @param opcode 	Opcode for the instruction
		 * @return Instruction* : Returns the updated clear display instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			(void)opcode;
			return std::static_pointer_cast<Instruction>(shared_from_this());
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_00E0_HPP_ */