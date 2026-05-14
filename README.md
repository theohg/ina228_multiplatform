# ina228_multiplatform

Multiplatform C++ library for the INA228 current, voltage, power, energy, and charge monitor.

## Features

- Shared library layout with `include/` and `src/`
- Platform abstraction for Arduino, STM32 HAL, and RP2040 Pico SDK
- Bus-aware constructor for multi-bus and multi-device setups
- High-level measurement API for voltage, current, power, temperature, energy, and charge
- Alert and overcurrent helper APIs

## Basic Usage

```cpp
#include <Wire.h>
#include <ina228.h>

INA228 monitor(&Wire, 0x40, 0.008f, 10.0f);

void setup() {
  Wire.begin();
  monitor.init();
}
```

Addresses are always passed as 7-bit I2C addresses.

## Examples

- `examples/basic_monitoring/basic_monitoring.ino`
- `examples/alert_monitoring/alert_monitoring.ino`
