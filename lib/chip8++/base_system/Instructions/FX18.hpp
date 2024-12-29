#ifndef _CHIP8_INSTUCTIONS_FX18_HPP_
#define _CHIP8_INSTUCTIONS_FX18_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Set the sound timer to the value of register VX
	 * 
	 * This class represents the instruction to set the sound timer to the value of register VX.
	 */
	class IFX18 : 
		public Instruction,
		public std::enable_shared_from_this<IFX18>
	{
		uint8_t registerVX;
	public:
		/**
		 * @brief Execute the instruction to set the sound timer to the value of register VX
		 * 
		 * This function sets the sound timer to the value of register VX.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			cpu->GetTimers()->SetSoundTimer(cpu->GetRegister(registerVX));
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the set the sound timer to the value of register VX instruction
		 * 
		 * @return std::string (LD ST, Vx) : Returns the mnemonic for the set the sound timer to the value of register VX instruction
		 */
		std::string GetMnemonic() override {
			return std::format("LD ST, V{:X}", registerVX);
		}

		/**
		 * @brief Returns the description for the set the sound timer to the value of register VX instruction
		 * 
		 * @return std::string (Set sound timer = Vx) : Returns the description for the set the sound timer to the value of register VX instruction
		 */
		std::string GetDescription() override {
			return std::format("Set sound timer = V{:X}", registerVX);
		}

		/**
		 * @brief Returns the opcode and mask for the set the sound timer to the value of register VX instruction
		 * 
		 * @return InstructionInfo_t (0xF018, 0xF0FF) : Returns the opcode and mask for the set the sound timer to the value of register VX instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xF018, 0xF0FF};
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

#endif /* _CHIP8_INSTUCTIONS_FX18_HPP_ */