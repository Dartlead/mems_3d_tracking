#
# Makefile for MEMs 3D Tracking
#
# 'make'       builds both the .elf and .bin
# 'make clean' deletes all compilation outputs
#

# Directories for binaries and libraries
BIN_PATH     = ~/Toolchains/gcc-arm-none-eabi-10-2020-q4-major/bin
VFP_LIB_PATH = ~/Toolchains/gcc-arm-none-eabi-10-2020-q4-major/arm-none-eabi/lib/thumb/v7e-m+dp/hard

# Toolchain components
CC      = $(BIN_PATH)/arm-none-eabi-gcc
CPPC    = $(BIN_PATH)/arm-none-eabi-g++
AS      = $(BIN_PATH)/arm-none-eabi-as
LD      = $(BIN_PATH)/arm-none-eabi-ld
AR      = $(BIN_PATH)/arm-none-eabi-ar
OBJCOPY = $(BIN_PATH)/arm-none-eabi-objcopy
OBJDUMP = $(BIN_PATH)/arm-none-eabi-objdump

# ==================================================================================================
# Compiler Flags
# ==================================================================================================
# General C/C++ compilation flags
C_FLAGS =      \
	-O0        \
	-g3        \
	-Wall      \
	-Werror    \
	-std=c99   \
	-D __CHECK_DEVICE_DEFINES
CPP_FLAGS =    \
	-O0        \
	-g3        \
	-Wall      \
	-Werror    \
	-std=c++11 \
	-fno-exceptions

# Cortex-M7 specific flags to set code execution state (thumb vs ARM) and the target's architecture
CM7_FLAGS =  \
	-mthumb  \
	-mcpu=cortex-m7

# Cortex-M7 floating point flags
#
# -mfloat-abi=soft/softfp/hard
#     soft
#     The compiler will not generate HW FPU instructions and will instead resort to full SW
#     emulation for floating-point support. This emulation is done through calls to soft float
#     library routines found within the internal SW floating point library GCC was configured to
#     use. The compiler will also generate prologue and epilogue functions to pass the floating
#     point arguments via integer registers (i.e. following the soft float ABI calling convention).
#
#     softfp
#     The compiler will generate HW FPU instructions but will still use the soft float ABI calling
#     convention. Code generated from the soft and softfp float ABIs are compatible with one
#     another because they utilize the same calling convention.
#
#     hard
#     The compiler will generate HW FPU instructions and use the floating point ABI (i.e. floating
#     point function arguments are passed directly into the FPU registers). When using this option,
#     you must specify an FPU using the -mfpu option.
#
# -mfpu=fpv4-sp-d16
#     Specifies the type of floating-point hardware (or emulation) available on the target. In this
#     case, the FPU specified conforms to the fpv5-sp (i.e. single precision variant of the FPv5
#     architecture, see https://www.keil.com/support/man/docs/armlink/armlink_pge1362075484206.htm
#     for more details) architecture and has 16 double-precision registers (the d16 portion of the
#     argument).
#
# -D __FPU_ENABLED
#     #define for startup code to enable the FPU coprocessor.
CM7_FLAGS +=          \
	-mfloat-abi=hard  \
	-mfpu=fpv5-sp-d16 \
	-D __FPU_ENABLED

# Directories
INCLUDE_DIRS =                                        \
	-I lib/CMSIS/                                     \
	-I src/device/                                    \
	-I src/device/registers/                          \
	-I lib/freertos/source/include/                   \
	-I lib/freertos/source/portable/GCC/ARM_CM7/r0p1/ \
	-I lib/freertos/source/portable/MemMang/          \
	-I lib/libdartlead                                \
	-I src/                                           \
	-I src/drivers/                                   \
	-I src/hw/

# ==================================================================================================
# Linker Flags
# ==================================================================================================
LD_FLAGS =                                                \
	-T toolchain_support/linker_script/c_linker_script.ld \
	-nostartfiles                                         \
	-Map bin/linker_map.map                               \
	-print-memory-usage

# This library path is needed for VFP compatible c, gcc, and math libraries when the FPU is used.
# The GCC ARM toolchain's README.txt suggests the use of the thumb/v7e-m+dp/hard multilib
LD_FLAGS += \
	-L $(VFP_LIB_PATH)

