//
//    FILE: AD5144A_test_control_register.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: read CONTROL REGISTER functions
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

  Serial.println("check datasheet");
  Serial.println("CH\tWP\tEE\tMODE\tBURST");
  for (uint8_t potMeter = 0; potMeter < AD.pmCount(); potMeter++)
  {
    uint8_t mask = AD.readBackCONTROL(potMeter);
    Serial.print(potMeter);
    Serial.print('\t');
    Serial.print(mask & 0x01);
    Serial.print('\t');
    Serial.print(mask & 0x02);
    Serial.print('\t');
    Serial.print(mask & 0x04);
    Serial.print('\t');
    Serial.print(mask & 0x08);
    Serial.println();
  }

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
