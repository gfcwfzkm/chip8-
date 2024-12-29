#ifndef _CHIP8_INSTRUCTIONS_8XY7_HPP_
#define _CHIP8_INSTRUCTIONS_8XY7_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Set register VX to the value of VY minus VX
	 * 
	 * This class represents the instruction to set register VX to the value of VY minus VX.
	 */
	class I8XY7 : 
		public Instruction,
		public std::enable_shared_from_this<I8XY7>
	{
		uint8_t registerVX;
		uint8_t registerVY;
	public:
		/**
		 * @brief Execute the instruction to set register VX to the value of VY minus VX
		 * 
		 * This function sets register VX to the value of VY minus VX.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			bool notBorrow = cpu->GetRegister(registerVY) >= cpu->GetRegister(registerVX);
			cpu->SetRegister(registerVX, cpu->GetRegister(registerVY) - cpu->GetRegister(registerVX));
			cpu->SetRegister(0xF, notBorrow);
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the set register VX to the value of VY minus VX instruction
		 * 
		 * @return std::string (SUBN Vx, Vy) : Returns the mnemonic for the set register VX to the value of VY minus VX instruction
		 */
		std::string GetMnemonic() override {
			return std::format("SUBN V{:X}, V{:X}", registerVX, registerVY);
		}

		/**
		 * @brief Returns the description for the set register VX to the value of VY minus VX instruction
		 * 
		 * @return std::string (Set Vx = Vy - Vx) : Returns the description for the set register VX to the value of VY minus VX instruction
		 */
		std::string GetDescription() override {
			return std::format("Set register V{:X} to the value of V{:X} minus V{:X}", registerVX, registerVY, registerVX);
		}

		/**
		 * @brief Returns the opcode and mask for the set register VX to the value of VY minus VX instruction
		 * 
		 * @return InstructionInfo_t (0x8007, 0xF00F) : Returns the opcode and mask for the set register VX to the value of VY minus VX instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x8007, 0xF00F};
		}

		/**
		 * @brief Update the instruction with the provided opcode
		 * 
		 * This function updates the instruction with the provided opcode.
		 * 
		 * @param opcode : Opcode to update the instruction with
		 * @return Instruction* : Returns the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerVX = (opcode & 0x0F00) >> 8;
			registerVY = (opcode & 0x00F0) >> 4;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_8XY7_HPP_ */