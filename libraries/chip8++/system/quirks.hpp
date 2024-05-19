#ifndef _CHIP8_QUIRKS_HPP_
#define _CHIP8_QUIRKS_HPP_

namespace CHIP8
{
	/**
	 * @brief Quirks
	 * 
	 * This class represents the quirks of the CHIP-8 interpreter.
	 * The quirks are the differences between the original CHIP-8 interpreter and the modern CHIP-8 interpreter.
	 *
	 * This class represents a collection of quirks that can be enabled or disabled.
	 * 
	 * The source of these quirks / information can be found at:
	 * https://github.com/chip-8/chip-8-database/blob/master/database/quirks.json
	 */
	class Quirks
	{
	public:
		/**
		 * @brief Catch jump loop
		 * 
		 * This can catch a endless jump loop in the `1NNN` opcode when NNN is PC - 2
		 * 
		 * if true:  Opcodes `1NNN` will catch endless jump loops
		 * if false: Opcodes `1NNN` will not catch endless jump loops
		 */
		bool CatchEndlessJump = true;

		/**
		 * @brief Shift Quirk
		 * 
		 * On most systems the shift opcodes take `vY` as input and stores the shifted version of `vY` into `vX`.
		 * The interpreters for the HP48 took `vX` as both the input and the output, introducing the shift quirk.
		 * 
		 * if true:  Opcodes `8XY6` and `8XYE` take `vX` as both input and output
		 * if false: Opcodes `8XY6` and `8XYE` take `vY` as input and `vX` as output
		 */
		bool Shift = false;

		/**
		 * @brief Load/Store quirk: increment index register by X
		 * 
		 * On most systems storing and retrieving data between registers and memory increments the `i` register
		 * with `X + 1` (the number of registers read or written). So for each register read or writen, the index
		 * register would be incremented. The CHIP-48 interpreter for the HP48 would only increment the `i` register
		 * by `X`, introducing the first load/store quirk.
		 * 
		 * if true:  `FX55` and `FX65` increment the `i` register with `X`
		 * if false: `FX55` and `FX65` increment the `i` register with `X + 1`
		 */
		bool MemoryIncrementByX = false;

		/**
		 * @brief Load/Store quirk: leave index register unchanged
		 * 
		 * On most systems storing and retrieving data between registers and memory increments the `i` register
		 * relative to the number of registers read or written. The Superchip 1.1 interpreter for the HP48 however
		 * did not increment the `i` register at all, introducing the second load/store quirk.
		 * 
		 * if true:  `FX55` and `FX65` leave the `i` register unchanged 
		 * if false: `FX55` and `FX65` increment the `i` register
		 */
		bool MemoryLeaveIunchanged = false;

		/**
		 * @brief Wrap quirk @todo
		 * 
		 * Most systems, when drawing sprites to the screen, will clip sprites at the edges of the screen.
		 * The Octo interpreter, which spawned the XO-CHIP variant of CHIP-8, instead wraps the sprite around to
		 * the other side of the screen. This introduced the wrap quirk.
		 * 
		 * if true:  The `DXYN` opcode wraps around to the other side of the screen when drawing at the edges
		 * if false: The `DXYN` opcode clips when drawing at the edges of the screen
		 */
		bool WrapSprite = false;

		/**
		 * @brief Jump quirk
		 * 
		 * The jump to `<address> + v0` opcode was wronly implemented on all the HP48 interpreters as jump to
		 * `<address> + vX`, introducing the jump quirk.
		 * 
		 * if true:  Opcode `BXNN` jumps to address `XNN + vX`
		 * if false: Opcode `BNNN` jumps to address `NNN + v0`
		 */
		bool Jump = false;

		/**
		 * @brief VBlank quirk
		 * 
		 * The original Cosmac VIP interpreter would wait for vertical blank before each sprite draw. This was
		 * done to prevent sprite tearing on the display, but it would also act as an accidental limit on the
		 * execution speed of the program. Some programs rely on this speed limit to be playable. Vertical blank
		 * happens at 60Hz, and as such its logic be combined with the timers.
		 * 
		 * if true:  Opcode `DXYN` waits for vertical blank (so max 60 sprites drawn per second)
		 * if false: Opcode `DXYN` draws immediately (number of sprites drawn per second only limited to
		 * 			 number of CPU cycles per frame)
		 */
		bool vBlank = true;

		/**
		 * @brief VF reset quirk
		 * 
		 * On the original Cosmac VIP interpreter, `vF` would be reset after each opcode that would invoke
		 * the maths coprocessor. Later interpreters have not copied this behaviour.
		 * 
		 * if true:  Opcodes `8XY1`, `8XY2` and `8XY3` (OR, AND and XOR) will set `vF` to zero after
		 * 	         execution (even if `vF` is the parameter `X`)
		 * if false: Opcodes `8XY1`, `8XY2` and `8XY3` (OR, AND and XOR) will leave `vF` unchanged
		 *           (unless `vF` is the parameter `X`)
		 */
		bool VFreset = true;
	};
}

#endif /* _CHIP8_QUIRKS_HPP_ */