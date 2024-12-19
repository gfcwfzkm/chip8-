// Scroll display 4 pixels left
#ifndef SCHIP8_INSTRUCTIONS_00FC_HPP
#define SCHIP8_INSTRUCTIONS_00FC_HPP

#include "extensions/SCHIP8/display.hpp"
#include "base_system/Instructions/Instruction.hpp"

namespace CHIP8::SCHIP8::Instructions
{
    /**
     * @brief Scroll display 4 pixels left
     * 
     * This class represents the instruction to scroll the display 4 pixels left.
     */
    class I00FC :
        public CHIP8::Instructions::Instruction,
        public std::enable_shared_from_this<I00FC>
    {
    public:
        /**
         * @brief Execute the instruction to scroll the display 4 pixels left
         * 
         * This function scrolls the display 4 pixels left.
         * 
         * @param CPU 	Pointer to the CPU object
         * @return bool (true) : Notify the CPU that the instruction was executed
         */
        bool Execute(CHIP8::CPU *cpu) override {
            auto display = std::dynamic_pointer_cast<SCHIP8Display>(cpu->GetDisplay());
            display->ScrollLeft();
            return true;
        }

        /**
         * @brief Returns the mnemonic for the scroll display 4 pixels left instruction
         * 
         * @return std::string (SCL) : Returns the mnemonic for the scroll display 4 pixels left instruction
         */
        std::string GetMnemonic() override {
            return "SCL";
        }

        /**
         * @brief Returns the description for the scroll display 4 pixels left instruction
         * 
         * @return std::string (Scroll display 4 pixels left) : Returns the description for the scroll display 4 pixels left instruction
         */
        std::string GetDescription() override {
            return "Scroll the display by 4 pixels to the left";
        }

        /**
         * @brief Returns the opcode and mask for the scroll display 4 pixels left instruction
         * 
         * @return InstructionInfo_t (0x00FC, 0xFFFF) : Returns the opcode and mask for the scroll display 4 pixels left instruction
         */
        InstructionInfo_t GetInfo() override {
            return {0x00FC, 0xFFFF};
        }

        std::shared_ptr<CHIP8::Instructions::Instruction> Update(uint16_t opcode) {
            (void)opcode;
        }
    };
}

#endif /* SCHIP8_INSTRUCTIONS_00FC_HPP */