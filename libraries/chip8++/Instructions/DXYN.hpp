#ifndef _CHIP8_INSTRUCTIONS_DXYN_HPP_
#define _CHIP8_INSTRUCTIONS_DXYN_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Draw a sprite at position (VX, VY) with N bytes of sprite data starting at the address stored in I
	 * 
	 * This class represents the instruction to draw a sprite at position (VX, VY) with N bytes of sprite data starting at the address stored in I.
	 */
	class IDXYN : 
		public Instruction,
		public std::enable_shared_from_this<IDXYN>
	{
		uint8_t RegX;
		uint8_t RegY;
		uint8_t SpritesN;
		std::expected<uint8_t, std::string> retValMemory;
	public:
		/**
		 * @brief Execute the instruction to draw a sprite at position (VX, VY) with N bytes of sprite data starting at the address stored in I
		 * 
		 * This function draws a sprite at position (VX, VY) with N bytes of sprite data starting at the address stored in I.
		 * A sprite has a fixed width of 8 pixels and a variable height of N pixels between 1 and 15.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			auto Display = cpu->GetDisplay();
			uint8_t DisplayX = cpu->GetRegister(RegX) % Display->GetWidth();
			uint8_t DisplayY = cpu->GetRegister(RegY) % Display->GetHeight();
			bool collision = false;
			bool WrapQuirk = cpu->GetQuirks().WrapSprite;
			
			// Reset the error message variable
			// retValMemory = std::expected<uint8_t, std::string>(0);

			for (int iy = 0; iy < SpritesN; iy++)
			{
				retValMemory = cpu->GetMemory()->GetByte(cpu->GetIndex() + iy);

				// On error, break the loop
				if (!retValMemory)
				{
					break;
				}

				for(int ix = 0; ix < 8; ix++)
				{
					int SpriteX = (DisplayX + ix);
					int SpriteY = (DisplayY + iy);

					if (WrapQuirk)
					{
						SpriteX = SpriteX % Display->GetWidth();
						SpriteY = SpriteY % Display->GetHeight();
					}
					else
					{
						if (SpriteX >= Display->GetWidth() || SpriteY >= Display->GetHeight())
						{
							continue;
						}
					}

					if ((retValMemory.value() & (0x80 >> ix)) != 0)
					{
						if (Display->at(SpriteX, SpriteY))
						{
							collision = true;
						}
						Display->at(SpriteX, SpriteY) = Display->at(SpriteX, SpriteY) ^ true;
					}
				}
			}

			Display->SetUpdateRequired();
			cpu->SetRegister(0xF, collision ? 1 : 0);

			return retValMemory ? true : false;
		};

		/**
		 * @brief Returns the mnemonic for the draw sprite instruction
		 * 
		 * @return std::string (DRW) : Returns the mnemonic for the draw sprite instruction
		 */
		std::string GetMnemonic() override {
			return std::format("DRAW V{:X}, V{:X}, {:X}", RegX, RegY, SpritesN);
		}

		/**
		 * @brief Returns the description for the draw sprite instruction
		 * 
		 * @return std::string (Draw a sprite at position (VX, VY) with N bytes of sprite data starting at the address stored in I) : Returns the description for the draw sprite instruction
		 */
		std::string GetDescription() override {
			return std::format("Draw a sprite at position (V{:X}, V{:X}) with {:X} "
				"bytes of sprite data starting at the address stored in I", RegX, RegY, SpritesN);
			}

		/**
		 * @brief Returns the opcode and mask for the draw sprite instruction
		 * 
		 * @return InstructionInfo_t (0xA000, 0xF000) : Returns the opcode and mask for the draw sprite instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xD000, 0xF000};
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
		 * @brief Updates the draw sprite instruction
		 * 
		 * This function updates the draw sprite instruction with the opcode provided and
		 * returns the updated draw sprite instruction.
		 * 
		 * @param opcode 	Opcode for the draw sprite instruction
		 * @return Instruction* : Returns the updated draw sprite instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			RegX = (opcode & 0x0F00) >> 8;
			RegY = (opcode & 0x00F0) >> 4;
			SpritesN = opcode & 0x000F;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_DXYN_HPP_ */