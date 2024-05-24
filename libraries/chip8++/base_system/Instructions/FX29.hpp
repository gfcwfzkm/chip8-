#ifndef _CHIP8_INSTRUCTIONS_FX29_HPP_
#define _CHIP8_INSTRUCTIONS_FX29_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Set I to the location of the sprite for the character in VX
	 * 
	 * This class represents the instruction to set I to the location of the sprite for the character in VX.
	 */
	class IFX29 : 
		public Instruction,
		public std::enable_shared_from_this<IFX29>
	{
		uint8_t registerVX;
	public:
		/**
		 * @brief Execute the instruction to set I to the location of the sprite for the character in VX
		 * 
		 * This function sets I to the location of the sprite for the character in VX.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			cpu->SetIndex((cpu->GetRegister(registerVX) & 0x0F) * 5 + cpu->GetMemory()->GetFontStart());
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the set I to the location of the sprite for the character in VX instruction
		 * 
		 * @return std::string (LD F, Vx) : Returns the mnemonic for the set I to the location of the sprite for the character in VX instruction
		 */
		std::string GetMnemonic() override {
			return std::format("LD F, V{:X}", registerVX);
		}

		/**
		 * @brief Returns the description for the set I to the location of the sprite for the character in VX instruction
		 * 
		 * @return std::string (Set I = location of sprite for digit Vx) : Returns the description for the set I to the location of the sprite for the character in VX instruction
		 */
		std::string GetDescription() override {
			return std::format("Set I = location of sprite for digit V{:X}", registerVX);
		}

		/**
		 * @brief Returns the opcode and mask for the set I to the location of the sprite for the character in VX instruction
		 * 
		 * @return InstructionInfo_t (0xF029, 0xF0FF) : Returns the opcode and mask for the set I to the location of the sprite for the character in VX instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xF029, 0xF0FF};
		}

		/**
		 * @brief Update the instruction with the opcode
		 * 
		 * This function updates the instruction with the opcode.
		 * 
		 * @param opcode : The opcode to update the instruction with
		 * @return Instruction* : Returns the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerVX = (opcode & 0x0F00) >> 8;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_FX29_HPP_ */