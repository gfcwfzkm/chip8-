#ifndef _CHIP8_INSTRUCTIONS_FX33_HPP_
#define _CHIP8_INSTRUCTIONS_FX33_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Store BCD representation of VX in memory locations I, I+1, and I+2
	 * 
	 * This class represents the instruction to store BCD representation of VX in memory locations I, I+1, and I+2.
	 */
	class IFX33 : 
		public Instruction,
		public std::enable_shared_from_this<IFX33>
	{
		uint8_t registerVX;
	public:
		/**
		 * @brief Execute the instruction to store BCD representation of VX in memory locations I, I+1, and I+2
		 * 
		 * This function stores BCD representation of VX in memory locations I, I+1, and I+2.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			uint8_t value = cpu->GetRegister(registerVX);
			cpu->GetMemory()->SetByte(cpu->GetIndex(), value / 100);
			cpu->GetMemory()->SetByte(cpu->GetIndex() + 1, (value / 10) % 10);
			cpu->GetMemory()->SetByte(cpu->GetIndex() + 2, value % 10);
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the store BCD representation of VX in memory locations I, I+1, and I+2 instruction
		 * 
		 * @return std::string (LD B, Vx) : Returns the mnemonic for the store BCD representation of VX in memory locations I, I+1, and I+2 instruction
		 */
		std::string GetMnemonic() override {
			return std::format("LD B, V{:X}", registerVX);
		}

		/**
		 * @brief Returns the description for the store BCD representation of VX in memory locations I, I+1, and I+2 instruction
		 * 
		 * @return std::string (Store BCD representation of Vx in memory locations I, I+1, and I+2) : Returns the description for the store BCD representation of VX in memory locations I, I+1, and I+2 instruction
		 */
		std::string GetDescription() override {
			return std::format("Store BCD representation of V{:X} in memory locations I, I+1, and I+2", registerVX);
		}

		/**
		 * @brief Returns the opcode and mask for the store BCD representation of VX in memory locations I, I+1, and I+2 instruction
		 * 
		 * @return InstructionInfo_t (0xF033, 0xF0FF) : Returns the opcode and mask for the store BCD representation of VX in memory locations I, I+1, and I+2 instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xF033, 0xF0FF};
		}

		/**
		 * @brief Update the instruction with the opcode
		 * 
		 * This function updates the instruction with the opcode.
		 * 
		 * @param opcode 	Opcode to update the instruction with
		 * @return Instruction*	Pointer to the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerVX = (opcode & 0x0F00) >> 8;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_FX33_HPP_ */