#ifndef _CHIP8_INSTRUCTIONS_EX9E_HPP_
#define _CHIP8_INSTRUCTIONS_EX9E_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Skip next instruction if key with the value of VX is pressed
	 * 
	 * This class represents the instruction to skip the next instruction if the key with the value of VX is pressed.
	 */
	class IEX9E : 
		public Instruction,
		public std::enable_shared_from_this<IEX9E>
	{
		uint8_t registerVX;
	public:
		/**
		 * @brief Execute the instruction to skip the next instruction if the key with the value of VX is pressed
		 * 
		 * This function skips the next instruction if the key with the value of VX is pressed.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {

			if (cpu->getKeypad()->IsKeyPressed((CHIP8::Keypad::Key)cpu->getRegister(registerVX)) == true)
			{
				cpu->setPC(cpu->getPC() + 2);
			}
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the skip the next instruction if the key with the value of VX is pressed instruction
		 * 
		 * @return std::string (SKP Vx) : Returns the mnemonic for the skip the next instruction if the key with the value of VX is pressed instruction
		 */
		std::string GetMnemonic() override {
			return std::format("SKP V{:X}", registerVX);
		}

		/**
		 * @brief Returns the description for the skip the next instruction if the key with the value of VX is pressed instruction
		 * 
		 * @return std::string (Skip next instruction if key with the value of Vx is pressed) : Returns the description for the skip the next instruction if the key with the value of VX is pressed instruction
		 */
		std::string GetDescription() override {
			return std::format("Skip next instruction if key with the value of V{:X} is pressed", registerVX);
		}

		/**
		 * @brief Returns the opcode and mask for the skip the next instruction if the key with the value of VX is pressed instruction
		 * 
		 * @return InstructionInfo_t (0xE09E, 0xF0FF) : Returns the opcode and mask for the skip the next instruction if the key with the value of VX is pressed instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xE09E, 0xF0FF};
		}

		/**
		 * @brief Update the instruction with the provided opcode
		 * 
		 * This function updates the instruction with the provided opcode.
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

#endif /* _CHIP8_INSTRUCTIONS_EX9E_HPP_ */