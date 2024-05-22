#ifndef _CHIP8_HPP_
#define _CHIP8_HPP_

#include <cstdint>
#include <fstream>
#include <ios>
#include <memory>
#include <thread>
#include <chrono>
#include <map>
#include "system/cpu.hpp"
#include "Instructions/Instruction.hpp"
#include "ch8_platform_specific.h"

namespace CHIP8Demo
{
	/**
	 * @brief Keyboard
	 * 
	 * This class represents a keyboard.
	 */
	class Keyboard : public CHIP8::Keypad
	{
		std::map<int, enum Key> keyMap = {
			{ '1', Key::KEY_1 },
			{ '2', Key::KEY_2 },
			{ '3', Key::KEY_3 },
			{ '4', Key::KEY_C },
			{ 'q', Key::KEY_4 },
			{ 'w', Key::KEY_5 },
			{ 'e', Key::KEY_6 },
			{ 'r', Key::KEY_D },
			{ 'a', Key::KEY_7 },
			{ 's', Key::KEY_8 },
			{ 'd', Key::KEY_9 },
			{ 'f', Key::KEY_E },
			{ 'y', Key::KEY_A },
			{ 'x', Key::KEY_0 },
			{ 'c', Key::KEY_B },
			{ 'v', Key::KEY_F }
		};
	public:
		Keyboard() : CHIP8::Keypad() {};

		/**
		 * @brief IsKeyPressed
		 * 
		 * This function checks if a key is pressed.
		 * 
		 * @param key The key to check.
		 * @return bool : true if the key is pressed, false otherwise.
		 */
		bool IsKeyPressed(enum Key key) override
		{
			if (keys[key])
			{
				keys[key] = false;
				return true;
			}
			return false;
		}

		/**
		 * @brief WaitForKeyPress
		 * 
		 * This function waits for a key to be pressed.
		 * 
		 * @return enum Key : The key that was pressed.
		 */
		enum Key WaitForKeyPress() override
		{
			for (int i = 0; i < 16; i++)
			{
				if (keys[i])
				{
					keys[i] = false;
					return static_cast<enum Key>(i);
				}
			}
			UpdateKeys();
						
			return Key::KEY_INVALID;
		}

		/**
		 * @brief UpdateKeys
		 * 
		 * This function updates the keys.
		 */
		void UpdateKeys() override
		{
			if (CH8_KBHIT())
			{
				const int key = CH8_GETCH();
				if (keyMap.find(key) != keyMap.end())
				{
					keys[keyMap[key]] = true;
				}
			}
		}
	};
	
	/**
	 * @brief Display
	 * 
	 * This class represents a display.
	 */
	class Display : public CHIP8::Display
	{
		bool beep = false;
	public:
		void setBeep(bool value)
		{
			beep = value;
		}

		void Update() override
		{
			Update(beep);
		}

		/**
		 * @brief Update the display on the console
		 * 
		 * This function updates the display with the current state of the display buffer 
		 * on the console. It uses the following characters to represent the display:
		 */
		void Update(bool optionalFakeBeep = false)
		{
			enum screenBorderType {TOP_LEFT = 0, TOP, TOP_RIGHT, LEFT, RIGHT, BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT};
			const std::array<std::string,8> screenBorderCharsBEEP = {
				CH8_FRAMEB_UPL,
				CH8_FRAMEB_UP,
				CH8_FRAMEB_UPR,
				CH8_FRAMEB_LEFT,
				CH8_FRAMEB_RGHT,
				CH8_FRAMEB_DNL,
				CH8_FRAMEB_DOWN,
				CH8_FRAMEB_DNR
			};
			const std::array<std::string,8> screenBorderCharsNORMAL = {
				CH8_FRAME_UPL,
				CH8_FRAME_UP,
				CH8_FRAME_UPR,
				CH8_FRAME_LEFT,
				CH8_FRAME_RGHT,
				CH8_FRAME_DNL,
				CH8_FRAME_DOWN,
				CH8_FRAME_DNR
			};

			std::string textScreen;
			const auto &screenBorder = optionalFakeBeep ? screenBorderCharsBEEP : screenBorderCharsNORMAL;

			textScreen.append(screenBorder[TOP_LEFT]);
			for (int i = 0; i < WIDTH; i++)
				textScreen.append(screenBorder[TOP]);
			textScreen.append(screenBorder[TOP_RIGHT]);
			textScreen.append("\n");

			for (int y = 0; y < HEIGHT; y += 2)
			{
				textScreen.append(screenBorder[LEFT]);
				for (int x = 0; x < WIDTH; x++)
				{
					if ((screenBuffer[y * WIDTH + x]) && (screenBuffer[(y+1) * WIDTH + x]))
					{
						textScreen.append(CH8_BOTHPIXEL);
					}
					else if (screenBuffer[y * WIDTH + x])
					{
						textScreen.append(CH8_UPPERPIXEL);
					}
					else if (screenBuffer[(y+1) * WIDTH + x])
					{
						textScreen.append(CH8_LOWERPIXEL);
					}
					else
					{
						textScreen.append(CH8_NOPIXEL);
					}
				}
				textScreen.append(screenBorder[RIGHT]);
				textScreen.append("\n");
			}

			textScreen.append(screenBorder[BOTTOM_LEFT]);
			for (int i = 0; i < WIDTH; i++)
				textScreen.append(screenBorder[BOTTOM]);
			textScreen.append(screenBorder[BOTTOM_RIGHT]);

			std::cout << "\033[0;0H";
			std::cout << textScreen;

			UpdateRequired = false;
		}
	};

	/**
	 * @brief Chip8Test
	 * 
	 * This class represents a CHIP-8 test.
	 * It is a basic example on how this CHIP8 library can be used by using the 
	 * default terminal as both screen and keyboard input.
	 */
	class Chip8Test
	{
		CHIP8::CPU *cpu;
		std::shared_ptr<Keyboard> keyboard;
		std::shared_ptr<Display> display;
	public:
		Chip8Test();
		Chip8Test(const std::string &romPath) : Chip8Test() { loadRom(romPath); }

		void loadRom(const std::string &filename);
		void playRom();
		CHIP8::CPU *getCpu() { return cpu; }
	};


}

#endif /* _CHIP8_HPP_ */