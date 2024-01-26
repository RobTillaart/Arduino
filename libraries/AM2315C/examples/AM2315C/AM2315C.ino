//
//    FILE: AM2315C.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for AM2315C I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/AM2315C
//
//  Always check datasheet
//
//                    +-----------------+
//    RED    -------- | VDD             |
//    YELLOW -------- | SDA    AM2315C  |
//    BLACK  -------- | GND             |
//    WHITE  -------- | SCL             |
//                    +-----------------+


#include "AM2315C.h"

AM2315C DHT;

uint8_t count = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AM2315C LIBRARY VERSION: ");
  Serial.println(AM2315C_LIB_VERSION);
  Serial.println();

  Wire.begin();
  DHT.begin();

  delay(1000);
}


void loop()
{
  if (millis() - DHT.lastRead() >= 1000)
  {
    //  READ DATA
    uint32_t start = micros();
    int status = DHT.read();
    uint32_t stop = micros();

    if ((count % 10) == 0)
    {
      count = 0;
      Serial.println();
      Serial.println("Type\tHumidity (%)\tTemp (°C)\tTime (µs)\tStatus");
    }
    count++;

    Serial.print("AM2315C \t");
    //  DISPLAY DATA, sensor has only one decimal.
    Serial.print(DHT.getHumidity(), 1);
    Serial.print("\t\t");
    Serial.print(DHT.getTemperature(), 1);
    Serial.print("\t\t");
    Serial.print(stop - start);
    Serial.print("\t\t");
    switch (status)
    {
      case AM2315C_OK:
        Serial.print("OK");
        break;
      case AM2315C_ERROR_CHECKSUM:
        Serial.print("Checksum error");
        break;
      case AM2315C_ERROR_CONNECT:
        Serial.print("Connect error");
        break;
      case AM2315C_MISSING_BYTES:
        Serial.print("Missing bytes");
        break;
      case AM2315C_ERROR_BYTES_ALL_ZERO:
        Serial.print("All bytes read zero");
        break;
      case AM2315C_ERROR_READ_TIMEOUT:
        Serial.print("Read time out");
        break;
      case AM2315C_ERROR_LASTREAD:
        Serial.print("Error read too fast");
        break;
      default:
        Serial.print("Unknown error");
        break;
    }
    Serial.print("\n");
  }
}


//  -- END OF FILE --
