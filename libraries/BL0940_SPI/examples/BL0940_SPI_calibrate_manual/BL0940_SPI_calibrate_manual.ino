//
//    FILE: BL0940_SPI_calibrate_manual.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: verify the formulas against the magic numbers from other lib
//     URL: https://github.com/RobTillaart/BL0940_SPI
//     URL: https://github.com/RobTillaart/printHelpers
//
//  to elaborate

#include "BL0940_SPI.h"
#include "printHelpers.h"  //

BL0940_SPI mySensor(5, 6, 7);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("BL0940_SPI_LIB_VERSION: ");
  Serial.println(BL0940_SPI_LIB_VERSION);
  Serial.println();

  SPI.begin();

  mySensor.begin();

  //  calibrate manually - hard coded values
  mySensor.setVoltageLSB(6.296E-05);
  mySensor.setCurrentLSB(3.981E-06);
  mySensor.setPowerLSB(1.604E-03);
  mySensor.setEnergyLSB(1.869E-04);

  Serial.println("VOLTAGE\t\tCURRENT\t\tPOWER\t\tENERGY");
  Serial.print(sci(mySensor.getVoltageLSB(), 3));
  Serial.print("\t");
  Serial.print(sci(mySensor.getCurrentLSB(), 3));
  Serial.print("\t");
  Serial.print(sci(mySensor.getPowerLSB(), 3));
  Serial.print("\t");
  Serial.println(sci(mySensor.getEnergyLSB(), 3));
  Serial.println();

  Serial.print("MAX VOLTAGE:     ");
  Serial.println(mySensor.getMaxVoltage(), 1);
  Serial.print("MAX VOLTAGE_RMS: ");
  Serial.println(mySensor.getMaxVoltageRMS(), 1);
  Serial.print("MAX CURRENT:     ");
  Serial.println(mySensor.getMaxCurrent(), 1);
  Serial.print("MAX CURRENT_RMS: ");
  Serial.println(mySensor.getMaxCurrentRMS(), 1);
  Serial.println();
}

void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();
    float delta = 1.01;
    switch (c)
    {
      case 'V' :
          mySensor.setVoltageLSB(mySensor.getVoltageLSB() * delta);
          Serial.println(mySensor.getVWave());
          break;
      case 'v' :
          mySensor.setVoltageLSB(mySensor.getVoltageLSB() / delta);
          Serial.println(mySensor.getVWave());
          break;
      case 'C' :
          mySensor.setCurrentLSB(mySensor.getCurrentLSB() * delta);
          Serial.println(mySensor.getIWave());
          break;
      case 'c' :
          mySensor.setCurrentLSB(mySensor.getCurrentLSB() / delta);
          Serial.println(mySensor.getIWave());
          break;
      case 'P' :
          mySensor.setPowerLSB(mySensor.getPowerLSB() * delta);
          Serial.println(mySensor.getWatt());
          break;
      case 'p' :
          mySensor.setPowerLSB(mySensor.getPowerLSB() / delta);
          Serial.println(mySensor.getWatt());
          break;
      case 'E' :
          mySensor.setEnergyLSB(mySensor.getEnergyLSB() * delta);
          Serial.println(mySensor.getEnergy());
          break;
      case 'e' :
          mySensor.setEnergyLSB(mySensor.getEnergyLSB() / delta);
          Serial.println(mySensor.getEnergy());
          break;
    }


    if (c == 'd')  //  dump
    {
      Serial.println("VOLTAGE\t\tCURRENT\t\tPOWER\t\tENERGY");
      Serial.print(sci(mySensor.getVoltageLSB(), 4));
      Serial.print("\t");
      Serial.print(sci(mySensor.getCurrentLSB(), 4));
      Serial.print("\t");
      Serial.print(sci(mySensor.getPowerLSB(), 4));
      Serial.print("\t");
      Serial.println(sci(mySensor.getEnergyLSB(), 4));
    }
  }

}



//  -- END OF FILE --