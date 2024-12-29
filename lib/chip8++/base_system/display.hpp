#ifndef _CHIP8_DISPLAY_HPP_
#define _CHIP8_DISPLAY_HPP_

#include <cstdint>
#include <memory>
#include <format>

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
		/** @brief Default Display Width
		 * 
		 * This constant represents the width of the display.
		 */
		static constexpr int DEFAULT_WIDTH = 64;

		/** @brief Default Display Height
		 * 
		 * This constant represents the height of the display.
		 */
		static constexpr int DEFAULT_HEIGHT = 32;

		/** @brief Width and Height of the Display
		 * 
		 * Width and Height of the initialised display buffer.
		*/
		int Width, Height;

		/** @brief Display Buffer
		 * 
		 * This vector stores the display buffer.
		 */
		//std::array<bool, WIDTH * HEIGHT> screenBuffer;
		std::unique_ptr<bool []> screenBuffer;


		/** @brief Update Required
		 * 
		 * This flag indicates if the display needs to be updated.
		 */
		bool UpdateRequired = false;

		/**
		 * @brief Construct a new Display object
		 * 
		 * This constructor initializes the display buffer and clears it.
		 * 
		 * @param height	Height in Pixels of the display buffer
		 * @param width		Width in Pixels of the display buffer
		 */
		Display(int height, int width) : Width(width), Height(height)
		{
			screenBuffer = std::make_unique<bool[]>(Height * Width);
			Clear();
		};
	public:
		/**
		 * @brief Construct a new Display object
		 * 
		 * This constructor initializes the display buffer and clears it.
		 */
		Display() : Width(DEFAULT_WIDTH), Height(DEFAULT_HEIGHT)
		{
			screenBuffer = std::make_unique<bool[]>(Height * Width);
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
		virtual bool IsUpdateRequired()
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
			return Width;
		}

		/**
		 * @brief Get the height of the display
		 * 
		 * @return constexpr int : Returns the height of the display
		 */
		virtual constexpr int GetHeight()
		{
			return Height;
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
			if (x >= Width || y >= Height)
				throw std::out_of_range(std::format("Display::at() : Out of range access (x={}"
					" >= WIDTH={} or y={} >= HEIGHT={})", x, Width, y, Height));
			return screenBuffer[size_t(y * Width + x)];
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
			if (x >= Width || y >= Height)
				throw std::out_of_range(std::format("Display::at() : Out of range access (x={}"
					" >= WIDTH={} or y={} >= HEIGHT={})", x, Width, y, Height));
			return screenBuffer[size_t(y * Width + x)];
		};

		/**
		 * @brief Clear the display
		 * 
		 * This function clears the display buffer.
		 */
		virtual void Clear()
		{
			std::fill(screenBuffer.get(), screenBuffer.get() + Width * Height, false);
			UpdateRequired = true;
		};

		/**
		 * @brief Update the display
		 * 
		 * This function updates the display with the current state of the display buffer.
		 */
		virtual void Update() = 0;
	};
}

#endif /* _DISPLAY_HPP_ */