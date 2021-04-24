## MEMS 3D Tracking

Dead Reckoning project for STM32F767ZI (Nucleo).

### Tool Versioning

This project uses OpenOCD 0.11.0-rc2.

This project uses FreeRTOS V12.00 (2020 release).

This project uses GNU ARM Embedded Toolchain 10-2020-q4-major.

### How to get Tools

#### OpenOCD

[0.11.0-rc2 Repository](https://sourceforge.net/p/openocd/code/ci/v0.11.0-rc2/tree/)

Perform the following commands

```
# Make sure you have the dependencies
sudo apt-get install make
sudo apt-get install libtool
sudo apt-get install pkg-config
sudo apt-get install autoconfg
sudo apt-get install automake
sudo apt-get install texinfo
sudo apt-get install libusb-1.o

git clone git://git.code.sf.net/p/openocd/code openocd-code
cd openocd-code
./bootstrap
./configure --enable-stlink --enable-cmsis-dap-v2
make
sudo make install
```

### Directory Hierarchy

#### bin/

The directory containing the binaries for programming the STM32F767ZI. Options include .bin, .elf and .hex.

#### CMSIS/

#### device/

#### device/registers/

#### freertos/source/

#### linker_script/

#### openocd_debug/

The directory containing:

**stm32f767zi_stlink.cfg** - The .cfg file for getting OpenOCD to work with the STM32F767ZI over the onboard ST-Link V2-1.

**mem_helper.tcl** - Functions for easier viewing of memory during runtime.

#### output/

#### source/

#### source/drivers/

#### startup/