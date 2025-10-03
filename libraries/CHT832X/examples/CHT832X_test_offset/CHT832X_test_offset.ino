//
//    FILE: CHT832X_test_offset.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for CHT832X I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/CHT832X

//  Always check datasheet for connections


#include "CHT832X.h"

CHT832X CHT;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("CHT832X_LIB_VERSION: "));
  Serial.println(CHT832X_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  CHT.begin();

  //  should print 0.00 twice
  Serial.println(CHT.getTemperatureOffset());
  Serial.println(CHT.getHumidityOffset());
  Serial.println();

  CHT.setTemperatureOffset(+273.15);  //  adjusts temperature to Kelvin
  CHT.setHumidityOffset(-50);         //  extreme just for demo
  delay(1000);
}


void loop()
{
  if (millis() - CHT.lastRead() >= 1000)
  {
    //  READ DATA
    CHT.read();

    Serial.print(millis());
    Serial.print('\t');
    Serial.print(CHT.getHumidity());
    Serial.print('\t');
    Serial.println(CHT.getTemperature());
  }
}


//  -- END OF FILE --
