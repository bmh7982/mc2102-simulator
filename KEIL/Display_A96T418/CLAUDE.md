# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is an embedded firmware project for the ABOV A96T418 microcontroller, designed for a water dispenser/purifier display control system. The A96T418 is a capacitive touch sensor MCU with integrated LED driver capabilities.

The firmware handles:
- Touch key sensing (hot, cold, room temperature, amount, power saving, cock dispense)
- LED indicator control (UV clean, water supply, hot lock, purifier status, etc.)
- External display communication via 3-wire interface (CLK, STB, DIO)
- Display dimming control with 8 levels
- Touch frequency selection for noise immunity

## Build System

This project uses KEIL μVision 5 IDE for compilation and debugging.

**Build commands:**
- Open project: Launch KEIL μVision 5 and open `application/a96t418_application.uvproj`
- Build: Press F7 or use Project → Build Target
- Rebuild: Project → Rebuild all target files
- Clean: Project → Clean Targets
- Download/Debug: Press F8 or use Debug → Start/Stop Debug Session

**Output files:** Located in `application/out/` directory
- `*.hex` - Intel HEX format for programming
- `*.axf` - ARM executable format
- `*.map` - Memory map file

## Code Architecture

### Directory Structure

```
application/source/     Main application code
  ├── main.c/h         System initialization and main task loop
  ├── proc.c/h         User application logic (display protocol handling)
  ├── A96T418_io.h     Pin definitions and hardware abstraction macros
  ├── user_function.c/h Feature configuration and initialization
  ├── led_driver.c/h   LED segment/common driver (optional)
  ├── touch_config.c   Touch sensor channel configuration
  └── [peripherals]    GPIO, I2C, WDT, timer, flash drivers

common/                 MCU-specific files
  ├── A96T418.h        SFR (Special Function Register) definitions
  └── common.h         Shared data structures and flags

library/                Touch sensor library (precompiled)
  └── library_touch_V105_20230918.LIB  - Proprietary touch sensing algorithms
```

### Main Task Loop Architecture

The firmware uses a round-robin task scheduler in `main.c`:

```c
while (1) {
    switch (task) {
        case TASK_LED:     // LED scanning (if LED_DRV_EN=1)
        case TASK_TOUCH:   // Touch sensing via library
        case TASK_GESTURE: // Slide/wheel processing
        case TASK_DEBUG:   // Debug output
        case TASK_USER:    // User logic in proc()
    }
    task = (task + 1) % TASK_MAX;
}
```

**Critical note:** The `proc()` function in `proc.c` runs every task cycle. Keep it non-blocking and fast to maintain responsive touch sensing.

### Touch Sensor Library Integration

The touch sensor functionality is provided by a precompiled library (`library_touch_V105_20230918.LIB`). The library is configured through:

1. **touch_config.c** - Channel mapping, thresholds, sensitivity settings
2. **user_function.h** - Feature flags (TOUCH_FREQ_SEL_EN, HOLD_KEY_RELEASE, etc.)
3. **Library callbacks** - Custom frequency selection via `func_p_Touch_Freq_Sel`

Key library functions:
- `Library_Data_Assign()` - Initialize library data structures
- `Touch_Config_Set()` - Apply configuration from touch_config.c
- `Touch_Do_Task()` - Execute touch sensing (call in TASK_TOUCH)
- `diff_data[]` - Global array with touch delta values for each channel

**Touch channels:** Maximum 20 channels (CH_00 to CH_19). Not all channels may be physically available depending on package/PCB design.

### External Display Interface

The firmware implements a 3-wire display protocol in `proc.c`:

**Interface pins:**
- CLK (P26) - Clock input (triggers INT_Ext10 on both edges)
- STB (P25) - Strobe/chip select (triggers INT_Ext11 on rising edge)
- DIO (P27) - Bidirectional data (input for commands, output for key status)

**Protocol modes:**
- **WRITE_MODE:** Receive display data and commands from external MCU
- **READ_MODE:** Send touch key status back to external MCU

