//
//    FILE: Cozir_SWSerial_getVersion.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir lib
//     URL: https://github.com/RobTillaart/Cozir
//
//    NOTE: software serial is less reliable than hardware serial


#include "Arduino.h"
#include "cozir.h"
#include "SoftwareSerial.h"

SoftwareSerial sws(3, 2);  //  RX, TX, optional inverse logic

COZIR czr(&sws);


void setup()
{
  sws.begin(9600);
  czr.init();

  Serial.begin(115200);
  Serial.print("COZIR_LIB_VERSION: ");
  Serial.println(COZIR_LIB_VERSION);
  Serial.println();

  delay(100);
  czr.getVersionSerial();
  delay(5);
  while (sws.available())
  {
    Serial.write(sws.read());
  }
  delay(100);

  czr.getConfiguration();
  delay(5);
  while (sws.available())
  {
    Serial.write(sws.read());
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
