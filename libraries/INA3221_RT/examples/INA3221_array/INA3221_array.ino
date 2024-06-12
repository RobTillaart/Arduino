//
//    FILE: INA3221_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo polling 3 channels
//     URL: https://github.com/RobTillaart/INA3221_RT
//
//  Compiles only on ESP32 or other board with (at least) two Wire ports.


#include "INA3221.h"

#define INADEVICES  8

INA3221 INA[INADEVICES]
{
  INA3221(0x40, &Wire), INA3221(0x41, &Wire), INA3221(0x42, &Wire), INA3221(0x43, &Wire),
  INA3221(0x40, &Wire1), INA3221(0x41, &Wire1), INA3221(0x42, &Wire1), INA3221(0x43, &Wire1)
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA3221_LIB_VERSION: ");
  Serial.println(INA3221_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);
  Wire1.begin();
  Wire1.setClock(400000);

  for (int i = 0; i < INADEVICES; i++)
  {
    Serial.print(i);
    Serial.print("\t");
    if (INA[i].begin() == false)
    {
      Serial.println("could not connect.");
    }
    else
    {
      Serial.print(INA[i].getDieID(), HEX);
      Serial.print("\t");
      Serial.print(INA[i].getManufacturerID(), HEX);
      Serial.print("\t");
      Serial.print(INA[i].getConfiguration(), HEX);
      Serial.println();
    }
  }

  //  set shunts.
  for (int i = 0; i < INADEVICES; i++)
  {
    INA[i].setShuntR(0, 0.100);
    INA[i].setShuntR(1, 0.100);
    INA[i].setShuntR(2, 0.100);
  }

  Serial.println();
}


void loop()
{
  for (int dev = 0; dev < INADEVICES; dev++)
  {
    Serial.println("DEV\tCHAN\tBUS\tSHUNT\tCURRENT\tPOWER");
    for (int channel = 0; channel < 3; channel++)
    {
      Serial.print(dev);
      Serial.print("\t");
      Serial.print(channel);
      Serial.print("\t");
      Serial.print(INA[dev].getBusVoltage(channel), 3);
      Serial.print("\t");
      Serial.print(INA[dev].getShuntVoltage_mV(channel), 3);
      Serial.print("\t");
      Serial.print(INA[dev].getCurrent_mA(channel), 3);
      Serial.print("\t");
      Serial.print(INA[dev].getPower_mW(channel), 3);
      Serial.println();
    }
    Serial.println();
  }

  delay(1000);
}


//  -- END OF FILE --
