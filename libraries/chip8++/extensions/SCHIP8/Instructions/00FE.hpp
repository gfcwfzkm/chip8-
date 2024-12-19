// Disable extended screen mode
#ifndef SCHIP8_INSTRUCTIONS_00FE_HPP
#define SCHIP8_INSTRUCTIONS_00FE_HPP

#include "extensions/SCHIP8/display.hpp"
#include "base_system/Instructions/Instruction.hpp"

namespace CHIP8::SCHIP8::Instructions
{
    class I00FE :
        public CHIP8::Instructions::Instruction,
        public std::enable_shared_from_this<I00FE>
    {
    public:
        bool Execute(CHIP8::CPU *cpu) override {
            auto display = std::dynamic_pointer_cast<SCHIP8Display>(cpu->GetDisplay());
            display->SetHighRes(false);
            return true;
        }

        std::string GetMnemonic() override {
            return "LRS";
        }

        std::string GetDescription() override {
            return "Disable extended screen mode";
        }

        InstructionInfo_t GetInfo() override {
            return {0x00FE, 0xFFFF};
        }

        std::shared_ptr<CHIP8::Instructions::Instruction> Update(uint16_t opcode) {
            (void)opcode;
        }
    };
}

#endif /* SCHIP8_INSTRUCTIONS_00FE_HPP */