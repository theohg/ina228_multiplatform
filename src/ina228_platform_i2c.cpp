#include "ina228_platform_i2c.h"

bool ina228_i2c_probe(bus_handle_t bus, uint8_t device_address)
{
  if (bus == NULL)
  {
    return false;
  }

#ifdef INA228_PLATFORM_ARDUINO
  bus->beginTransmission(device_address);
  return bus->endTransmission() == 0;
#elif defined(INA228_PLATFORM_STM32)
  return HAL_I2C_IsDeviceReady(bus, (uint16_t)(device_address << 1), 1, HAL_MAX_DELAY) == HAL_OK;
#elif defined(INA228_PLATFORM_RP2040)
  uint8_t reg = 0;
  return i2c_write_blocking(bus, device_address, &reg, 1, false) == 1;
#else
  (void)device_address;
  return false;
#endif
}

bool ina228_i2c_write_pointer(bus_handle_t bus, uint8_t device_address, uint8_t reg)
{
  if (bus == NULL)
  {
    return false;
  }

#ifdef INA228_PLATFORM_ARDUINO
  bus->beginTransmission(device_address);
  bus->write(reg);
  return bus->endTransmission(false) == 0;
#elif defined(INA228_PLATFORM_STM32)
  return HAL_I2C_Master_Transmit(bus, (uint16_t)(device_address << 1), &reg, 1, HAL_MAX_DELAY) == HAL_OK;
#elif defined(INA228_PLATFORM_RP2040)
  return i2c_write_blocking(bus, device_address, &reg, 1, true) == 1;
#else
  (void)device_address;
  (void)reg;
  return false;
#endif
}

bool ina228_i2c_read_data(bus_handle_t bus, uint8_t device_address, uint8_t* buffer, size_t length)
{
  if (bus == NULL || buffer == NULL || length == 0)
  {
    return false;
  }

#ifdef INA228_PLATFORM_ARDUINO
  if (bus->requestFrom(device_address, static_cast<uint8_t>(length)) != length)
  {
    return false;
  }

  for (size_t index = 0; index < length; ++index)
  {
    if (!bus->available())
    {
      return false;
    }
    buffer[index] = bus->read();
  }
  return true;
#elif defined(INA228_PLATFORM_STM32)
  return HAL_I2C_Master_Receive(bus, (uint16_t)(device_address << 1), buffer, (uint16_t)length, HAL_MAX_DELAY) == HAL_OK;
#elif defined(INA228_PLATFORM_RP2040)
  return i2c_read_blocking(bus, device_address, buffer, length, false) == (int)length;
#else
  (void)device_address;
  (void)buffer;
  (void)length;
  return false;
#endif
}

bool ina228_i2c_write_register16(bus_handle_t bus, uint8_t device_address, uint8_t reg, uint16_t value)
{
  if (bus == NULL)
  {
    return false;
  }

  uint8_t payload[3];
  payload[0] = reg;
  payload[1] = (uint8_t)(value >> 8);
  payload[2] = (uint8_t)(value & 0xFF);

#ifdef INA228_PLATFORM_ARDUINO
  bus->beginTransmission(device_address);
  bus->write(payload, 3);
  return bus->endTransmission() == 0;
#elif defined(INA228_PLATFORM_STM32)
  return HAL_I2C_Master_Transmit(bus, (uint16_t)(device_address << 1), payload, 3, HAL_MAX_DELAY) == HAL_OK;
#elif defined(INA228_PLATFORM_RP2040)
  return i2c_write_blocking(bus, device_address, payload, 3, false) == 3;
#else
  (void)device_address;
  (void)reg;
  (void)value;
  return false;
#endif
}
