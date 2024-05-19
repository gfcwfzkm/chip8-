#ifndef _CHIP8_INSTRUCTIONS_8XY2_HPP_
#define _CHIP8_INSTRUCTIONS_8XY2_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Set register X to the value of register X AND register Y
	 * 
	 * This class represents the instruction to set register X to the value of register X AND register Y.
	 */
	class I8XY2 : 
		public Instruction,
		public std::enable_shared_from_this<I8XY2>
	{
		uint8_t registerVX;
		uint8_t registerVY;
	public:
		/**
		 * @brief Execute the instruction to set register X to the value of register X AND register Y
		 * 
		 * This function sets register X to the value of register X AND register Y.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			cpu->setRegister(registerVX, cpu->getRegister(registerVX) & cpu->getRegister(registerVY));
			if (cpu->getQuirks().VFreset)
			{
				cpu->setRegister(0xF, 0);
			}
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the set register X to the value of register X AND register Y instruction
		 * 
		 * @return std::string (AND Vx, Vy) : Returns the mnemonic for the set register X to the value of register X AND register Y instruction
		 */
		std::string GetMnemonic() override {
			return std::format("AND V{:X}, V{:X}", registerVX, registerVY);
		}

		/**
		 * @brief Returns the description for the set register X to the value of register X AND register Y instruction
		 * 
		 * @return std::string (Set register Vx to Vx AND Vy) : Returns the description for the set register X to the value of register X AND register Y instruction
		 */
		std::string GetDescription() override {
			return std::format("Set register V{:X} to V{:X} AND V{:X}", registerVX, registerVX, registerVY);
		}

		/**
		 * @brief Returns the opcode and mask for the set register X to the value of register X AND register Y instruction
		 * 
		 * @return InstructionInfo_t (0x8002, 0xF00F) : Returns the opcode and mask for the set register X to the value of register X AND register Y instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x8002, 0xF00F};
		}

		/**
		 * @brief Updates the set register X to the value of register X AND register Y instruction
		 * 
		 * @param opcode The new opcode
		 * @return Instruction* Returns the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerVX = (opcode & 0x0F00) >> 8;
			registerVY = (opcode & 0x00F0) >> 4;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_8XY2_HPP_ */