# Linker libraries
LD_LIBS =    \
	-lc      \
	-lstdc++ \
	-lg      \
	-lm

# ==================================================================================================
# Files
# ==================================================================================================
SOURCES = \
	port.c                           heap_4.c                         croutine.c            \
	event_groups.c                   list.c                           queue.c               \
	stream_buffer.c                  tasks.c                          timers.c              \
	startup_stm32f767zi.c            system_stm32f767zi.c             main.cpp              \
	driver_GPIO.cpp                  onboard_led.cpp                  dartlead_assert.c

OBJECTS = \
	bin/output/port.o                bin/output/heap_4.o              bin/output/croutine.o \
	bin/output/event_groups.o        bin/output/list.o                bin/output/queue.o    \
	bin/output/stream_buffer.o       bin/output/tasks.o               bin/output/timers.o   \
	bin/output/startup_stm32f767zi.o bin/output/system_stm32f767zi.o  bin/output/main.o     \
	bin/output/driver_GPIO.o         bin/output/onboard_led.o         bin/output/dartlead_assert.o

# ==================================================================================================
# Rules
# ==================================================================================================
.PHONY: all clean

all: dartlead.elf dartlead.hex dartlead.bin

dartlead.elf : $(OBJECTS)
	@$(LD) $(LD_FLAGS) $^ $(LD_LIBS) -o bin/dartlead.elf

dartlead.hex : bin/dartlead.elf
	@$(OBJCOPY) -O ihex $^ bin/dartlead.hex

dartlead.bin : bin/dartlead.elf
	@$(OBJCOPY) -O binary $^ bin/dartlead.bin

clean:
	-@rm -f bin/output/*.o
	-@rm -f bin/output/*.map
	-@rm -f bin/*.elf
	-@rm -f bin/*.hex
	-@rm -f bin/*.bin

# ==================================================================================================
# FreeRTOS File Rules
# ==================================================================================================
bin/output/port.o : lib/freertos/source/portable/GCC/ARM_CM7/r0p1/port.c
	@$(CC) $(CM7_FLAGS) $(C_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/heap_4.o : lib/freertos/source/portable/MemMang/heap_4.c
	@$(CC) $(CM7_FLAGS) $(C_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/croutine.o : lib/freertos/source/croutine.c
	@$(CC) $(CM7_FLAGS) $(C_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/event_groups.o : lib/freertos/source/event_groups.c
	@$(CC) $(CM7_FLAGS) $(C_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/list.o : lib/freertos/source/list.c
	@$(CC) $(CM7_FLAGS) $(C_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/queue.o : lib/freertos/source/queue.c
	@$(CC) $(CM7_FLAGS) $(C_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/stream_buffer.o : lib/freertos/source/stream_buffer.c
	@$(CC) $(CM7_FLAGS) $(C_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/tasks.o : lib/freertos/source/tasks.c
	@$(CC) $(CM7_FLAGS) $(C_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/timers.o : lib/freertos/source/timers.c
	@$(CC) $(CM7_FLAGS) $(C_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

# ==================================================================================================
# Dartlead File Rules
# ==================================================================================================
bin/output/startup_stm32f767zi.o : src/startup/startup_stm32f767zi.c
	@$(CC) $(CM7_FLAGS) $(C_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/system_stm32f767zi.o : src/device/system_stm32f767zi.c
	@$(CC) $(CM7_FLAGS) $(C_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/main.o : src/main.cpp
	@$(CPPC) $(CM7_FLAGS) $(CPP_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/driver_GPIO.o : src/drivers/driver_GPIO.cpp
	@$(CPPC) $(CM7_FLAGS) $(CPP_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/onboard_led.o : src/hw/onboard_led.cpp
	@$(CPPC) $(CM7_FLAGS) $(CPP_FLAGS) $(INCLUDE_DIRS) -c $< -o $@
bin/output/dartlead_assert.o : lib/libdartlead/dartlead_assert.c
	@$(CC) $(CM7_FLAGS) $(C_FLAGS) $(INCLUDE_DIRS) -c $< -o $@