// Exit CHIP interpreter
#ifndef SCHIP8_INSTRUCTIONS_00FD_HPP
#define SCHIP8_INSTRUCTIONS_00FD_HPP

#include "base_system/Instructions/Instruction.hpp"

namespace CHIP8::SCHIP8::Instructions
{
    /**
     * @brief Exit CHIP interpreter
     * 
     * This class represents the instruction to exit the CHIP interpreter.
     */
    class I00FD :
        public CHIP8::Instructions::Instruction,
        public std::enable_shared_from_this<I00FD>
    {
    public:
        /**
         * @brief Execute the instruction to exit the CHIP interpreter
         * 
         * This function exits the CHIP interpreter.
         * 
         * @param CPU 	Pointer to the CPU object
         * @return bool (false) : Notify the CPU that the instruction was executed
         */
        bool Execute(CHIP8::CPU *cpu) override {
            (void)cpu;
            return false;
        }

        /**
         * @brief Returns the mnemonic for the exit CHIP interpreter instruction
         * 
         * @return std::string (EXT) : Returns the mnemonic for the exit CHIP interpreter instruction
         */
        std::string GetMnemonic() override {
            return "EXT";
        }

        /**
         * @brief Returns the description for the exit CHIP interpreter instruction
         * 
         * @return std::string (Exit CHIP interpreter) : Returns the description for the exit CHIP interpreter instruction
         */
        std::string GetDescription() override {
            return "Exit the CHIP interpreter";
        }

        /**
         * @brief Returns the opcode and mask for the exit CHIP interpreter instruction
         * 
         * @return InstructionInfo_t (0x00FD, 0xFFFF) : Returns the opcode and mask for the exit CHIP interpreter instruction
         */
        InstructionInfo_t GetInfo() override {
            return {0x00FD, 0xFFFF};
        }

        std::shared_ptr<CHIP8::Instructions::Instruction> Update(uint16_t opcode) {
            (void)opcode;
        }
    };
}

#endif /* SCHIP8_INSTRUCTIONS_00FD_HPP */