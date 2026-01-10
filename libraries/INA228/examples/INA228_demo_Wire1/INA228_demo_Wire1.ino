//
//    FILE: INA228_demo_Wire1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo core functions
//     URL: https://github.com/RobTillaart/INA228


#include "INA228.h"


INA228 INA(0x40, &Wire1);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA228_LIB_VERSION: ");
  Serial.println(INA228_LIB_VERSION);
  Serial.println();

  Wire1.begin();
  if (!INA.begin() )
  {
    Serial.println("Could not connect. Fix and Reboot");
    while(1);
  }

  INA.setMaxCurrentShunt(10, 0.015);

}


void loop()
{
  Serial.println("\nVBUS\tVSHUNT\tCURRENT\tPOWER\tTEMP");
  for (int i = 0; i < 20; i++)
  {
    Serial.print(INA.getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA.getShuntMilliVolt(), 3);
    Serial.print("\t");
    Serial.print(INA.getMilliAmpere(), 3);
    Serial.print("\t");
    Serial.print(INA.getMilliWatt(), 3);
    Serial.print("\t");
    Serial.print(INA.getTemperature(), 3);
    Serial.println();
    delay(1000);
  }
}


//  -- END OF FILE --
