#ifndef _CHIP8_INSTRUCTIONS_FX65_HPP_
#define _CHIP8_INSTRUCTIONS_FX65_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Fill registers V0 through VX with values from memory starting at address I
	 * 
	 * This class represents the instruction to fill registers V0 through VX with values from memory starting at address I.
	 */
	class IFX65 : 
		public Instruction,
		public std::enable_shared_from_this<IFX65>
	{
		uint8_t registerVX;
		std::expected<uint8_t, std::string> retValMemory;
	public:
		/**
		 * @brief Execute the instruction to fill registers V0 through VX with values from memory starting at address I
		 * 
		 * This function fills registers V0 through VX with values from memory starting at address I.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			for (uint8_t i = 0; i <= registerVX; i++)
			{
				retValMemory = cpu->GetMemory()->GetByte(cpu->GetIndex() + i);

				if (retValMemory)
				{
					cpu->SetRegister(i, retValMemory.value());
				}
				else
				{
					break;
				}
			}
			
			if (cpu->GetQuirks().MemoryIncrementByX)
			{
				cpu->SetIndex(cpu->GetIndex() + registerVX + 1);
			}
			
			return retValMemory ? true : false;
		};

		/**
		 * @brief Returns the mnemonic for the fill registers V0 through VX with values from memory starting at address I instruction
		 * 
		 * @return std::string (LD Vx, [I]) : Returns the mnemonic for the fill registers V0 through VX with values from memory starting at address I instruction
		 */
		std::string GetMnemonic() override {
			return std::format("LD V{:X}, [I]", registerVX);
		}

		/**
		 * @brief Returns the description for the fill registers V0 through VX with values from memory starting at address I instruction
		 * 
		 * @return std::string (Fill V0 to Vx with memory) : Returns the description for the fill registers V0 through VX with values from memory starting at address I instruction
		 */
		std::string GetDescription() override {
			return std::format("Fill registers V0 through V{:X} with values from memory starting at address I", registerVX);
		}

		/**
		 * @brief Returns the opcode and mask for the fill registers V0 through VX with values from memory starting at address I instruction
		 * 
		 * @return InstructionInfo_t (0xF065, 0xF0FF) : Returns the opcode and mask for the fill registers V0 through VX with values from memory starting at address I instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xF065, 0xF0FF};
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
		 * @param opcode 	Opcode to be used to update the instruction
		 * @return Instruction*	Pointer to the updated instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerVX = (opcode & 0x0F00) >> 8;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_FX65_HPP_ */