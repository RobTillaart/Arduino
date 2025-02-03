//
//    FILE: INA239_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo core functions
//     URL: https://github.com/RobTillaart/INA239


#include "INA239.h"

//  select, dataIn, dataOut, clock == SOFTWARE SPI
//  INA239 INA(5, 6, 7, 8);

//  select, &SPI === HW SPI
INA239 INA(5, &SPI);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("INA239_LIB_VERSION: ");
  Serial.println(INA239_LIB_VERSION);
  Serial.println();

  SPI.begin();

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
