#ifndef SCHIP8_DISPLAY_HPP
#define SCHIP8_DISPLAY_HPP

#include <cstdint>
#include <memory>
#include <algorithm>
#include "base_system/display.hpp"

namespace CHIP8::SCHIP8
{
	/**
	 * @brief SCHIP-8 Display
	 * 
	 * This class represents the display of the SCHIP-8 system.
	 * The SCHIP-8 system has a display of 128x64 pixels.
	 * 
	 * Only the display buffer allocation is overridden, as the
	 * other display base class functions are sufficient.
	 * 
	 * @see CHIP8::Display
	 */
	class SCHIP8Display : public CHIP8::Display
	{
	protected:
		/** @brief Display Width
		 * 
		 * This constant represents the width of the display.
		 */
		static constexpr int WIDTH = 128;

		/** @brief Display Height
		 * 
		 * This constant represents the height of the display.
		 */
		static constexpr int HEIGHT = 64;

		/** @brief High Resolution Mode
		 * 
		 * This flag indicates if the high resolution mode is enabled.
		 */
		bool highResMode = false;
	public:
		/**
		 * @brief Construct a new SCHIP-8 Display object
		 * 
		 * This constructor initializes the display buffer.
		 */
		SCHIP8Display()	: Display(HEIGHT, WIDTH) {}

		/**
		 * @brief Set High Resolution Mode
		 * 
		 * This function sets the high resolution mode.
		 * 
		 * @param highRes High resolution mode flag
		 */
		void SetHighRes(bool highRes)
		{
			highResMode = highRes;
		}

		/**
		 * @brief Get High Resolution Mode
		 * 
		 * This function returns the high resolution mode.
		 * 
		 * @return bool : High resolution mode flag
		 */
		bool GetHighRes()
		{
			return highResMode;
		}

		/**
		 * @brief Scroll Down N Lines
		 * 
		 * This function scrolls the display down by N lines.
		 * 
		 * @param lines Number of lines to scroll down
		 */
		void ScrollDown(int lines)
		{
			lines = lines % (highResMode ? 16 : 8);

			memmove(screenBuffer.get(), screenBuffer.get() + Width * lines, Width * (Height - lines) * sizeof(bool));
			std::fill(screenBuffer.get(), screenBuffer.get() + Width * lines, false);
		}

		/**
		 * @brief Scroll Left 4 Pixels
		 * 
		 * This function scrolls the display left by 4 pixels.
		 */
		void ScrollLeft()
		{
			int pixels = highResMode ? 8 : 4;

			for (int i = 0; i < Height; i++)
			{
				memmove(screenBuffer.get() + i * Width, screenBuffer.get() + i * Width + pixels, (Width - pixels) * sizeof(bool));
				std::fill(screenBuffer.get() + i * Width + Width - pixels, screenBuffer.get() + i * Width + Width, false);
			}
		}

		/**
		 * @brief Scroll Right 4 Pixels
		 * 
		 * This function scrolls the display right by 4 pixels.
		 */
		void ScrollRight()
		{
			int pixels = highResMode ? 8 : 4;

			for (int i = 0; i < Height; i++)
			{
				memmove(screenBuffer.get() + i * Width + pixels, screenBuffer.get() + i * Width, (Width - pixels) * sizeof(bool));
				std::fill(screenBuffer.get() + i * Width, screenBuffer.get() + i * Width + pixels, false);
			}
		}
	};
}

#endif // SCHIP8_DISPLAY_HPP