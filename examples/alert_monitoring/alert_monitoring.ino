#include <Wire.h>
#include <ina228.h>

#define INA228_ADDR            0x40
#define SHUNT_RESISTOR_OHMS    0.008f
#define MAX_CURRENT_AMPS       10.0f
#define ALERT_LIMIT_AMPS       2.5f

#if (defined(PICO_BOARD) || defined(PICO_RP2040) || defined(PICO_SDK_VERSION_MAJOR)) && !defined(ARDUINO)
#include "hardware/gpio.h"
void initBus()
{
  i2c_init(i2c0, 400000);
  gpio_set_function(4, GPIO_FUNC_I2C);
  gpio_set_function(5, GPIO_FUNC_I2C);
  gpio_pull_up(4);
  gpio_pull_up(5);
}
INA228 monitor(i2c0, INA228_ADDR, SHUNT_RESISTOR_OHMS, MAX_CURRENT_AMPS);
#else
void initBus()
{
  Wire.begin();
}
INA228 monitor(&Wire, INA228_ADDR, SHUNT_RESISTOR_OHMS, MAX_CURRENT_AMPS);
#endif

void setup()
{
  Serial.begin(115200);
  initBus();

  if (!monitor.init())
  {
    Serial.print("INA228 init failed, error=");
    Serial.println(monitor.getLastError());
    return;
  }

  monitor.setMode(INA228_MODE_CONT_TEMP_BUS_SHUNT);
  if (!monitor.setOvercurrentLimit(ALERT_LIMIT_AMPS, true))
  {
    Serial.println("Failed to configure overcurrent alert");
    return;
  }

  Serial.println("INA228 alert monitoring ready");
}

void loop()
{
  Serial.print("Current: ");
  Serial.print(monitor.getCurrent(), 3);
  Serial.println(" A");

  if (monitor.getDiagnoseAlertBit(INA228_DIAG_SHUNT_OVER_LIMIT))
  {
    Serial.println("Overcurrent alert active");
    Serial.print("Alert register: 0x");
    Serial.println(monitor.getDiagnoseAlert(), HEX);
  }

  if (monitor.hasMathOverflow())
  {
    Serial.println("Math overflow detected");
  }

  int error = monitor.getLastError();
  if (error != 0)
  {
    Serial.print("Last I2C error: ");
    Serial.println(error);
  }

  delay(500);
}
