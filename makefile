#
# Makefile for MEMs 3D Tracking
#
# 'make'       builds both the .elf and .bin
# 'make clean' deletes all compilation outputs
#

# Directories for binaries and libraries
BIN_PATH     = ~/toolchains/gcc-arm-none-eabi-10-2020-q4-major/bin
VFP_LIB_PATH = ~/toolchains/gcc-arm-none-eabi-10-2020-q4-major/arm-none-eabi/lib/thumb/v7e-m+dp/hard

# Toolchain components
CC      = $(BIN_PATH)/arm-none-eabi-gcc
CPPC    = $(BIN_PATH)/arm-none-eabi-g++
AS      = $(BIN_PATH)/arm-none-eabi-as
LD      = $(BIN_PATH)/arm-none-eabi-ld
AR      = $(BIN_PATH)/arm-none-eabi-ar
OBJCOPY = $(BIN_PATH)/arm-none-eabi-objcopy
OBJDUMP = $(BIN_PATH)/arm-none-eabi-objdump

# =================================================================================================================
# Compiler Flags
# =================================================================================================================
# General C/C++ compilation flags
C_FLAGS =   \
	-O0     \
	-g3     \
	-Wall   \
	-Werror \
	-D __CHECK_DEVICE_DEFINES
CPP_FLAGS = \
	-O0     \
	-g3     \
	-Wall   \
	-Werror \
	-fno-exceptions

# Cortex-M7 specific flags to set code execution state (thumb vs ARM) and the target's architecture
C_FLAGS +=   \
	-mthumb  \
	-mcpu=cortex-m7
CPP_FLAGS += \
	-mthumb  \
	-mcpu=cortex-m7

# Cortex-M7 floating point flags
#
# -mfloat-abi=soft/softfp/hard
#     soft
#     The compiler will not generate HW FPU instructions and will instead resort to full SW emulation for floating-
#     point support. This emulation is done through calls to soft float library routines found within the internal
#     SW floating point library GCC was configured to use. The compiler will also generate prologue and epilogue
#     functions to pass the floating point arguments via integer registers (i.e. following the soft float ABI
#     calling convention).
#
#     softfp
#     The compiler will generate HW FPU instructions but will still use the soft float ABI calling convention. Code
#     generated from the soft and softfp float ABIs are compatible with one another because they utilize the same
#     calling convention.
#
#     hard
#     The compiler will generate HW FPU instructions and use the floating point ABI (i.e. floating point function
#     arguments are passed directly into the FPU registers). When using this option, you must specify an FPU using
#     the -mfpu option.
#
# -mfpu=fpv4-sp-d16
#     Specifies the type of floating-point hardware (or emulation) available on the target. In this case, the FPU
#     specified conforms to the fpv5-sp (i.e. single precision variant of the FPv5 architecture, see
#     https://www.keil.com/support/man/docs/armlink/armlink_pge1362075484206.htm for more details) architecture and
#     has 16 double-precision registers (the d16 portion of the argument).
#
# -D __FPU_ENABLED
#     #define for startup code to enable the FPU coprocessor.
C_FLAGS +=            \
	-mfloat-abi=hard  \
	-mfpu=fpv5-sp-d16 \
	-D __FPU_ENABLED
CPP_FLAGS +=          \
	-mfloat-abi=hard  \
	-mfpu=fpv5-sp-d16

# Directories
C_FLAGS +=                                        \
	-I CMSIS/                                     \
	-I device/                                    \
	-I device/registers/                          \
	-I freertos/source/include/                   \
	-I freertos/source/portable/GCC/ARM_CM7/r0p1/ \
	-I src/
CPP_FLAGS +=                                      \
	-I CMSIS/                                     \
	-I device/                                    \
	-I device/registers/                          \
	-I freertos/source/include/                   \
	-I freertos/source/portable/GCC/ARM_CM7/r0p1/ \
	-I freertos/source/portable/MemMang/          \
	-I src/                                       \
	-I src/drivers/

