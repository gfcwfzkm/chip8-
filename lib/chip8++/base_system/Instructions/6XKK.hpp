#ifndef _CHIP8_INSTRUCTIONS_6XKK_HPP_
#define _CHIP8_INSTRUCTIONS_6XKK_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Set register X to KK
	 * 
	 * This class represents the instruction to set register X to KK.
	 */
	class I6XKK : 
		public Instruction,
		public std::enable_shared_from_this<I6XKK>
	{
		uint8_t registerV;
		uint8_t immediateValue;
	public:
		/**
		 * @brief Execute the instruction to set register X to KK
		 * 
		 * This function sets register X to KK.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			cpu->SetRegister(registerV, immediateValue);
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the set register X to KK instruction
		 * 
		 * @return std::string (LD Vx, byte) : Returns the mnemonic for the set register X to KK instruction
		 */
		std::string GetMnemonic() override {
			return std::format("LD V{:X}, 0x{:02X}", registerV, immediateValue);
		}

		/**
		 * @brief Returns the description for the set register X to KK instruction
		 * 
		 * @return std::string (Set register Vx to byte) : Returns the description for the set register X to KK instruction
		 */
		std::string GetDescription() override {
			return std::format("Set register V{:X} to 0x{:02X}", registerV, immediateValue);
		}

		/**
		 * @brief Returns the opcode and mask for the set register X to KK instruction
		 * 
		 * @return InstructionInfo_t (0x6000, 0xF000) : Returns the opcode and mask for the set register X to KK instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x6000, 0xF000};
		}

		/**
		 * @brief Updates the set register X to KK instruction
		 * 
		 * This function updates the set register X to KK instruction with the opcode provided and
		 * returns the updated set register X to KK instruction.
		 * 
		 * @param opcode 	Opcode to update the set register X to KK instruction with
		 * @return Instruction* : Returns the updated set register X to KK instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerV = (opcode & 0x0F00) >> 8;
			immediateValue = opcode & 0x00FF;
			return shared_from_this();
		}
	};

}

#endif /* _CHIP8_INSTRUCTIONS_6XKK_HPP_ */