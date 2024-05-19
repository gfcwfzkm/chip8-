#ifndef _CHIP8_INSTRUCTIONS_FX0A_HPP_
#define _CHIP8_INSTRUCTIONS_FX0A_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Wait for a key press and store the value of the key in VX
	 * 
	 * This class represents the instruction to wait for a key press and store the value of the key in VX.
	 */
	class IFX0A : 
		public Instruction,
		public std::enable_shared_from_this<IFX0A>
	{
		uint8_t registerVX;
	public:
		/**
		 * @brief Execute the instruction to wait for a key press and store the value of the key in VX
		 * 
		 * This function waits for a key press and stores the value of the key in VX.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			// Get the keypad
			CHIP8::Keypad::Key keypad = cpu->getKeypad()->WaitForKeyPress();

			if (keypad != CHIP8::Keypad::Key::KEY_INVALID) {
				// Store the key in the register
				cpu->setRegister(registerVX, (uint8_t)keypad);
			}
			else
			{
				// Decrement the program counter to repeat the instruction
				cpu->setPC(cpu->getPC() - 2);
			}

			return true;
		};

		/**
		 * @brief Returns the mnemonic for the wait for a key press and store the value of the key in VX instruction
		 * 
		 * @return std::string (LD Vx, K) : Returns the mnemonic for the wait for a key press and store the value of the key in VX instruction
		 */
		std::string GetMnemonic() override {
			return std::format("LD V{:X}, K", registerVX);
		}

		/**
		 * @brief Returns the description for the wait for a key press and store the value of the key in VX instruction
		 * 
		 * @return std::string (Wait for a key press and store the value of the key in Vx) : Returns the description for the wait for a key press and store the value of the key in VX instruction
		 */
		std::string GetDescription() override {
			return std::format("Wait for a key press and store the value of the key in V{:X}", registerVX);
		}

		/**
		 * @brief Returns the opcode and mask for the wait for a key press and store the value of the key in VX instruction
		 * 
		 * @return InstructionInfo_t (0xF00A, 0xF0FF) : Returns the opcode and mask for the wait for a key press and store the value of the key in VX instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xF00A, 0xF0FF};
		}

		/**
		 * @brief Update the instruction with the provided opcode
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

#endif /* _CHIP8_INSTRUCTIONS_FX0A_HPP_ */