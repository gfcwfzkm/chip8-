#ifndef _CHIP8_INSTRUCTIONDECODER_HPP_
#define _CHIP8_INSTRUCTIONDECODER_HPP_

#include <cstdint>
#include <array>
#include <memory>
#include <expected>
#include "Instructions/Instruction.hpp"

namespace CHIP8
{
	/**
	 * @brief Instruction Decoder
	 * 
	 * This class represents the instruction decoder. It decodes the opcode and returns the instruction.
	 */
	class InstructionDecoder
	{
		/** @brief Instruction Table
		 * 
		 * This array stores the instruction objects based on the opcode.
		 */
		std::array<std::shared_ptr<Instructions::Instruction>, (1<<16)> InstructionTable;

		/** @brief Bad InstructionS
		 * 
		 * This pointer stores the illegal instruction object.
		 */
		std::shared_ptr<Instructions::Instruction> badInstruction;
	public:
		/**
		 * @brief Construct a new Instruction Decoder object
		 * 
		 * This constructor initializes the instruction table with the default instruction.
		 * 
		 * @param defaultInstruction 	Default instruction to initialize the instruction table
		 */
		InstructionDecoder(std::shared_ptr<Instructions::Instruction> illegalInstruction) {
			InstructionTable.fill(illegalInstruction);
			badInstruction = illegalInstruction;
		};

		/**
		 * @brief Destroy the Instruction Decoder object
		 * 
		 * This destructor deletes all the instruction objects in the instruction table.
		 */
		~InstructionDecoder() = default;
		
		/**
		 * @brief Register an instruction
		 * 
		 * This function registers an instruction in the instruction table.
		 * 
		 * @param instruction 	Pointer to the instruction object
		 */
		std::expected<void, std::string> RegisterInstruction(std::shared_ptr<Instructions::Instruction> instruction) {
			auto InstructionInfo = instruction->GetInfo();

			if (InstructionInfo.mask & 0xF000)
			{
				for (int i = 0; i < 0x1000; i++)
				{
					auto num = (InstructionInfo.opcode & InstructionInfo.mask) | (i & ~InstructionInfo.mask);
					InstructionTable[num] = instruction;
				}
			}
			else
			{
				return std::unexpected(std::format("Invalid mask, got 0x{:04X} which gets masked with 0xF000", InstructionInfo.mask));
			}
			return std::expected<void, std::string>();
		}
		
		/**
		 * @brief Decode the instruction
		 * 
		 * This function decodes the opcode and returns the instruction.
		 * 
		 * @param opcode 						Opcode to decode
		 * @return Instructions::Instruction* 	Pointer to the instruction object
		 */
		std::shared_ptr<Instructions::Instruction> DecodeInstruction(uint16_t opcode) {
			return InstructionTable[opcode]->Update(opcode);
		}

		/**
		 * @brief Get the bad instruction
		 * 
		 * This function returns the illegal instruction object.
		 * 
		 * @return Instructions::Instruction* 	Pointer to the illegal instruction object
		 */
		std::shared_ptr<Instructions::Instruction> GetBadInstruction() {
			return badInstruction;
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONDECODER_HPP_ */