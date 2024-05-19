#ifndef _CHIP8_INSTRUCTIONS_FX07_HPP_
#define _CHIP8_INSTRUCTIONS_FX07_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Set VX to the value of the delay timer
	 * 
	 * This class represents the instruction to set VX to the value of the delay timer.
	 */
	class IFX07 : 
		public Instruction,
		public std::enable_shared_from_this<IFX07>
	{
		uint8_t registerVX;
	public:
		/**
		 * @brief Execute the instruction to set VX to the value of the delay timer
		 * 
		 * This function sets VX to the value of the delay timer.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			cpu->setRegister(registerVX, cpu->getTimers()->getDelayTimer());
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the set VX to the value of the delay timer instruction
		 * 
		 * @return std::string (LD Vx, DT) : Returns the mnemonic for the set VX to the value of the delay timer instruction
		 */
		std::string GetMnemonic() override {
			return std::format("LD V{:X}, DT", registerVX);
		}

		/**
		 * @brief Returns the description for the set VX to the value of the delay timer instruction
		 * 
		 * @return std::string (Set Vx = delay timer value) : Returns the description for the set VX to the value of the delay timer instruction
		 */
		std::string GetDescription() override {
			return std::format("Set V{:X} = delay timer value", registerVX);
		}

		/**
		 * @brief Returns the opcode and mask for the set VX to the value of the delay timer instruction
		 * 
		 * @return InstructionInfo_t (0xF007, 0xF0FF) : Returns the opcode and mask for the set VX to the value of the delay timer instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xF007, 0xF0FF};
		}

		/**
		 * @brief Update the instruction with the opcode
		 * 
		 * This function updates the instruction with the opcode.
		 * 
		 * @param opcode : The opcode to update the instruction with
		 * @return std::shared_ptr<Instruction> : Returns a shared pointer to the instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerVX = (opcode & 0x0F00) >> 8;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_FX07_HPP_ */