//
//    FILE: AD5144A_test_EEPROM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test EEPROM functions
//     URL: https://github.com/RobTillaart/AD5144A


#include "AD5144A.h"

//  select the right type
//  adjust address
AD5144A AD(0x77);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  if (AD.begin() == false)
  {
    Serial.println("device not found");
    return;
  }

  //  values should be same after start
  for (int potMeter = 0; potMeter < AD.pmCount(); potMeter++)
  {
    Serial.print(potMeter);
    Serial.print('\t');
    Serial.print(AD.recallEEPROM(potMeter));
    Serial.print('\t');
    Serial.print(AD.readBackRDAC(potMeter));
    Serial.println();
  }

  //  update values for after next (full) power up.
  for (int potMeter = 0; potMeter < AD.pmCount(); potMeter++)
  {
    uint8_t value = AD.recallEEPROM(potMeter);
    AD.storeEEPROM(potMeter, value + 1);
  }

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
