#ifndef _CHIP8_INSTRUCTIONS_5XY0_HPP_
#define _CHIP8_INSTRUCTIONS_5XY0_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Skip next instruction if Vx == Vy
	 * 
	 * This class represents the instruction to skip the next instruction if Vx == Vy.
	 */
	class I5XY0 : 
		public Instruction,
		public std::enable_shared_from_this<I5XY0>
	{
		uint8_t registerVX;
		uint8_t registerVY;
	public:
		/**
		 * @brief Execute the instruction to skip the next instruction if Vx == Vy
		 * 
		 * This function skips the next instruction if Vx == Vy.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			if (cpu->getRegister(registerVX) == cpu->getRegister(registerVY))
			{
				cpu->setPC(cpu->getPC() + 2);
			}
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the skip next instruction if Vx == Vy instruction
		 * 
		 * @return std::string (SE Vx, Vy) : Returns the mnemonic for the skip next instruction if Vx == Vy instruction
		 */
		std::string GetMnemonic() override {
			return std::format("SE V{:X}, V{:X}", registerVX, registerVY);
		}

		/**
		 * @brief Returns the description for the skip next instruction if Vx == Vy instruction
		 * 
		 * @return std::string (Skip next instruction if Vx == Vy) : Returns the description for the skip next instruction if Vx == Vy instruction
		 */
		std::string GetDescription() override {
			return std::format("Skip next instruction if V{:X} == V{:X}", registerVX, registerVY);
		}

		/**
		 * @brief Returns the opcode and mask for the skip next instruction if Vx == Vy instruction
		 * 
		 * @return InstructionInfo_t (0x5000, 0xF00F) : Returns the opcode and mask for the skip next instruction if Vx == Vy instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x5000, 0xF00F};
		}

		/**
		 * @brief Updates the skip next instruction if Vx == Vy instruction
		 * 
		 * This function updates the skip next instruction if Vx == Vy.
		 * 
		 * @param opcode 	Opcode to be used for the update
		 * @return Instruction* 	Pointer to the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerVX = (opcode & 0x0F00) >> 8;
			registerVY = (opcode & 0x00F0) >> 4;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_5XY0_HPP_ */