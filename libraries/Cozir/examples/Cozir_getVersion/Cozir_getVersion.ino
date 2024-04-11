//
//    FILE: Cozir_getVersion.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir lib
//     URL: https://github.com/RobTillaart/Cozir
//
//    NOTE: this sketch needs a MEGA or a Teensy that supports a second
//          Serial port named Serial1


#include "Arduino.h"
#include "cozir.h"


COZIR czr(&Serial1);


void setup()
{
  Serial1.begin(9600);
  czr.init();

  Serial.begin(115200);
  Serial.print("COZIR_LIB_VERSION: ");
  Serial.println(COZIR_LIB_VERSION);
  Serial.println();

  delay(100);
  czr.getVersionSerial();
  delay(5);
  while (Serial1.available())
  {
    Serial.write(Serial1.read());
  }
  delay(100);

  czr.getConfiguration();
  delay(5);
  while (Serial1.available())
  {
    Serial.write(Serial1.read());
  }
  delay(1000);

  //  set to polling explicitly.
  czr.setOperatingMode(CZR_POLLING);
  delay(1000);
}


void loop()
{
  float t = czr.celsius();
  float f = czr.fahrenheit();
  float h = czr.humidity();
  uint32_t c = czr.CO2();

  Serial.print("Celsius =\t");    Serial.println(t);
  Serial.print("Fahrenheit =\t"); Serial.println(f);
  Serial.print("Humidity =\t");   Serial.println(h);
  Serial.print("CO2 =\t");        Serial.println(c);
  Serial.println();

  delay(3000);
}


//  -- END OF FILE --

