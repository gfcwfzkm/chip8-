#ifndef _CHIP8_INSTRUCTIONS_3XKK_HPP_
#define _CHIP8_INSTRUCTIONS_3XKK_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Skip next instruction if Vx == KK
	 * 
	 * This class represents the instruction to skip the next instruction if Vx == KK.
	 */
	class I3XKK : 
		public Instruction,
		public std::enable_shared_from_this<I3XKK>
	{
		uint8_t registerV;
		uint8_t immediateValue;
	public:
		/**
		 * @brief Execute the instruction to skip the next instruction if Vx == KK
		 * 
		 * This function skips the next instruction if Vx == KK.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			if (cpu->GetRegister(registerV) == immediateValue)
			{
				cpu->SetPC(cpu->GetPC() + 2);
			}
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the skip next instruction if Vx == KK instruction
		 * 
		 * @return std::string (SE Vx, byte) : Returns the mnemonic for the skip next instruction if Vx == KK instruction
		 */
		std::string GetMnemonic() override {
			return std::format("SE V{:X}, {:02X}", registerV, immediateValue);
		}

		/**
		 * @brief Returns the description for the skip next instruction if Vx == KK instruction
		 * 
		 * @return std::string (Skip next instruction if Vx == byte) : Returns the description for the skip next instruction if Vx == KK instruction
		 */
		std::string GetDescription() override {
			return std::format("Skip next instruction if V{:X} == {:02X}", registerV, immediateValue);
		}

		/**
		 * @brief Returns the opcode and mask for the skip next instruction if Vx == KK instruction
		 * 
		 * @return InstructionInfo_t (0x3000, 0xF000) : Returns the opcode and mask for the skip next instruction if Vx == KK instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0x3000, 0xF000};
		}

		/**
		 * @brief Updates the skip next instruction if Vx == KK instruction
		 * 
		 * @param opcode 	16-bit opcode
		 * @return Instruction* : Returns the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerV = (opcode & 0x0F00) >> 8;
			immediateValue = opcode & 0x00FF;
			return shared_from_this();
		};
	};
}

#endif /* _CHIP8_INSTRUCTIONS_3XKK_HPP_ */