# =================================================================================================================
# Linker Flags
# =================================================================================================================
LD_FLAGS =                      \
	-T linker_script/default.ld \
	-nostartfiles               \
	-Map output/linker_map.map  \
	-print-memory-usage

# This library path is needed for VFP compatible c, gcc, and math libraries when the FPU is used. The GCC ARM
# toolchain's README.txt suggests the use of the thumb/v7e-m+dp/hard multilib
LD_FLAGS += \
	-L $(VFP_LIB_PATH)

# Linker libraries
LD_LIBS += \
	-lc    \
	-lg    \
	-lm

# =================================================================================================================
# Files
# =================================================================================================================
SOURCES = \
	port.c          heap_4.c              croutine.c           event_groups.c \
	list.c          queue.c               stream_buffer.c      tasks.c        \
	timers.c        startup_stm32f767zi.c system_stm32f767zi.c main.cpp       \
	driver_GPIO.cpp onboard_led.cpp

OBJECTS = \
	output/port.o        output/heap_4.o              output/croutine.o           output/event_groups.o \
	output/list.o        output/queue.o               output/stream_buffer.o      output/tasks.o        \
	output/timers.o      output/startup_stm32f767zi.o output/system_stm32f767zi.o output/main.o         \
	output/driver_GPIO.o output/onboard_led.o

# =================================================================================================================
# Rules
# =================================================================================================================
.PHONY: all clean

all: dartlead.elf dartlead.hex dartlead.bin

dartlead.elf : $(OBJECTS)
	@$(LD) $(LD_FLAGS) $^ $(LD_LIBS) -o bin/dartlead.elf

dartlead.hex : bin/dartlead.elf
	@$(OBJCOPY) -O ihex $^ bin/dartlead.hex

dartlead.bin : bin/dartlead.elf
	@$(OBJCOPY) -O binary $^ bin/dartlead.bin

clean:
	-@rm -f output/*.o
	-@rm -f output/*.map
	-@rm -f bin/*.elf
	-@rm -f bin/*.hex
	-@rm -f bin/*.bin

# =================================================================================================================
# FreeRTOS File Rules
# =================================================================================================================
output/port.o : freertos/source/portable/GCC/ARM_CM7/r0p1/port.c
	@$(CC) $(C_FLAGS) -c $< -o $@
output/heap_4.o : freertos/source/portable/MemMang/heap_4.c
	@$(CC) $(C_FLAGS) -c $< -o $@
output/croutine.o : freertos/source/croutine.c
	@$(CC) $(C_FLAGS) -c $< -o $@
output/event_groups.o : freertos/source/event_groups.c
	@$(CC) $(C_FLAGS) -c $< -o $@
output/list.o : freertos/source/list.c
	@$(CC) $(C_FLAGS) -c $< -o $@
output/queue.o : freertos/source/queue.c
	@$(CC) $(C_FLAGS) -c $< -o $@
output/stream_buffer.o : freertos/source/stream_buffer.c
	@$(CC) $(C_FLAGS) -c $< -o $@
output/tasks.o : freertos/source/tasks.c
	@$(CC) $(C_FLAGS) -c $< -o $@
output/timers.o : freertos/source/timers.c
	@$(CC) $(C_FLAGS) -c $< -o $@

# =================================================================================================================
# Dartlead File Rules
# =================================================================================================================
output/startup_stm32f767zi.o : startup/startup_stm32f767zi.c
	@$(CC) $(C_FLAGS) -c $< -o $@
output/system_stm32f767zi.o : device/system_stm32f767zi.c
	@$(CC) $(C_FLAGS) -c $< -o $@
output/main.o : src/main.cpp
	@$(CPPC) $(CPP_FLAGS) -c $< -o $@
output/driver_GPIO.o : src/drivers/driver_GPIO.cpp
	@$(CPPC) $(CPP_FLAGS) -c $< -o $@
output/onboard_led.o : src/drivers/onboard_led.cpp
	@$(CPPC) $(CPP_FLAGS) -c $< -o $@