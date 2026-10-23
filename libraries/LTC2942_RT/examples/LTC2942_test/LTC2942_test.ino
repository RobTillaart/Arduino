//
//    FILE: LTC2942_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test core functions
//     URL: https://github.com/RobTillaart/LTC2942_RT


#include "LTC2942.h"

LTC2942 LTC;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LTC2942_LIB_VERSION: ");
  Serial.println(LTC2942_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = LTC.begin(2000, 0.050);
  Serial.print("BEGIN:\t");
  Serial.println(b);
  Serial.print("ADDR:\t");
  Serial.println(LTC.getAddress());

  test_stat();
  test_charge();
  test_voltage();
  test_temperature();

  Serial.println("\ndone");
}

void loop()
{
}

//////////////////////////////////////////////////

void test_stat()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.print("STAT \tCONTROL\n");
  uint8_t status;
  LTC.getStatus(status);
  uint8_t alcc = 0;
  uint8_t prescaler = 0;
  uint8_t shutdown = 0;
  uint8_t ADCMode = 0;
  LTC.getControl(alcc, prescaler, shutdown, ADCMode);
  Serial.print(status, HEX);
  Serial.print("\t");
  Serial.print(alcc);
  Serial.print("\t");
  Serial.print(prescaler);
  Serial.print("\t");
  Serial.print(shutdown);
  Serial.print("\t");
  Serial.println(ADCMode);
}

void test_charge()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.print("getCharge: \t");
  //  save old value to restore
  uint16_t val;
  uint16_t nval;
  LTC.getRawCharge(val);
  val ^= 0xFFFF;
  LTC.setRawCharge(val);
  LTC.getRawCharge(nval);
  if (nval != (val))
  {
    Serial.println("Error");
  }
  else
  {
    Serial.println("OK");
  }
  //  restore
  LTC.setRawCharge(val ^ 0xFFFF);


  Serial.print("getChargeThresholdHigh: \t");
  //  save old value to restore
  LTC.getRawChargeThresholdHigh(val);
  val ^= 0xFFFF;
  LTC.setRawChargeThresholdHigh(val);
  LTC.getRawChargeThresholdHigh(nval);
  if (nval != val)
  {
    Serial.println("Error");
  }
  else
  {
    Serial.println("OK");
  }
  //  restore
  LTC.setRawChargeThresholdHigh(val ^ 0xFFFF);


  Serial.print("getChargeThresholdLow: \t");
  //  save old value to restore
  LTC.getRawChargeThresholdLow(val);
  val ^= 0xFFFF;
  LTC.setRawChargeThresholdLow(val);
  LTC.getRawChargeThresholdLow(nval);
  if (nval != val)
  {
    Serial.println("Error");
  }
  else
  {
    Serial.println("OK");
  }
  //  restore
  LTC.setRawChargeThresholdLow(val ^ 0xFFFF);
}

void test_voltage()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.print("getVoltage: \t");
  float volts;
  LTC.getVoltage(volts);
  Serial.println(volts);

  Serial.print("getVoltageThresholdHigh: \t");
  LTC.getVoltageThresholdHigh(volts);
  Serial.println(volts);

  Serial.print("getVoltageThresholdLow: \t");
  LTC.getVoltageThresholdLow(volts);
  Serial.println(volts);
}

void test_temperature()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.print("getTemperature: \t");
  float temperature;
  LTC.getTemperature(temperature);
  Serial.println(temperature);

  Serial.print("getTemperatureThresholdHigh: \t");
  LTC.getTemperatureThresholdHigh(temperature);
  Serial.println(temperature);

  Serial.print("getTemperatureThresholdLow: \t");
  LTC.getTemperatureThresholdLow(temperature);
  Serial.println(temperature);
}


//  -- END OF FILE --
