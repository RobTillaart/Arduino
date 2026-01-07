//
//    FILE: BL0942_SPI_calibrate.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: basic behaviour calibration
//     URL: https://github.com/RobTillaart/BL0942_SPI
//     URL: https://github.com/RobTillaart/printHelpers


#include "BL0942_SPI.h"
#include "printHelpers.h"  //  

BL0942_SPI mySensor(4, 5, 6, 7);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("BL0942_SPI_LIB_VERSION: ");
  Serial.println(BL0942_SPI_LIB_VERSION);
  Serial.println();

  SPI.begin();

  mySensor.begin();

  //  numbers from the BL0942 APP NOTE 
  float RF = (390000.0 * 5 + 510.0) / 510.0;
  float SHUNT = 0.001;
  
  mySensor.calibrate(SHUNT, RF);  //  shunt in ohm, reduction factor voltage.

  Serial.print("SHUNT:\t");
  Serial.println(SHUNT, 4);
  Serial.print("RF:\t");
  Serial.println(RF, 2);
  Serial.println();

  Serial.print("VOLTAGE_LSB:\t");
  Serial.println(sci(mySensor.getVoltageLSB(), 3));
  Serial.println(3494335 * mySensor.getVoltageLSB(), 3);  //  219.999 V
  Serial.println();

  Serial.print("CURRENT_LSB:\t");
  Serial.println(sci(mySensor.getCurrentLSB(), 2));
  Serial.println(251213 * mySensor.getCurrentLSB(), 2);  //  ~1.0 Ampere
  Serial.println();

  Serial.print("POWER_LSB:\t");
  Serial.println(sci(mySensor.getPowerLSB(), 2));
  Serial.println(137146 * mySensor.getPowerLSB(), 2);  //  220 Watt
  Serial.println();

  Serial.print("ENERGY_LSB:\t");
  Serial.println(sci(mySensor.getEnergyLSB(), 3));
  Serial.println(1200 * mySensor.getEnergyLSB(), 3);   //  0.224 kWh
  Serial.println();

  Serial.println("Done...");
}


void loop()
{
}


//  -- END OF FILE --
