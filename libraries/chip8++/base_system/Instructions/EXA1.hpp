#ifndef _CHIP8_INSTRUCTIONS_EXA1_HPP_
#define _CHIP8_INSTRUCTIONS_EXA1_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Skip next instruction if key with the value of VX is not pressed
	 * 
	 * This class represents the instruction to skip the next instruction if the key with the value of VX is not pressed.
	 */
	class IEXA1 : 
		public Instruction,
		public std::enable_shared_from_this<IEXA1>
	{
		uint8_t registerVX;
	public:
		/**
		 * @brief Execute the instruction to skip the next instruction if the key with the value of VX is not pressed
		 * 
		 * This function skips the next instruction if the key with the value of VX is not pressed.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			if (cpu->GetKeypad()->IsKeyPressed((CHIP8::Keypad::Key)cpu->GetRegister(registerVX)) == false)
			{
				cpu->SetPC(cpu->GetPC() + 2);
			}
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the skip the next instruction if the key with the value of VX is not pressed instruction
		 * 
		 * @return std::string (SKNP Vx) : Returns the mnemonic for the skip the next instruction if the key with the value of VX is not pressed instruction
		 */
		std::string GetMnemonic() override {
			return std::format("SKNP V{:X}", registerVX);
		}

		/**
		 * @brief Returns the description for the skip the next instruction if the key with the value of VX is not pressed instruction
		 * 
		 * @return std::string (Skip next instruction if key with the value of Vx is not pressed) : Returns the description for the skip the next instruction if the key with the value of VX is not pressed instruction
		 */
		std::string GetDescription() override {
			return std::format("Skip next instruction if key with the value of V{:X} is not pressed", registerVX);
		}

		/**
		 * @brief Returns the opcode and mask for the skip the next instruction if the key with the value of VX is not pressed instruction
		 * 
		 * @return InstructionInfo_t (0xE0A1, 0xF0FF) : Returns the opcode and mask for the skip the next instruction if the key with the value of VX is not pressed instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xE0A1, 0xF0FF};
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

#endif /* _CHIP8_INSTRUCTIONS_EXA1_HPP_ */