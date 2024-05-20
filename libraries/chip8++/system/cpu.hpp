#ifndef _CHIP8_CPU_HPP_
#define _CHIP8_CPU_HPP_

#include <cstdint>
#include <array>
#include <stdexcept>
#include <memory>
#include "memory.hpp"
#include "display.hpp"
#include "keypad.hpp"
#include "timers.hpp"
#include "quirks.hpp"

namespace CHIP8
{
	class InstructionDecoder;
	/**
	 * @brief CPU
	 * 
	 * This class represents the CHIP-8 CPU.
	 * The CPU has 16 8-bit registers, a 16-bit index register, a 16-bit program counter, and a 16-bit stack.
	 * The CPU also has a display, a keypad, and memory.
	 * The CPU can set and get registers, the index register, the program counter, and the stack.
	 * The CPU can also push and pop values from the stack.
	 */
	class CPU 
	{
		/** @brief Stack depth
		 * 
		 * This constant represents the depth of the stack.
		 */
		static constexpr int STACKDEPTH	= 16;

		/** @brief Number of work registers
		 * 
		 * This constant represents the number of work registers.
		 */
		static constexpr int WORK_REGS	= 16;

		/** @brief Work registers
		 * 
		 * This array stores the work registers.
		 */
		std::array<uint8_t, WORK_REGS> V;

		/** @brief Stack
		 * 
		 * This array stores the stack.
		 */
		std::array<uint16_t, STACKDEPTH> Stack;

		/** @brief Stack Pointer
		 * 
		 * This variable represents the stack pointer.
		 */
		size_t SP;

		/** @brief Index Register
		 * 
		 * This variable represents the index register.
		 */
		uint16_t I;

		/** @brief Program Counter
		 * 
		 * This variable represents the program counter.
		 */
		uint16_t PC;

		/** @brief Instruction Failure Description
		 * 
		 * This string holds the reason why an instruction has 
		 * failed or stopped the emulation. 
		 */
		std::string InstructionError;

		/** @brief Instruction Decoder
		 * 
		 * This variable represents the instruction decoder.
		 */
		std::shared_ptr<InstructionDecoder> decoder;

		/** @brief Memory
		 * 
		 * This variable represents the memory.
		 */
		std::shared_ptr<Memory> memory;

		/** @brief Keypad
		 * 
		 * This variable represents the keypad.
		 */
		//Keypad *keypad;
		std::shared_ptr<Keypad> keypad;

		/** @brief Display
		 * 
		 * This variable represents the display.
		 */
		std::shared_ptr<Display> display;

		std::shared_ptr<Timers> timers;

		/** @brief Quirks
		 * 
		 * This variable contains the quirks of the Chip8 platform
		 */
		Quirks quirks;
	public:
		
		CPU(std::shared_ptr<Keypad> keypad, std::shared_ptr<Display> display,
			std::shared_ptr<InstructionDecoder> decoder = nullptr,
			std::shared_ptr<Memory> memory = std::make_shared<Memory>(),
			std::shared_ptr<Timers> timers = std::make_shared<Timers>());

		/**
		 * @brief Reset the CPU
		 * 
		 * This function resets the CPU. If a full system reset is performed,
		 * the memory, display and timers are also reset.
		 * 
		 * @param fullSystemReset : Perform a full system reset
		 */
		void Reset(bool fullSystemReset = false);

		/**
		 * @brief Run a cycle
		 * 
		 * This function runs a cycle of the CPU.
		 * 
		 * @return true : The cycle was successful
		 * @return false : The cycle was unsuccessful
		 */
		bool RunCycle();

		/**
		 * @brief Set the Register
		 * 
		 * This function sets the register provided to the value provided.
		 * 
		 * @param reg : The register to set the value of
		 * @param value : The value to set the register to
		 */
		void SetRegister(uint8_t reg, uint8_t value);

		/**
		 * @brief Get the Register
		 * 
		 * This function returns the value of the register provided.
		 * 
		 * @param reg : The register to get the value of
		 * @return uint8_t : The value of the register
		 */
		uint8_t GetRegister(uint8_t reg);

		/**
		 * @brief Set the Index
		 * 
		 * This function sets the index register to the value provided.
		 * 
		 * @param value : The value to set the index register to
		 */
		void SetIndex(uint16_t value);

		/**
		 * @brief Get the Index
		 * 
		 * This function returns the value of the index register.
		 * 
		 * @return uint16_t : The value of the index register
		 */
		uint16_t GetIndex();

		/**
		 * @brief Set the PC
		 * 
		 * This function sets the program counter to the value provided.
		 * 
		 * @param value : The value to set the program counter to
		 */
		void SetPC(uint16_t value);

		/**
		 * @brief Get the PC
		 * 
		 * This function returns the value of the program counter.
		 * 
		 * @return uint16_t : The value of the program counter
		 */
		uint16_t GetPC();

		/**
		 * @brief Push a value onto the stack
		 * 
		 * This function pushes a value onto the stack.
		 * 
		 * @param value : The value to push onto the stack
		 */
		void PushStack(uint16_t value);

		/**
		 * @brief Pop a value from the stack
		 * 
		 * This function pops a value from the stack.
		 * 
		 * @return uint16_t : The value popped from the stack
		 */
		uint16_t PopStack();

		/**
		 * @brief Get the Display object
		 * 
		 * This function returns the display object.
		 * 
		 * @return Display* : The display object
		 */
		std::shared_ptr<Display> GetDisplay();

		/**
		 * @brief Get the Keypad object
		 * 
		 * This function returns the keypad object.
		 * 
		 * @return Keypad* : The keypad object
		 */
		std::shared_ptr<Keypad> GetKeypad();

		/**
		 * @brief Get the Memory object
		 * 
		 * This function returns the memory object.
		 * 
		 * @return Memory* : The memory object
		 */
		std::shared_ptr<Memory> GetMemory();

		/**
		 * @brief Get the Instruction Decoder object
		 * 
		 * This function returns the instruction decoder object.
		 * 
		 * @return InstructionDecoder* : The instruction decoder object
		 */
		std::shared_ptr<InstructionDecoder> GetDecoder();

		/**
		 * @brief Get the Quirks object
		 * 
		 * This function returns the quirks object.
		 * 
		 * @return Quirks* : The quirks object
		 */
		Quirks &GetQuirks();

		/**
		 * @brief Get Instruction Error
		 * 
		 * This function returns a handle to the instruction error
		 * 
		 * @return 
		 */
		const std::string &GetInstructionError();

		std::shared_ptr<Timers> GetTimers();
	};
}

#endif /* _CHIP8_CPU_HPP_ */