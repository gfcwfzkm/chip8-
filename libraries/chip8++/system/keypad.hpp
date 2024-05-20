#ifndef _CHIP8_KEYPAD_HPP_
#define _CHIP8_KEYPAD_HPP_

#include <iostream>
#include <array>

namespace CHIP8
{
	/**
	 * @brief Keypad Interface
	 * 
	 * This class represents the CHIP-8 keypad.
	 * The keypad has 16 keys, 0-9 and A-F.
	 */
	class Keypad
	{
	protected:
		std::array<bool, 16> keys;
	public:
		Keypad() : keys({false}) {};

		virtual ~Keypad() = default;

		/**
		 * @brief Enum for the CHIP-8 keypad
		 * 
		 * This enum represents the CHIP-8 keypad.
		 * The keypad has 16 keys, 0-9 and A-F.
		 */
		enum Key
		{
			KEY_0 = 0, KEY_1, KEY_2, KEY_3,
			KEY_4, KEY_5, KEY_6, KEY_7,
			KEY_8, KEY_9, KEY_A, KEY_B,
			KEY_C, KEY_D, KEY_E, KEY_F,
			KEY_INVALID
		};

		/**
		 * @brief Check if a key is pressed
		 * 
		 * This function checks if a key is pressed.
		 * 
		 * @param key : The key to check
		 * @return true : The key is pressed
		 * @return false : The key is not pressed
		 */
		virtual bool IsKeyPressed(enum Key key)
		{
			return keys[key];
		}

		/**
		 * @brief Wait for a key press
		 * 
		 * This function waits for a key press.
		 * 
		 * @return uint8_t : The key that was pressed
		 */
		virtual enum Key WaitForKeyPress()
		{
			while(true)
			{
				for (int i = 0; i < 16; i++)
				{
					if (keys[i])
					{
						return static_cast<enum Key>(i);
					}
				}
				UpdateKeys();
			}
		}

		virtual void UpdateKeys() = 0;
	};    
} // namespace CHIP8


#endif /* _CHIP8_KEYPAD_HPP_ */