#ifndef SCHIP8_DISPLAY_HPP
#define SCHIP8_DISPLAY_HPP

#include <cstdint>
#include <memory>
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

		/**
		 * @brief Allocate the display buffer
		 * 
		 * This function allocates the display buffer.
		 * Called by the constructor of the base class.
		 */
		virtual void allocateDisplay() override
		{
			screenBuffer = std::make_unique<bool[]>(WIDTH * HEIGHT);
		}

		bool highResMode = false;
	public:
		void setHighRes(bool highRes)
		{
			highResMode = highRes;
		}

		bool getHighRes()
		{
			return highResMode;
		}
	};
}

#endif // SCHIP8_DISPLAY_HPP