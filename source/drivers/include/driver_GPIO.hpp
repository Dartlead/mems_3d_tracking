#ifndef DRIVER_GPIO_HPP
#define DRIVER_GPIO_HPP

#include <cstdint>

namespace GPIO {
	enum class GPIO_PORT : std::uint32_t {
		  A = 0
		, B = 1
		, C = 2
		, D = 3
		, E = 4
		, F = 5
		, G = 6
		, H = 7
		, I = 8
		, J = 9
		, K = 10
	};

	enum class GPIO_MODE : std::uint32_t {
		  ALT_FUNC_0  = 0
		, ALT_FUNC_1  = 1
		, ALT_FUNC_2  = 2
		, ALT_FUNC_3  = 3
		, ALT_FUNC_4  = 4
		, ALT_FUNC_5  = 5
		, ALT_FUNC_6  = 6
		, ALT_FUNC_7  = 7
		, ALT_FUNC_8  = 8
		, ALT_FUNC_9  = 9
		, ALT_FUNC_10 = 10
		, ALT_FUNC_11 = 11
		, ALT_FUNC_12 = 12
		, ALT_FUNC_13 = 13
		, ALT_FUNC_14 = 14
		, ALT_FUNC_15 = 15
		, INPUT       = 16
		, OUTPUT      = 16
		, ALT_FUNC    = 18
		, ANALOG      = 19
	};

	enum class GPIO_OUTPUT_TYPE : std::uint32_t {
		  PUSH_PULL  = 0
		, OPEN_DRAIN = 1
	};

	enum class GPIO_OUTPUT_SPEED : std::uint32_t {
		  LOW       = 0
		, MEDIUM    = 1
		, HIGH      = 2
		, VERY_HIGH = 3
	};

	enum class GPIO_PULL : std::uint32_t {
		  OFF  = 0
		, UP   = 1
		, DOWN = 2
	};

	class GPIO_base {
	public:
		GPIO_base();

		//!# Sets the mode of a GPIO pin
		void mode(std::uint32_t const pin, GPIO_MODE const mode) const;

		//!# Sets the pull-up/down for a GPIO pin
		void pull(std::uint32_t const pin, GPIO_PULL const pull) const;

		//!# Reads an input GPIO pin
		bool read(std::uint32_t const pin) const;

		//!# Writes a '1' or '0' to an output GPIO pin
		void write(std::uint32_t const pin, bool const val) const;

		//!# Toggles an output GPIO pin
		void toggle(std::uint32_t const pin) const;

		//!# Locks a GPIO pin's configuration from changing until after a system reset
		void lock(std::uint32_t const pin) const;

		//!# Checks whether a GPIO pin is locked
		bool is_locked(std::uint32_t const pin) const;
	};
}

#endif /* DRIVER_GPIO_HPP */

/* EOF */
