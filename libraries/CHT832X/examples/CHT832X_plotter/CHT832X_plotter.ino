//
//    FILE: CHT832X_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for CHT832X I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/CHT832X
//
//  Always check datasheet for connections
//  to be used with Arduino Serial plotter


#include "CHT832X.h"

CHT832X CHT;


void setup()
{
  Serial.begin(115200);
  //  Serial.println();
  //  Serial.println(__FILE__);
  //  Serial.print(F("CHT832X_LIB_VERSION: "));
  //  Serial.println(CHT832X_LIB_VERSION);
  //  Serial.println();

  Wire.begin();
  CHT.begin();

  delay(1000);
  //  header
  Serial.println("HUMIDITY\tTEMPERATURE");
}


void loop()
{
  //  500 ms ==> 2 samples per second.
  //  change for other frequency, be aware one sample takes 60++ ms.
  if (millis() - CHT.lastRead() >= 500)
  {
    //  READ DATA
    CHT.read();
    Serial.print(CHT.getHumidity());
    Serial.print('\t');
    Serial.println(CHT.getTemperature());
  }
}


//  -- END OF FILE --
