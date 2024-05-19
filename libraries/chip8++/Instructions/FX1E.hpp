#ifndef _CHIP8_INSTRUCTIONS_FX1E_HPP_
#define _CHIP8_INSTRUCTIONS_FX1E_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Add the value of register VX to the I register
	 * 
	 * This class represents the instruction to add the value of register VX to the I register.
	 */
	class IFX1E : 
		public Instruction,
		public std::enable_shared_from_this<IFX1E>
	{
		uint8_t registerVX;
	public:
		/**
		 * @brief Execute the instruction to add the value of register VX to the I register
		 * 
		 * This function adds the value of register VX to the I register.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			cpu->setIndex(cpu->getIndex() + cpu->getRegister(registerVX));
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the add the value of register VX to the I register instruction
		 * 
		 * @return std::string (ADD I, Vx) : Returns the mnemonic for the add the value of register VX to the I register instruction
		 */
		std::string GetMnemonic() override {
			return std::format("ADD I, V{:X}", registerVX);
		}

		/**
		 * @brief Returns the description for the add the value of register VX to the I register instruction
		 * 
		 * @return std::string (Add the value of Vx to I) : Returns the description for the add the value of register VX to the I register instruction
		 */
		std::string GetDescription() override {
			return std::format("Add the value of register V{:X} to the I register", registerVX);
		}

		/**
		 * @brief Returns the opcode and mask for the add the value of register VX to the I register instruction
		 * 
		 * @return InstructionInfo_t (0xF01E, 0xF0FF) : Returns the opcode and mask for the add the value of register VX to the I register instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xF01E, 0xF0FF};
		}

		/**
		 * @brief Update the instruction with the opcode
		 * 
		 * This function updates the instruction with the opcode.
		 * 
		 * @param opcode : The opcode to update the instruction with
		 * @return Instruction* : Returns the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerVX = (opcode & 0x0F00) >> 8;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_FX1E_HPP_ */