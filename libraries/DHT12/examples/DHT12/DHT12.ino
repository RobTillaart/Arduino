//
//    FILE: DHT12.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for DHT12 I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/DHT12


#include "DHT12.h"

DHT12 DHT;  //  implicit Wire


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DHT12 LIBRARY VERSION: ");
  Serial.println(DHT12_LIB_VERSION);
  Serial.println();

  Wire.begin();
  DHT.begin();

  delay(2000);

  Serial.println("Type,\tStatus,\tHumidity (%),\tTemperature (C)");
}


void loop()
{
  if (millis() - DHT.lastRead() >= 2000)
  {
    //  READ DATA
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
    //  DISPLAY DATA, sensor has only one decimal.
    Serial.print(DHT.getHumidity(), 1);
    Serial.print(",\t");
    Serial.println(DHT.getTemperature(), 1);
  }
}


//  -- END OF FILE --
