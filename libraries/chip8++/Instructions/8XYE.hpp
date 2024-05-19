#ifndef _CHIP8_INSTRUCTIONS_8XYE_HPP_
#define _CHIP8_INSTRUCTIONS_8XYE_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Set register VX to the value of register VY shifted left by 1
	 * 
	 * This class represents the instruction to set register VX to the value of register VY shifted left by 1.
	 */
	class I8XYE : 
		public Instruction,
		public std::enable_shared_from_this<I8XYE>
	{
		uint8_t registerVX;
		uint8_t registerVY;
	public:
		/**
		 * @brief Execute the instruction to set register VX to the value of register VY shifted left by 1
		 * 
		 * This function sets register VX to the value of register VY shifted left by 1.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			bool flag;

			if (cpu->getQuirks().Shift)
			{
				flag = cpu->getRegister(registerVX) >> 7;
				cpu->setRegister(registerVX, cpu->getRegister(registerVX) << 1);
			}
			else
			{
				flag = cpu->getRegister(registerVY) >> 7;
				cpu->setRegister(registerVX, cpu->getRegister(registerVY) << 1);
			}
			
			cpu->setRegister(0xF, flag);
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the set register VX to the value of register VX shifted left by 1 instruction
		 * 
		 * @return std::string (SHL Vx) : Returns the mnemonic for the set register VX to the value of register VX shifted left by 1 instruction
		 */
		std::string GetMnemonic() override {
			return std::format("SHL V{:X}", registerVX);
		}

		/**
		 * @brief Returns the description for the set register VX to the value of register VX shifted left by 1 instruction
		 * 
		 * @return std::string (Set register Vx to Vx << 1) : Returns the description for the set register VX to the value of register VX shifted left by 1 instruction
		 */
		std::string GetDescription() override {
			return std::format("Set register V{:X} to the value of register V{:X} shifted left by 1", registerVX, registerVX);
		}

		/**
		 * @brief Returns the opcode and mask for the set register VX to the value of register VX shifted left by 1 instruction
		 * 
		 * @return InstructionInfo_t (0x800E, 0xF00F) : Returns the opcode and mask for the set register VX to the value of register VX shifted left by 1 instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x800E, 0xF00F};
		}

		/**
		 * @brief Update the instruction with the provided opcode
		 * 
		 * This function updates the instruction with the provided opcode.
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

#endif /* _CHIP8_INSTRUCTIONS_8XYE_HPP_ */