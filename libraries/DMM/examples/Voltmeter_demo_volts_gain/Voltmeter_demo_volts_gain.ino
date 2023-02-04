//
//    FILE: DMM_volts_gain.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DMM 
//     URL: https://github.com/RobTillaart/DMM
//
//  add a 25 -> 5 volt converter before A0


#include "DMM.h"


DMM dmm;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("DMM_LIB_VERSION: ");
  Serial.println(DMM_LIB_VERSION);

  dmm.begin(A0, 5.000, 1023);

  //  add a 25 -> 5 volt converter before A0
  dmm.setGain(5);

  //  alternative
  //  dmm.begin(A0, 25.000, 1023);

}


void loop()
{
  float volts = dmm.readVolts();
  Serial.print("VOLT: ");
  Serial.print(volts, 3);
  Serial.print("\tGAIN: ");
  Serial.print(dmm.getGain(), 3);
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --
