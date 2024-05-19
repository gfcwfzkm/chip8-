#ifndef _CHIP8_INSTRUCTIONS_HPP_
#define _CHIP8_INSTRUCTIONS_HPP_

#include <cstdint>
#include <string>
#include <array>
#include <format>
#include <memory>
#include "../system/cpu.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Instruction Interface
	 * 
	 * This class is an interface for the instructions. All instructions
	 * must inherit from this class and implement the virtual functions.
	 */
	class Instruction
	{
	public:
		/**
		 * @brief Instruction Info
		 * 
		 * This struct contains the opcode and mask for the instruction.
		 * Used to identify the instruction and correctly assign it on the
		 * instruction table.
		 */
		typedef struct
		{
			uint16_t opcode;	/**< Static opcode of the instruction */
			uint16_t mask;		/**< Mask to the static opcode */
		} InstructionInfo_t;

		/**
		 * @brief Virtual: Execute the instruction
		 * 
		 * This function executes the instruction and returns a boolean value
		 * to notify the CPU if the instruction was executed successfully.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool : Returns true if the instruction was executed successfully
		 */
		virtual bool Execute(CHIP8::CPU *cpu) = 0;

		/**
		 * @brief Virtual: Get the mnemonic for the instruction
		 * 
		 * This function returns the mnemonic for the instruction.
		 * 
		 * @return std::string : Returns the mnemonic for the instruction
		 */
		virtual std::string GetMnemonic() = 0;

		/**
		 * @brief Virtual: Get the description for the instruction
		 * 
		 * This function returns the description for the instruction.
		 * 
		 * @return std::string : Returns the description for the instruction
		 */
		virtual std::string GetDescription() = 0;

		/**
		 * @brief Virtual: Get the opcode and mask for the instruction
		 * 
		 * This function returns the opcode and mask for the instruction.
		 * 
		 * @return InstructionInfo_t : Returns the opcode and mask for the instruction
		 */
		virtual InstructionInfo_t GetInfo() = 0;

		/**
		 * @brief Virtual: Get the reason why the function returned false in Execute
		 * 
		 * This function provides a string that describes the reason why it failed or aborted
		 * 
		 * @return std::string : Returns the error report for the instruction
		*/
		virtual std::string GetAbortReason() {
			return "Instruction does not abort";
		}

		/**
		 * @brief Virtual: Update the instruction
		 * 
		 * This function updates the instruction with the opcode provided
		 * and returns the updated instruction.
		 * 
		 * @param opcode 	Opcode to update the instruction with
		 * @return Instruction* : Returns the updated instruction
		 */
		virtual std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) = 0;
	};
}

#endif /* _CHIP8_INSTRUCTIONS_HPP_ */