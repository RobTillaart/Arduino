//
//    FILE: DHT20.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for DHT20 I2C humidity & temperature sensor
//


#include "DHT20.h"

DHT20 DHT;


void setup()
{
  DHT.begin();

  Wire.setClock(400000);
  
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DHT20 LIBRARY VERSION: ");
  Serial.println(DHT20_LIB_VERSION);
  Serial.println();

  delay(2000);

  Serial.println("Type,\tStatus,\tHumidity (%),\tTemperature (C)");
}


void loop()
{
  if (millis() - DHT.lastRead() >= 1000)
  {
    // READ DATA
    uint32_t start = micros();
    int status = DHT.read();
    uint32_t stop = micros();
    switch (status)
    {
    case DHT20_OK:
      Serial.print("OK,\t");
      break;
    case DHT20_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case DHT20_ERROR_CONNECT:
      Serial.print("Connect error,\t");
      break;
    case DHT20_MISSING_BYTES:
      Serial.print("Missing bytes,\t");
      break;
    default:
      Serial.print("Unknown error,\t");
      break;
    }
    // DISPLAY DATA, sensor has only one decimal.
    Serial.print("DHT20, \t");
    Serial.print(DHT.getHumidity(), 1);
    Serial.print(",\t");
    Serial.print(DHT.getTemperature(), 1);
    Serial.print(",\t");
    Serial.print(stop - start);
    Serial.print("\n");
  }
}


// -- END OF FILE --
