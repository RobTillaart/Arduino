//
//    FILE: BL0942_SPI_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/BL0942_SPI


#include "BL0942_SPI.h"


BL0942_SPI mySensor(4, 5, 6, 7);


void setup()
{
  Serial.begin(115200);
//  Serial.println();
//  Serial.println(__FILE__);
//  Serial.print("BL0942_SPI_LIB_VERSION: ");
//  Serial.println(BL0942_SPI_LIB_VERSION);
//  Serial.println();

  SPI.begin();

  mySensor.begin();

  //  numbers from the BL0942 APP NOTE 
  float RF = (390000.0 * 5 + 510.0) / 510.0;
  float SHUNT = 0.001;
  
  mySensor.calibrate(SHUNT, RF);  //  shunt in ohm, reduction factor voltage.


  //  HEADER
  Serial.println("Volt\t Amp\t Watt\t kWh\t Freq\tStatus");
}

void loop()
{
  //  might need scaling...
  Serial.print(mySensor.getIWave());
  Serial.print("\t");
  Serial.print(mySensor.getVWave());
  Serial.print("\t");
  Serial.print(mySensor.getWatt());
  Serial.print("\t");
  Serial.print(mySensor.getEnergy());
  Serial.print("\t");
  Serial.print(mySensor.getFrequency());
  Serial.print("\t");
  Serial.println(mySensor.getStatus());
}


//  -- END OF FILE --
