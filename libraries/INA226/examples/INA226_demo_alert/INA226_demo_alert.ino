//
//    FILE: INA226_demo_alert.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA226


//  EXPERIMENTAL CODE - NOT TESTED.


#include "INA226.h"


INA226 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA226_LIB_VERSION: ");
  Serial.println(INA226_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }

  //  to be tested....
  //  measure POWER LIMIT ?
  //  assume milliamperes.
  uint16_t limit = 1000;
  INA.setAlertLimit(limit);

  //  read back to verify.
  uint16_t test_limit = INA.getAlertLimit();
  if (test_limit != limit)
  {
    Serial.print("Unexpected limit:\t");
    Serial.println(test_limit);
    while(1);
  }

  uint16_t alert_mask = INA226_POWER_OVER_LIMIT;
  INA.setAlertRegister(alert_mask);
}


void loop()
{
  uint16_t flags = INA.getAlertFlag();
  if (flags )
  {
    Serial.print("alarm:\t");
    Serial.println(INA.getShuntVoltage());
  }
}


//  -- END OF FILE --

