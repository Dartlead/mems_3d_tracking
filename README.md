## MEMS 3D Tracking

Dead Reckoning project for STM32F767ZI (Nucleo).

<br>

### Tool Versioning

Toolchains used by this project:

+ OpenOCD 0.11.0
+ FreeRTOS V10.4.3
+ GNU ARM Embedded Toolchain 10-2020-q4-major

<br>

### Directory Hierarchy

```
mems_3d_tracking
│   README.md
│   makefile
│   .gitignore
│
└───bin
│   │   dartlead.bin
│   │   dartlead.elf
│   │   dartlead.hex
│   │   linker_map.map
│   │
│   └───output
|       Compiled object files.
│   
└───lib
|   |
│   └───CMSIS
|   |   ARM provided header files for compiler-specific intrinsics.
|   |
│   └───freertos
|   |   Source files for FreeRTOS V10.4.3.
|   |
│   └───libdartlead
|       Source files for custom dartlead functionality.
|
└───src
|   |   FreeRTOSConfig.h
|   |   main.cpp
|   |
│   └───device
|   |   Device register mappings and system functionality.
|   |
│   └───drivers
|   |   Peripheral drivers.
|   |
│   └───startup
|   |   Reset vector startup code and vector table.
|
└───toolchain_support
|   |
│   └───linker_scripts
|   |   Linker scripts for microcontroller.
|   |
│   └───openocd_debug
        Files for OpenOCD debug configuration scripts.
```

<br>

### Next Section