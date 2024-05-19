#ifndef _CHIP8_DISPLAY_HPP_
#define _CHIP8_DISPLAY_HPP_

#include <array>
#include <cstdint>
#include <format>
#include "exceptions.hpp"

namespace CHIP8
{
	/**
	 * @brief Display
	 * 
	 * This class represents the display of the CHIP-8 system.
	 */
	class Display
	{
	protected:
		/** @brief Display Width
		 * 
		 * This constant represents the width of the display.
		 */
		static constexpr int WIDTH = 64;

		/** @brief Display Height
		 * 
		 * This constant represents the height of the display.
		 */
		static constexpr int HEIGHT = 32;

		/** @brief Display Buffer
		 * 
		 * This vector stores the display buffer.
		 */
		std::array<bool, WIDTH * HEIGHT> screenBuffer;

		/** @brief Update Required
		 * 
		 * This flag indicates if the display needs to be updated.
		 */
		bool UpdateRequired = false;
	public:
		/**
		 * @brief Construct a new Display object
		 * 
		 * This constructor initializes the display buffer and clears it.
		 */
		Display()
		{
			Clear();
		};

		/**
		 * @brief Destroy the Display object
		 * 
		 * This destructor deletes the display buffer.
		 */
		virtual ~Display() = default;

		/**
		 * @brief Get the value of the Update Required flag
		 * 
		 * @return bool : Returns true if the display needs to be updated
		 */
		virtual bool GetUpdateRequired()
		{
			return UpdateRequired;
		}

		/**
		 * @brief Set the value of the Update Required flag
		 * 
		 * This function sets the value of the Update Required flag.
		 */
		virtual void SetUpdateRequired()
		{
			UpdateRequired = true;
		}

		/**
		 * @brief Get the width of the display
		 * 
		 * @return constexpr int : Returns the width of the display
		 */
		virtual constexpr int GetWidth()
		{
			return WIDTH;
		}

		/**
		 * @brief Get the height of the display
		 * 
		 * @return constexpr int : Returns the height of the display
		 */
		virtual constexpr int GetHeight()
		{
			return HEIGHT;
		}

		/**
		 * @brief Access a pixel on the display
		 * 
		 * This function accesses a pixel on the display buffer.
		 * 
		 * @param x  X coordinate
		 * @param y  Y coordinate
		 * @return const bool& : Returns the value of the pixel 
		 */
		virtual const bool &at(uint8_t x, uint8_t y) const
		{
			if (x >= WIDTH || y >= HEIGHT)
				throw std::out_of_range(std::format("Display::at() : Out of range access (x={}"
					" >= WIDTH={} or y={} >= HEIGHT={})", x, WIDTH, y, HEIGHT));
			return screenBuffer[y * WIDTH + x];
		};

		/**
		 * @brief Access a pixel on the display
		 * 
		 * This function accesses a pixel on the display buffer.
		 * 
		 * @param x  X coordinate
		 * @param y  Y coordinate
		 * @return bool& : Returns the value of the pixel 
		 */
		virtual bool &at(uint8_t x, uint8_t y)
		{
			if (x >= WIDTH || y >= HEIGHT)
				throw std::out_of_range(std::format("Display::at() : Out of range access (x={}"
					" >= WIDTH={} or y={} >= HEIGHT={})", x, WIDTH, y, HEIGHT));
			return screenBuffer[y * WIDTH + x];
		};

		/**
		 * @brief Clear the display
		 * 
		 * This function clears the display buffer.
		 */
		virtual void Clear()
		{
			screenBuffer.fill(false);
			UpdateRequired = true;
		};

		/**
		 * @brief Update the display
		 * 
		 * This function updates the display with the current state of the display buffer.
		 */
		virtual void Update()
		{

		};
	};
}

#endif /* _DISPLAY_HPP_ */