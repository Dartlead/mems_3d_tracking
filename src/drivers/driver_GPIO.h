#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

#include <cstdint>
#include "stm32f767zi.h"

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
	  mode_alt_func_0
	, mode_alt_func_1
	, mode_alt_func_2
	, mode_alt_func_3
	, mode_alt_func_4
	, mode_alt_func_5
	, mode_alt_func_6
	, mode_alt_func_7
	, mode_alt_func_8
	, mode_alt_func_9
	, mode_alt_func_10
	, mode_alt_func_11
	, mode_alt_func_12
	, mode_alt_func_13
	, mode_alt_func_14
	, mode_alt_func_15
	, mode_input
	, mode_output
	, mode_analog
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

enum class GPIO_status_t : uint8_t {
	  GPIO_status_ok
	, GPIO_status_error
};

class GPIO {
private:
	port_t         port_letter;
	GPIO_TypeDef * port_base_addr;
	pin_t          num;
	mode_t         mode;
	output_type_t  output_type;
	output_speed_t output_speed;
	pull_t         pull;
	bool           locked;

public:
	GPIO(port_t         const port_init
		, pin_t          const pin_init
		, mode_t         const mode_init
		, output_type_t  const output_type_init
		, output_speed_t const output_speed_init
		, pull_t         const pull_init
	);

	GPIO_status set_mode(mode const pin_mode);
	GPIO_status set_output_type(output_type const pin_output_type);
	GPIO_status set_output_speed(output_speed const pin_output_speed);
	GPIO_status set_pull(pull const pin_pull);

	GPIO_status lock_config(void);
	GPIO_status is_locked(bool &locked);

	GPIO_status write(uint32_t const val);
	GPIO_status write_atomic(uint32_t const val);
	GPIO_status read(uint32_t &val);
	GPIO_status toggle(void);
};

#endif /* DRIVER_GPIO_H */

/* EOF */
