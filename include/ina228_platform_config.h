/**
 * @file ina228_platform_config.h
 * @brief Compile-time platform detection for the INA228 library.
 */

#ifndef INA228_PLATFORM_CONFIG_H
#define INA228_PLATFORM_CONFIG_H

#if defined(ESP32) || defined(ESP_PLATFORM) || defined(ARDUINO)
    #define INA228_PLATFORM_ARDUINO
    #ifndef PLATFORM_ARDUINO
        #define PLATFORM_ARDUINO
    #endif
    #include <Arduino.h>

#elif defined(USE_HAL_DRIVER) || defined(USE_STM32_HAL_DRIVER) || defined(INA228_PLATFORM_STM32)
    #ifndef INA228_PLATFORM_STM32
        #define INA228_PLATFORM_STM32
    #endif
    #ifndef PLATFORM_STM32
        #define PLATFORM_STM32
    #endif
    #include <stdio.h>
    #include <math.h>
    #include <string.h>

    #if defined(INA228_STM32_HAL_HEADER)
        #include INA228_STM32_HAL_HEADER
    #elif defined(STM32C0xx)
        #include "stm32c0xx_hal.h"
    #elif defined(STM32F0xx)
        #include "stm32f0xx_hal.h"
    #elif defined(STM32F1xx)
        #include "stm32f1xx_hal.h"
    #elif defined(STM32F2xx)
        #include "stm32f2xx_hal.h"
    #elif defined(STM32F3xx)
        #include "stm32f3xx_hal.h"
    #elif defined(STM32F4xx)
        #include "stm32f4xx_hal.h"
    #elif defined(STM32F7xx)
        #include "stm32f7xx_hal.h"
    #elif defined(STM32G0xx)
        #include "stm32g0xx_hal.h"
    #elif defined(STM32G4xx)
        #include "stm32g4xx_hal.h"
    #elif defined(STM32H5xx)
        #include "stm32h5xx_hal.h"
    #elif defined(STM32H7xx)
        #include "stm32h7xx_hal.h"
    #elif defined(STM32L0xx)
        #include "stm32l0xx_hal.h"
    #elif defined(STM32L1xx)
        #include "stm32l1xx_hal.h"
    #elif defined(STM32L4xx)
        #include "stm32l4xx_hal.h"
    #elif defined(STM32L5xx)
        #include "stm32l5xx_hal.h"
    #elif defined(STM32U0xx)
        #include "stm32u0xx_hal.h"
    #elif defined(STM32U5xx)
        #include "stm32u5xx_hal.h"
    #elif defined(STM32WBxx) || defined(STM32WB5Mxx) || defined(STM32WB55xx)
        #include "stm32wbxx_hal.h"
    #elif defined(STM32WBAxx)
        #include "stm32wbaxx_hal.h"
    #elif defined(STM32WLxx)
        #include "stm32wlxx_hal.h"
    #else
        #error "STM32 family not detected. Define INA228_STM32_HAL_HEADER in build flags."
    #endif

#elif defined(PICO_BOARD) || defined(PICO_RP2040) || defined(PICO_SDK_VERSION_MAJOR)
    #define INA228_PLATFORM_RP2040
    #ifndef PLATFORM_RP2040
        #define PLATFORM_RP2040
    #endif
    #include <stdio.h>
    #include <math.h>
    #include <string.h>
    #include "hardware/i2c.h"

#else
    #error "Unsupported platform. Define INA228_PLATFORM_ARDUINO, INA228_PLATFORM_STM32, or INA228_PLATFORM_RP2040 manually."
#endif

#endif /* INA228_PLATFORM_CONFIG_H */
