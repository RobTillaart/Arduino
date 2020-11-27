//
//    FILE: DHT12_test_esp.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Demo for DHT12 I2C humidity & temperature sensor
//
// HISTORY:
// 0.1.0    2020-04-11 initial version
//

#include <DHT12.h>

DHT12 DHT;

void setup()
{
  DHT.begin(12, 13);  // select your pin numbers here

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DHT12 LIBRARY VERSION: ");
  Serial.println(DHT12_LIB_VERSION);
  Serial.println();

  delay(2000);

  Serial.println("Type,\tStatus,\tHumidity (%),\tTemperature (C)");
}

void loop()
{
  // READ DATA
  Serial.print("DHT12, \t");
  int status = DHT.read();
  switch (status)
  {
  case DHT12_OK:
    Serial.print("OK,\t");
    break;
  case DHT12_ERROR_CHECKSUM:
    Serial.print("Checksum error,\t");
    break;
  case DHT12_ERROR_CONNECT:
    Serial.print("Connect error,\t");
    break;
  case DHT12_MISSING_BYTES:
    Serial.print("Missing bytes,\t");
    break;
  default:
    Serial.print("Unknown error,\t");
    break;
  }
  // DISPLAY DATA, sensor has only one decimal.
  Serial.print(DHT.getHumidity(), 1);
  Serial.print(",\t");
  Serial.println(DHT.getTemperature(), 1);

  delay(2000);
}

// -- END OF FILE --
