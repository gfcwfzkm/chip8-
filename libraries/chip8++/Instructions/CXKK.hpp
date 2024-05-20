#ifndef _CHIP8_INSTRUCTIONS_CXKK_HPP_
#define _CHIP8_INSTRUCTIONS_CXKK_HPP_

#include "Instruction.hpp"
#include <cstdlib>

namespace CHIP8::Instructions
{
	/**
	 * @brief Set register VX to random byte AND KK
	 * 
	 * This class represents the instruction to set register VX to random byte AND KK.
	 */
	class ICXKK : 
		public Instruction,
		public std::enable_shared_from_this<ICXKK>
	{
		uint8_t registerVX;
		uint8_t valueKK;
	public:
		/**
		 * @brief Execute the instruction to set register VX to random byte AND KK
		 * 
		 * This function sets register VX to random byte AND KK.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			uint8_t randomByte = std::rand() % 256;
			cpu->SetRegister(registerVX, randomByte & valueKK);
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the set register VX to random byte AND KK instruction
		 * 
		 * @return std::string (RND Vx, KK) : Returns the mnemonic for the set register VX to random byte AND KK instruction
		 */
		std::string GetMnemonic() override {
			return std::format("RND V{:X}, {:#X}", registerVX, valueKK);
		}

		/**
		 * @brief Returns the description for the set register VX to random byte AND KK instruction
		 * 
		 * @return std::string (Set Vx = random byte AND KK) : Returns the description for the set register VX to random byte AND KK instruction
		 */
		std::string GetDescription() override {
			return std::format("Set V{:X} = random byte AND {:#X}", registerVX, valueKK);
		}

		/**
		 * @brief Returns the opcode and mask for the set register VX to random byte AND KK instruction
		 * 
		 * @return InstructionInfo_t (0xC000, 0xF000) : Returns the opcode and mask for the set register VX to random byte AND KK instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xC000, 0xF000};
		}

		/**
		 * @brief Update the instruction with the provided opcode
		 * 
		 * This function updates the instruction with the provided opcode.
		 * 
		 * @param opcode 	Opcode to update the instruction with
		 * @return Instruction* : Returns the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerVX = (opcode & 0x0F00) >> 8;
			valueKK = opcode & 0x00FF;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_CXKK_HPP_ */