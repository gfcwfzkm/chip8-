#ifndef _ChIP8_INSTRUCTIONS_8XY5_HPP_
#define _ChIP8_INSTRUCTIONS_8XY5_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Set register VX to the value of register VX - register VY
	 * 
	 * This class represents the instruction to set register VX to the value of register VX - register VY.
	 */
	class I8XY5 : 
		public Instruction,
		public std::enable_shared_from_this<I8XY5>
	{
		uint8_t registerVX;
		uint8_t registerVY;
	public:
		/**
		 * @brief Execute the instruction to set register VX to the value of register VX - register VY
		 * 
		 * This function sets register VX to the value of register VX - register VY.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			bool notBorrow = cpu->getRegister(registerVX) >= cpu->getRegister(registerVY);
			cpu->setRegister(registerVX, cpu->getRegister(registerVX) - cpu->getRegister(registerVY));
			cpu->setRegister(0xF, notBorrow);
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the set register VX to the value of register VX - register VY instruction
		 * 
		 * @return std::string (SUB Vx, Vy) : Returns the mnemonic for the set register VX to the value of register VX - register VY instruction
		 */
		std::string GetMnemonic() override {
			return std::format("SUB V{:X}, V{:X}", registerVX, registerVY);
		}

		/**
		 * @brief Returns the description for the set register VX to the value of register VX - register VY instruction
		 * 
		 * @return std::string (Set register Vx to Vx - Vy) : Returns the description for the set register VX to the value of register VX - register VY instruction
		 */
		std::string GetDescription() override {
			return std::format("Set register V{:X} to V{:X} - V{:X}", registerVX, registerVX, registerVY);
		}

		/**
		 * @brief Returns the opcode and mask for the set register VX to the value of register VX - register VY instruction
		 * 
		 * @return InstructionInfo_t (0x8005, 0xF00F) : Returns the opcode and mask for the set register VX to the value of register VX - register VY instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x8005, 0xF00F};
		}

		/**
		 * @brief Updates the set register VX to the value of register VX - register VY instruction
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

#endif /* _ChIP8_INSTRUCTIONS_8XY5_HPP_ */