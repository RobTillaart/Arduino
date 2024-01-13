//
//    FILE: INA226_dump_registers.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA226
//
//     expected output something like
//
//      REGISTER      VALUE   VALUE_X
//    -----------------------------------
//    CONFIGURATION:  16679   4127
//            SHUNT:  65533   FFFD
//      BUS VOLTAGE:  2       2
//            POWER:  0       0
//          CURRENT:  0       0
//      CALIBRATION:  0       0
//


#include "INA226.h"


INA226 INA(0x40);


char names[6][20] =
{
  "CONFIGURATION: ",
  "        SHUNT: ",
  "  BUS VOLTAGE: ",
  "        POWER: ",
  "      CURRENT: ",
  "  CALIBRATION: "
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA226_LIB_VERSION: ");
  Serial.println(INA226_LIB_VERSION);

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

