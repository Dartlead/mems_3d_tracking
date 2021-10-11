#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

#include <cstdint>
#include "stm32f767zi.h"

namespace GPIO
{
	enum class port_t : uint8_t {
		  port_A
		, port_B
		, port_C
		, port_D
		, port_E
		, port_F
		, port_G
		, port_H
		, port_I
		, port_J
		, port_K
	};

	//Maybe get rid of this in place of just using a normal uint
	enum class pin_t : uint8_t {
		  pin_0
		, pin_1
		, pin_2
		, pin_3
		, pin_4
		, pin_5
		, pin_6
		, pin_7
		, pin_8
		, pin_9
		, pin_10
		, pin_11
		, pin_12
		, pin_13
		, pin_14
		, pin_15
	};

	enum class mode_t : uint8_t {
		  alt_func_0
		, alt_func_1
		, alt_func_2
		, alt_func_3
		, alt_func_4
		, alt_func_5
		, alt_func_6
		, alt_func_7
		, alt_func_8
		, alt_func_9
		, alt_func_10
		, alt_func_11
		, alt_func_12
		, alt_func_13
		, alt_func_14
		, alt_func_15
		, input
		, output
		, analog
	};

	enum class output_type_t : uint8_t {
		  output_type_push_pull
		, output_type_open_drain
	};

	enum class output_speed_t : uint8_t {
		  output_speed_low
		, output_speed_medium
		, output_speed_high
		, output_speed_very_high
	};

	enum class pull_t : uint8_t {
		  pull_none
		, pull_up
		, pull_down
	};

	enum class status_t : uint8_t {
		  ok
		, invalid_pin_mode
	};

	class pin {
	private:
		port_t         port;
		GPIO_TypeDef * port_base_addr;
		pin_t          number;
		mode_t         mode;
		output_type_t  output_type;
		output_speed_t output_speed;
		pull_t         pull;
		bool           locked;

	public:
		pin(  port_t         const pin_port
			, pin_t          const pin_number
			, mode_t         const pin_mode
			, output_type_t  const pin_output_type
			, output_speed_t const pin_output_speed
			, pull_t         const pin_pull
		);

		status_t set_mode(mode_t const pin_mode);
		status_t set_output_type(output_type_t const pin_output_type);
		status_t set_output_speed(output_speed_t const pin_output_speed);
		status_t set_pull(pull_t const pin_pull);

		status_t lock_config(void);
		status_t is_locked(bool &locked);

		status_t write(uint32_t const val);
		status_t write_atomic(uint32_t const val);
		status_t read(uint32_t &val);
		status_t toggle(void);
	};
}

#endif /* DRIVER_GPIO_H */

/* EOF */