**Display control:**
- `ADDR[14]` array stores segment data received from external MCU
- `DOUT[6]` array holds key status to send back
- `DIMM` variable controls PWM dimming level (0-56 range)
- `Display_stat` enum controls overall display on/off

The `subDisplay()` function in `proc.c` maps the ADDR[] array to physical LED outputs on GPIO pins based on the dimming counter.

## Configuration Files

### user_function.h

Central configuration header for enabling/disabling features:

```c
#define LED_DRV_EN              0  // Use hardware LED driver (0=GPIO control)
#define UART_ENABLE             0  // Debug UART output
#define I2C_ENABLE              0  // I2C slave interface
#define WDT_ENABLE              0  // Watchdog timer
#define TOUCH_FREQ_SEL_EN       1  // Automatic frequency hopping
#define HOLD_KEY_RELEASE        1  // Hold key release behavior
#define WHEEL_FUNCTION_EN       0  // Wheel gesture support
#define SLIDE_FUNCTION_EN       0  // Slide gesture support
```

**Important:** After changing feature flags, rebuild the entire project to ensure consistency.

### A96T418_io.h

Hardware abstraction layer defining:
- GPIO pin assignments for each LED output
- `LED_xxx_on()` / `LED_xxx_off()` macros for each indicator
- Port direction/pull-up/open-drain configuration values
- Pin function selection register values

**LED naming convention:** Matches the water dispenser UI (LED_HOT, LED_COLD, LED_COCK1, LED_PWR_SAVING, etc.)

## Interrupt Handlers

The firmware uses these interrupts:

1. **INT_Ext10 (CLK)** - Shift in data bits from external display controller on CLK edges
2. **INT_Ext11 (STB)** - Reset communication state when STB goes high
3. **INT_Timer1** - 0.01ms period for display dimming PWM (updates Dimming_cnt)
4. **INT_Timer2** - 1ms period for touch key debouncing (sets bit_key_oper flag)

All interrupt handlers are in `main.c`. Keep handlers minimal and use flags to defer processing to main loop.

## Common Development Tasks

**Modifying touch sensitivity:**
1. Edit channel thresholds in `application/source/touch_config.c`
2. Adjust `SENS_SEL` and `HYS_SEL` values for each channel
3. Rebuild and test on hardware

**Adding a new LED indicator:**
1. Assign GPIO pin in `A96T418_io.h` (check pin availability)
2. Add macro definitions: `LED_NAME_on()`, `LED_NAME_off()`
3. Update `P[x]IO_VAL` and `P[x]_VAL` configuration
4. Call the macros in `proc.c` based on your logic

**Changing display protocol:**
- Modify interrupt handlers `INT_Ext10()` and `INT_Ext11()` in `main.c`
- Update `proc()` function in `proc.c` for command parsing
- Adjust `ADDR[]` to LED mapping in `subDisplay()`

**Debugging touch issues:**
1. Enable UART output: Set `UART_ENABLE 1` in `user_function.h`
2. Read `diff_data[]` array to see raw touch delta values
3. Check if `TOUCH_FREQ_SEL_EN` helps with noise (frequency hopping)
4. Verify touch channel to physical sensor mapping in `touch_config.c`

## Memory Constraints

The A96T418 has limited RAM (typically 512-1024 bytes depending on variant). Avoid:
- Large stack allocations or deep recursion
- Excessive use of `printf()` with floating point (uses ~2KB)
- Large global arrays (use `code` space for const data when possible)

Use `data`, `idata`, `xdata`, `code` memory modifiers appropriately for the 8051 architecture.

## Code Style Notes

- Interrupt handlers use `interrupt N` syntax (KEIL C51)
- Bit variables use the `bit` type for single-bit flags
- SFR access uses direct register names (P0, P1, IE, etc.) from `A96T418.h`
- Macros use do-while(0) pattern for safe expansion
- Korean comments are present in legacy code (primarily in `proc.c`)
