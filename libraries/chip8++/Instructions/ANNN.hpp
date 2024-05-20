#ifndef _CHIP8_INSTRUCTIONS_ANNN_HPP_
#define _CHIP8_INSTRUCTIONS_ANNN_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Set I to the address NNN
	 * 
	 * This class represents the instruction to set the I register to the address NNN.
	 */
	class IANNN : 
		public Instruction,
		public std::enable_shared_from_this<IANNN>
	{
		uint16_t address;
	public:
		/**
		 * @brief Execute the instruction to set I to the address NNN
		 * 
		 * This function sets the I register to the address NNN.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			cpu->SetIndex(address);
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the set I to address NNN instruction
		 * 
		 * @return std::string (LD I, addr) : Returns the mnemonic for the set I to address NNN instruction
		 */
		std::string GetMnemonic() override {
			return std::format("LD I, {:03X}", address);
		}

		/**
		 * @brief Returns the description for the set I to address NNN instruction
		 * 
		 * @return std::string (Set I to address) : Returns the description for the set I to address NNN instruction
		 */
		std::string GetDescription() override {
			return std::format("Set I to {:03X}", address);
		}

		/**
		 * @brief Returns the opcode and mask for the set I to address NNN instruction
		 * 
		 * @return InstructionInfo_t (0xA000, 0xF000) : Returns the opcode and mask for the set I to address NNN instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xA000, 0xF000};
		}

		/**
		 * @brief Updates the set I to address NNN instruction
		 * 
		 * This function updates the set I to address NNN instruction with the opcode provided and
		 * returns the updated set I to address NNN instruction.
		 * 
		 * @param opcode 	Opcode to update the set I to address NNN instruction with
		 * @return Instruction* : Returns the updated set I to address NNN instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			address = opcode & 0x0FFF;
			return shared_from_this();
		}
	};

}

#endif /* _CHIP8_INSTRUCTIONS_ANNN_HPP_ */