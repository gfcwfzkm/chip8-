#ifndef _CHIP8_HPP_
#define _CHIP8_HPP_

#include <cstdint>
#include <fstream>
#include <ios>
#include <memory>
#include <thread>
#include <chrono>
#include <conio.h>
#include <map>

#include "system/cpu.hpp"

namespace CHIP8Demo
{
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
	public:
		Chip8Test();
		Chip8Test(const std::string &romPath) : Chip8Test() { loadRom(romPath); }

		void loadRom(const std::string &filename);
		void playRom();
		CHIP8::CPU *getCpu() { return cpu; }
	};

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
		virtual ~Keyboard() = default;

		bool IsKeyPressed(enum Key key) override
		{
			if (keys[key])
			{
				keys[key] = false;
				return true;
			}
			return false;
		}

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
			updateKeys();
						
			return Key::KEY_INVALID;
		}

		void updateKeys() override
		{
			if (kbhit())
			{
				const int key = getch();
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
			const std::array<unsigned char,8> screenBorderCharsBEEP = {0xC9, 0xCD, 0xBB, 0xBA, 0xBA, 0xC8, 0xCD, 0xBC};
			const std::array<unsigned char,8> screenBorderCharsNORMAL = {0xDA, 0xC4, 0xBF, 0xB3, 0xB3, 0xC0, 0xC4, 0xD9};

			std::string textScreen;
			const auto &screenBorder = optionalFakeBeep ? screenBorderCharsBEEP : screenBorderCharsNORMAL;

			textScreen.push_back(screenBorder[TOP_LEFT]);
			for (int i = 0; i < WIDTH; i++)
				textScreen.push_back(screenBorder[TOP]);
			textScreen.push_back(screenBorder[TOP_RIGHT]);
			textScreen.push_back('\n');

			for (int y = 0; y < HEIGHT; y += 2)
			{
				textScreen.push_back(screenBorder[LEFT]);
				for (int x = 0; x < WIDTH; x++)
				{
					if ((screenBuffer[y * WIDTH + x]) && (screenBuffer[(y+1) * WIDTH + x]))
					{
						textScreen.push_back('\xDB');
					}
					else if (screenBuffer[y * WIDTH + x])
					{
						textScreen.push_back('\xDF');
					}
					else if (screenBuffer[(y+1) * WIDTH + x])
					{
						textScreen.push_back('\xDC');
					}
					else
					{
						textScreen.push_back(' ');
					}
				}
				textScreen.push_back(screenBorder[RIGHT]);
				textScreen.push_back('\n');
			}

			textScreen.push_back(screenBorder[BOTTOM_LEFT]);
			for (int i = 0; i < WIDTH; i++)
				textScreen.push_back(screenBorder[BOTTOM]);
			textScreen.push_back(screenBorder[BOTTOM_RIGHT]);

			std::cout << "\033[0;0H";
			std::cout << textScreen;

			UpdateRequired = false;
		}
	};
}

#endif /* _CHIP8_HPP_ */