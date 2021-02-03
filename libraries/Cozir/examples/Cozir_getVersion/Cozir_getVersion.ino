//
//    FILE: Cozir_getVersion.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo of Cozir lib (>= 0.1.06)
//    DATE: 2021-01-31
//     URL: http://forum.arduino.cc/index.php?topic=91467.0
//

// Note: this sketch needs a MEGA or a Teensy that supports a second
//       Serial port named Serial1

#include "cozir.h"

COZIR czr(&Serial1);

void setup()
{
  Serial1.begin(9600);
  czr.init();
  
  Serial.begin(115200);
  Serial.print("Cozir HardwareSerial: ");
  Serial.println(COZIR_LIB_VERSION);
  Serial.println();

  delay(100);
  czr.GetVersionSerial();
  delay(5);
  while (Serial1.available())
  {
    Serial.write(Serial1.read());
  }
  delay(100);

  czr.GetConfiguration();
  delay(5);
  while (Serial1.available())
  {
    Serial.write(Serial1.read());
  }
  delay(1000);

  // reset to polling again.
  czr.SetOperatingMode(CZR_POLLING);
}

void loop()
{
  float t = czr.Celsius();
  float f = czr.Fahrenheit();
  float h = czr.Humidity();
  uint32_t c = czr.CO2();

  Serial.print("Celcius =\t");    Serial.println(t);
  Serial.print("Fahrenheit =\t"); Serial.println(f);
  Serial.print("Humidity =\t");   Serial.println(h);
  Serial.print("CO2 =\t");        Serial.println(c);
  Serial.println();

  delay(3000);
}

// -- END OF FILE --
