#ifndef _CHIP8_EXCEPTIONS_HPP_
#define _CHIP8_EXCEPTIONS_HPP_

#include <stdexcept>

namespace CHIP8
{
	/**
	 * @brief Decoding Error
	 * 
	 * This class represents an error decoding an instruction.
	 */
	class DecodingError : public std::runtime_error
	{
		
	};

	/**
	 * @brief Stack Underflow
	 * 
	 * This class represents a stack underflow error.
	 */
	class StackUnderflow : public std::underflow_error
	{
		
	};

	/**
	 * @brief Stack Overflow
	 * 
	 * This class represents a stack overflow error.
	 */
	class StackOverflow : public std::exception
	{
		
	};

	/**
	 * @brief Invalid Register
	 * 
	 * This class represents an invalid register error.
	 */
	class InvalidRegister : public std::runtime_error
	{
		
	};

	/**
	 * @brief Invalid Memory Access
	 * 
	 * This class represents an invalid memory access error.
	 */
	class InvalidMemoryAccess : public std::runtime_error
	{
		
	};

	/**
	 * @brief Invalid Display Access
	 * 
	 * This class represents an invalid display access error.
	 */
	class InvalidDisplayAccess : public std::runtime_error
	{
		
	};

	/**
	 * @brief Invalid Keypad Access
	 * 
	 * This class represents an invalid keypad access error.
	 */
	class InvalidKeypadAccess : public std::runtime_error
	{
		
	};

	/**
	 * @brief Nullptr Instruction
	 * 
	 * This class represents a nullptr instruction error.
	 */
	class NullptrInstruction : public std::runtime_error
	{
		
	};
}

#endif /* _CHIP8_EXCEPTIONS_HPP_ */