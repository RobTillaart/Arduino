//
//    FILE: LTC2941_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test core functions
//     URL: https://github.com/RobTillaart/LTC2941


#include "LTC2941.h"

LTC2941 LTC;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LTC2941_LIB_VERSION: ");
  Serial.println(LTC2941_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = LTC.begin(2000, 0.050);
  Serial.print("BEGIN:\t");
  Serial.println(b);
  Serial.print("ADDR:\t");
  Serial.println(LTC.getAddress());

  test_stat();
  test_charge();

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
  uint8_t batAlert = 0;
  LTC.getControl(alcc, prescaler, shutdown, batAlert);
  Serial.print(status, HEX);
  Serial.print("\t");
  Serial.print(alcc);
  Serial.print("\t");
  Serial.print(prescaler);
  Serial.print("\t");
  Serial.print(shutdown);
  Serial.print("\t");
  Serial.println(batAlert);
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


  Serial.print("getThresholdHigh: \t");
  //  save old value to restore
  LTC.getRawThresholdHigh(val);
  val ^= 0xFFFF;
  LTC.setRawThresholdHigh(val);
  LTC.getRawThresholdHigh(nval);
  if (nval != val)
  {
    Serial.println("Error");
  }
  else
  {
    Serial.println("OK");
  }
  //  restore
  LTC.setRawThresholdHigh(val ^ 0xFFFF);


  Serial.print("getThresholdLow: \t");
  //  save old value to restore
  LTC.getRawThresholdLow(val);
  val ^= 0xFFFF;
  LTC.setRawThresholdLow(val);
  LTC.getRawThresholdLow(nval);
  if (nval != val)
  {
    Serial.println("Error");
  }
  else
  {
    Serial.println("OK");
  }
  //  restore
  LTC.setRawThresholdLow(val ^ 0xFFFF);
}


//  -- END OF FILE --
