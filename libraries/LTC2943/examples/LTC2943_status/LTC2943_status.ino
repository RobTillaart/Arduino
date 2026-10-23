//
//    FILE: LTC2943_status.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: split status bits.
//     URL: https://github.com/RobTillaart/LTC2943


#include "LTC2943.h"

LTC2943 LTC;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LTC2943_LIB_VERSION: ");
  Serial.println(LTC2943_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = LTC.begin(2000, 0.050);
  Serial.print("BEGIN:\t");
  Serial.println(b);
  Serial.print("ADDR:\t");
  Serial.println(LTC.getAddress());

  Serial.print("CHARGE \tCONT \tSTAT\n");
}


void loop()
{
  uint16_t charge;
  LTC.getRawCharge(charge);
  uint8_t status;
  LTC.getStatus(status);

  Serial.print(charge);
  Serial.print("\t");
  Serial.print(status, HEX);
  //  check all status fields,
  //  multiple alerts are possible
  if (status & LTC2943_ALERT_UNDERVOLTAGE)  Serial.print("\tundervoltage");
  if (status & LTC2943_ALERT_VOLTAGE)       Serial.print("\tvoltage");
  if (status & LTC2943_ALERT_CHARGE_LOW)    Serial.print("\tchargeLow");
  if (status & LTC2943_ALERT_CHARGE_HIGH)   Serial.print("\tchargeHigh");
  if (status & LTC2943_ALERT_TEMPERATURE)   Serial.print("\ttemperature");
  if (status & LTC2943_ALERT_UNDEROVERFLOW) Serial.print("\toverflow");
  if (status & LTC2943_ALERT_CURRENT)       Serial.print("\tcurrent");
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --
