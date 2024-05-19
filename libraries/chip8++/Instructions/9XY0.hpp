#ifndef _CHIP8_INSTRUCTIONS_9XY0_HPP_
#define _CHIP8_INSTRUCTIONS_9XY0_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Skip next instruction if VX != VY
	 * 
	 * This class represents the instruction to skip the next instruction if VX != VY.
	 */
	class I9XY0 : 
		public Instruction,
		public std::enable_shared_from_this<I9XY0>
	{
		uint8_t registerVX;
		uint8_t registerVY;
	public:
		/**
		 * @brief Execute the instruction to skip the next instruction if VX != VY
		 * 
		 * This function skips the next instruction if VX != VY.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			if (cpu->getRegister(registerVX) != cpu->getRegister(registerVY))
			{
				cpu->setPC(cpu->getPC() + 2);
			}
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the skip the next instruction if VX != VY instruction
		 * 
		 * @return std::string (SNE Vx, Vy) : Returns the mnemonic for the skip the next instruction if VX != VY instruction
		 */
		std::string GetMnemonic() override {
			return std::format("SNE V{:X}, V{:X}", registerVX, registerVY);
		}

		/**
		 * @brief Returns the description for the skip the next instruction if VX != VY instruction
		 * 
		 * @return std::string (Skip next instruction if Vx != Vy) : Returns the description for the skip the next instruction if VX != VY instruction
		 */
		std::string GetDescription() override {
			return std::format("Skip next instruction if V{:X} != V{:X}", registerVX, registerVY);
		}

		/**
		 * @brief Returns the opcode and mask for the skip the next instruction if VX != VY instruction
		 * 
		 * @return InstructionInfo_t (0x9000, 0xF00F) : Returns the opcode and mask for the skip the next instruction if VX != VY instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x9000, 0xF00F};
		}

		/**
		 * @brief Update the instruction with the provided opcode
		 * 
		 * @param opcode Opcode to be used to update the instruction
		 * @return Instruction* Returns the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerVX = (opcode & 0x0F00) >> 8;
			registerVY = (opcode & 0x00F0) >> 4;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_9XY0_HPP_ */