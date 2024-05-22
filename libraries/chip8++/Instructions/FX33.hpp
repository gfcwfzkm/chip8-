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
		uint16_t registerI;
		std::expected<void, std::string> retValMemory;
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
			registerI = cpu->GetIndex();
			auto mem = cpu->GetMemory();

			// Store the BCD representation of the value in memory
			for (int i = 2; i >= 0; i--) {
				retValMemory = mem->SetByte(registerI + i, value % 10);
				value /= 10;
				
				if (!retValMemory) {
					break;
				}
			}
			
			return retValMemory ? true : false;
		};

		/**
		 * @brief Returns the mnemonic for the store BCD representation of VX in memory locations I, I+1, and I+2 instruction
		 * 
		 * @return std::string (LD BCD, Vx) : Returns the mnemonic for the store BCD representation of VX in memory locations I, I+1, and I+2 instruction
		 */
		std::string GetMnemonic() override {
			return std::format("LD BCD, V{:X}", registerVX);
		}

		/**
		 * @brief Returns the description for the store BCD representation of VX in memory locations I, I+1, and I+2 instruction
		 * 
		 * @return std::string (Store BCD representation of Vx in memory locations I, I+1, and I+2) : Returns the description for the store BCD representation of VX in memory locations I, I+1, and I+2 instruction
		 */
		std::string GetDescription() override {
			return std::format("Store BCD representation of V{:X} in memory locations I=0x{:03X}, I+1, and I+2", registerVX, registerI);
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
		 * @brief Get the reason why the function returned false in Execute
		 * 
		 * This function provides a string that describes the reason why it failed or aborted
		 * 
		 * @return std::string : Returns the error report for the instruction
		 */
		std::string GetAbortReason() override {
			return retValMemory.error();
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