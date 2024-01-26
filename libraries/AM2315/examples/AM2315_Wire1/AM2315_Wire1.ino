//
//    FILE: AM2315_Wire1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for AM2315 I2C humidity & temperature sensor
//          Wire1 on ESP32 (et al)
//     URL: https://github.com/RobTillaart/AM2315


#include "AM2315.h"

AM2315 sensor(&Wire1);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AM2315_LIB_VERSION: ");
  Serial.println(AM2315_LIB_VERSION);
  Serial.println();

  Wire.begin();
  //  Wire.setClock(100000);

  while (sensor.begin() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to sensor.");
    delay(1000);
  }

  delay(2000);

  Serial.println("Type,\tStatus,\tHumidity (%),\tTemperature (C), \t micros");
  delay(100);
}


void loop()
{
  if (millis() - sensor.lastRead() >= 2000)
  {
    //  READ DATA
    uint32_t start = micros();
    int status = sensor.read();
    uint32_t stop = micros();
    switch (status)
    {
    case AM2315_OK:
      Serial.print("OK,\t");
      break;
    case AM2315_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case AM2315_ERROR_CONNECT:
      Serial.print("Connect error,\t");
      break;
    case AM2315_MISSING_BYTES:
      Serial.print("Bytes error,\t");
      break;
    default:
      Serial.print("error <");
      Serial.print(status);
      Serial.print(">,\t");
      break;
    }
    //  DISPLAY DATA, sensor has only one decimal.
    Serial.print("AM2315, \t");
    Serial.print(sensor.getHumidity(), 1);
    Serial.print(",\t");
    Serial.print(sensor.getTemperature(), 1);
    Serial.print(",\t");
    Serial.print(stop - start);
    Serial.print("\n");
  }
}


//  -- END OF FILE --
