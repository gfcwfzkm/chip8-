#ifndef _CHIP8_INSTRUCTIONS_8XY4_HPP_
#define _CHIP8_INSTRUCTIONS_8XY4_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Add register Y to register X
	 * 
	 * This class represents the instruction to add register Y to register X.
	 */
	class I8XY4 : 
		public Instruction,
		public std::enable_shared_from_this<I8XY4>
	{
		uint8_t registerVX;
		uint8_t registerVY;
	public:
		/**
		 * @brief Execute the instruction to add register Y to register X
		 * 
		 * This function adds register Y to register X.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			uint16_t value = cpu->GetRegister(registerVX) + cpu->GetRegister(registerVY);
			cpu->SetRegister(registerVX, uint8_t(value));
			cpu->SetRegister(0xF, value > 0xFF ? 1 : 0);
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the add register Y to register X instruction
		 * 
		 * @return std::string (ADD Vx, Vy) : Returns the mnemonic for the add register Y to register X instruction
		 */
		std::string GetMnemonic() override {
			return std::format("ADD V{:X}, V{:X}", registerVX, registerVY);
		}

		/**
		 * @brief Returns the description for the add register Y to register X instruction
		 * 
		 * @return std::string (Set register Vx to Vx + Vy) : Returns the description for the add register Y to register X instruction
		 */
		std::string GetDescription() override {
			return std::format("Set register V{:X} to V{:X} + V{:X}", registerVX, registerVX, registerVY);
		}

		/**
		 * @brief Returns the opcode and mask for the add register Y to register X instruction
		 * 
		 * @return InstructionInfo_t (0x8004, 0xF00F) : Returns the opcode and mask for the add register Y to register X instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x8004, 0xF00F};
		}

		/**
		 * @brief Updates the add register Y to register X instruction
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

#endif /* _CHIP8_INSTRUCTIONS_8XY4_HPP_ */