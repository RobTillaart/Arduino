//
//    FILE: INA260_dump_registers.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA260
//
//     expected output something like
//
//      REGISTER      VALUE   VALUE_X
//    -----------------------------------
//    CONFIGURATION:  16679   4127
//          CURRENT:  65533   FFFD
//      BUS VOLTAGE:  2       2
//            POWER:  0       0
//


#include "INA260.h"


INA260 INA(0x40);


char names[6][20] =
{
  "CONFIGURATION: ",
  "      CURRENT: ",
  "  BUS VOLTAGE: ",
  "        POWER: "
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA260_LIB_VERSION: ");
  Serial.println(INA260_LIB_VERSION);

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
}


void loop()
{
  Serial.println("\n\tREGISTER\tVALUE\tVALUE_X");
  for (int r = 0; r < 6; r++)
  {
    Serial.print('\t');
    Serial.print(names[r]);
    Serial.print('\t');
    Serial.print(INA.getRegister(r), DEC);
    Serial.print('\t');
    Serial.println(INA.getRegister(r), HEX);
  }
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --
