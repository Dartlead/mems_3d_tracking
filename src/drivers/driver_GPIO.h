#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

#include <cstdint>

enum class port : uint8_t {
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

enum class pin : uint8_t {
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

enum class mode : uint8_t {
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

enum class output_type : uint8_t {
	  output_type_push_pull
	, output_type_open_drain
};

enum class output_speed : uint8_t {
	  output_speed_low
	, output_speed_medium
	, output_speed_high
	, output_speed_very_high
};

enum class pull : uint8_t {
	  pull_none
	, pull_up
	, pull_down
};

class GPIO {
private:
	port         port_letter;
	pin          pin_num;
	mode         pin_mode;
	output_type  pin_output_type;
	output_speed pin_output_speed;
	pull         pin_pull;

public:
	GPIO( port         const port_letter
		, pin          const pin_num
		, mode         const pin_mode
		, output_type  const pin_output_type
		, output_speed const pin_output_speed
		, pull         const pin_pull
	);

	int setupPin(int create); //Setup pin (ARGS create: whether to create or destroy pin (1 for create, 0 for destroy))
	int setDirection(int direction); //Set pin direction (ARGS direction: either 1 for output or 0 for input)
	int readValue(void); //Read current value of the pin (ARGS *level: Address of string type variable, run command with readValue(&STRING_VAR) and the result will be stored in STRING_VAR) (only works if _direction is 0 (input))
	int writeValue(int level); //Write pin (ARGS level: level to set pin, either 0 for LOW or 1 for HIGH) (only works if _direction is 1 (output))
};

#endif /* DRIVER_GPIO_H */

/* EOF */
