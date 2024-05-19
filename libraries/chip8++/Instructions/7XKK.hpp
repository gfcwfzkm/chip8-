#ifndef _CHIP8_INSTRUCTIONS_7XKK_HPP_
#define _CHIP8_INSTRUCTIONS_7XKK_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Add KK to register X
	 * 
	 * This class represents the instruction to add KK to register X.
	 */
	class I7XKK : 
		public Instruction,
		public std::enable_shared_from_this<I7XKK>
	{
		uint8_t registerV;
		uint8_t immediateValue;
	public:
		/**
		 * @brief Execute the instruction to add KK to register X
		 * 
		 * This function adds KK to register X.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			cpu->setRegister(registerV, cpu->getRegister(registerV) + immediateValue);
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the add KK to register X instruction
		 * 
		 * @return std::string (ADD Vx, byte) : Returns the mnemonic for the add KK to register X instruction
		 */
		std::string GetMnemonic() override {
			return std::format("ADD V{:X}, {:02X}", registerV, immediateValue);
		}

		/**
		 * @brief Returns the description for the add KK to register X instruction
		 * 
		 * @return std::string (Add byte to register Vx) : Returns the description for the add KK to register X instruction
		 */
		std::string GetDescription() override {
			return std::format("Add {:02X} to register V{:X}", immediateValue, registerV);
		}

		/**
		 * @brief Returns the opcode and mask for the add KK to register X instruction
		 * 
		 * @return InstructionInfo_t (0x7000, 0xF000) : Returns the opcode and mask for the add KK to register X instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x7000, 0xF000};
		}

		/**
		 * @brief Updates the add KK to register X instruction
		 * 
		 * @param opcode The new opcode
		 * @return Instruction* Returns the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerV = (opcode & 0x0F00) >> 8;
			immediateValue = opcode & 0x00FF;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_7XKK_HPP_ */