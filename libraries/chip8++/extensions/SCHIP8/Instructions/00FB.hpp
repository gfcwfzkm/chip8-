// Scroll display 4 pixels right
#ifndef SCHIP8_INSTRUCTIONS_00FB_HPP
#define SCHIP8_INSTRUCTIONS_00FB_HPP

#include "extensions/SCHIP8/display.hpp"
#include "base_system/Instructions/Instruction.hpp"

namespace CHIP8::SCHIP8::Instructions
{
    /**
     * @brief Scroll display 4 pixels right
     * 
     * This class represents the instruction to scroll the display 4 pixels right.
     */
    class I00FB :
        public CHIP8::Instructions::Instruction,
        public std::enable_shared_from_this<I00FB>
    {
    public:
        /**
         * @brief Execute the instruction to scroll the display 4 pixels right
         * 
         * This function scrolls the display 4 pixels right.
         * 
         * @param CPU 	Pointer to the CPU object
         * @return bool (true) : Notify the CPU that the instruction was executed
         */
        bool Execute(CHIP8::CPU *cpu) override {
            auto display = std::dynamic_pointer_cast<SCHIP8Display>(cpu->GetDisplay());
            display->ScrollRight();
            return true;
        }

        /**
         * @brief Returns the mnemonic for the scroll display 4 pixels right instruction
         * 
         * @return std::string (SCR) : Returns the mnemonic for the scroll display 4 pixels right instruction
         */
        std::string GetMnemonic() override {
            return "SCR";
        }

        /**
         * @brief Returns the description for the scroll display 4 pixels right instruction
         * 
         * @return std::string (Scroll display 4 pixels right) : Returns the description for the scroll display 4 pixels right instruction
         */
        std::string GetDescription() override {
            return "Scroll the display by 4 pixels to the right";
        }

        /**
         * @brief Returns the opcode and mask for the scroll display 4 pixels right instruction
         * 
         * @return InstructionInfo_t (0x00FB, 0xFFFF) : Returns the opcode and mask for the scroll display 4 pixels right instruction
         */
        InstructionInfo_t GetInfo() override {
            return {0x00FB, 0xFFFF};
        }

        /**
         * @brief Update the instruction
         * 
         * This function updates the instruction and returns the updated instruction.
         * 
         * @param opcode Opcode to update the instruction
         * @return std::shared_ptr<CHIP8::Instructions::Instruction> : Returns the updated instruction
         */
        std::shared_ptr<CHIP8::Instructions::Instruction> Update(uint16_t opcode) {
            (void)opcode;
        }
    };
}

#endif /* SCHIP8_INSTRUCTIONS_00FB_HPP */