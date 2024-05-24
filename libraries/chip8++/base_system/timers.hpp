#ifndef _CHIP8_TIMERS_HPP_
#define _CHIP8_TIMERS_HPP_

#include <cstdint>

namespace CHIP8
{
	/**
	 * @brief Timers
	 * 
	 * This class represents the CHIP-8 timers. 
	 * The CHIP-8 has two timers, the delay timer and the sound timer.
	 * The delay timer is used for timing the events of games.
	 * The sound timer is used for sound effects.
	 * 
	 * Both timers count down at 60Hz. 
	 * When the sound timer is non-zero, a sound is played. 
	 * The timers can be set and read.
	 */
    class Timers
	{
	protected:
        uint8_t delayTimer;
        uint8_t soundTimer;
		bool beeperState;
    public:
		/**
		 * @brief Construct a new Timers object
		 * 
		 * This constructor initializes the delay and sound timers to zero.
		 */
		Timers() : delayTimer(0), soundTimer(0), beeperState(false) {};

		/**
		 * @brief Reset the timers
		 * 
		 * This function resets the delay and sound timers to zero.
		 */
		void Reset()
		{
			delayTimer = 0;
			soundTimer = 0;
		}

		/**
		 * @brief Set the delay timer
		 * 
		 * This function sets the delay timer to the value provided.
		 * 
		 * @param value : The value to set the delay timer to
		 */
		void SetDelayTimer(uint8_t value)
		{
			delayTimer = value;
		}

		/**
		 * @brief Get the delay timer
		 * 
		 * This function returns the value of the delay timer.
		 * 
		 * @return uint8_t : The value of the delay timer
		 */
		uint8_t GetDelayTimer()
		{
			return delayTimer;
		}

		/**
		 * @brief Get the sound timer
		 * 
		 * This function returns the value of the sound timer.
		 * 
		 * @return uint8_t : The value of the sound timer
		 */
		void SetSoundTimer(uint8_t value)
		{
			soundTimer = value;
			if (soundTimer > 0)
				UpdateBeeper(true);
			else
				UpdateBeeper(false);
		}

		/**
		 * @brief Get the sound timer
		 * 
		 * This function returns the value of the sound timer.
		 * 
		 * @return uint8_t : The value of the sound timer
		 */
		void DecrementTimers()
		{
			if (delayTimer > 0) {
				delayTimer--;
			}
			if (soundTimer > 0) {
				soundTimer--;
				if (soundTimer == 0) {
					UpdateBeeper(false);
				}
			}
		}

		/**
		 * @brief Get the sound timer
		 * 
		 * This function returns the value of the sound timer.
		 * 
		 * @return uint8_t : The value of the sound timer
		 */
		virtual void UpdateBeeper(bool beeperState)
		{
			this->beeperState = beeperState;
		}

		/**
		 * @brief Get the buzzer state
		 * 
		 * This function returns the state of the buzzer.
		 * 
		 * @return bool : The state of the buzzer
		 */
		virtual bool GetBeeperState()
		{
			return beeperState;
		}
    };
}

#endif /* _TIMERS_HPP_ */