//
//    FILE: INA229_setBusVoltageConversionTime.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA229


#include "INA229.h"


//  select, dataIn, dataOut, clock == SOFTWARE SPI
INA229 INA(5, 6, 7, 8);

//  select, &SPI === HW SPI
//  INA229 INA(5, &SPI);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA229_LIB_VERSION: ");
  Serial.println(INA229_LIB_VERSION);
  Serial.println();

  SPI.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
  INA.setMaxCurrentShunt(10, 0.015);


  Serial.println("CONVERT TIME");
  for (int convertTime = 0; convertTime < 8; convertTime++)
  {
    INA.setBusVoltageConversionTime(convertTime);
    Serial.print(INA.getBusVoltageConversionTime());
  }
  Serial.println();
  Serial.println();


  Serial.println("AVERAGE");
  for (int avg = 0; avg < 8; avg++)
  {
    INA.setAverage(avg);
    Serial.print(INA.getAverage());
  }
  Serial.println();
  Serial.println();

  INA.setAverage(4);
}


void loop()
{
  for (int convertTime = 0; convertTime < 8; convertTime++)
  {
    Serial.print(INA.getBusVoltageConversionTime());
    Serial.print("\t");
    Serial.print(INA.getBusVoltage(), 4);
    Serial.println();
    delay(100);
  }
  Serial.println();

}


//  -- END OF FILE --
