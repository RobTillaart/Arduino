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
  for (int ch = 0; ch < AD.pmCount(); ch++)
  {
    Serial.print(ch);
    Serial.print('\t');
    Serial.print(AD.recallEEPROM(ch));
    Serial.print('\t');
    Serial.print(AD.readBackRDAC(ch));
    Serial.println();
  }

  //  update values for after next (full) power up.
  for (int ch = 0; ch < AD.pmCount(); ch++)
  {
    uint8_t val = AD.recallEEPROM(ch);
    AD.storeEEPROM(ch, val + 1);
  }

  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --
