//
//    FILE: LTC2942_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic charge reading
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

  Serial.print("CONT \tSTAT \tCHARGE \tVOLTS \tTEMPC\n");
}


void loop()
{
  uint16_t charge;
  LTC.getRawCharge(charge);
  float volts;
  LTC.getVoltage(volts);
  float temperature;
  LTC.getTemperature(temperature);
  uint8_t status;
  LTC.getStatus(status);
  
  uint8_t alcc = 0;
  uint8_t prescaler = 0;
  uint8_t shutdown = 0;
  uint8_t batAlert = 0;
  LTC.getControl(alcc, prescaler, shutdown, batAlert);

  Serial.print(alcc);
  Serial.print("\t");
  Serial.print(prescaler);
  Serial.print("\t");
  Serial.print(shutdown);
  Serial.print("\t");
  Serial.print(batAlert);
  Serial.print("\t");
  Serial.print(status, HEX);
  Serial.print("\t");
  Serial.print(charge);
  Serial.print("\t");
  Serial.print(volts);
  Serial.print("\t");
  Serial.println(temperature);
  delay(2000);
}


//  -- END OF FILE --
