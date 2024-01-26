//
//    FILE: AM2315C_test_Wire1.ino
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

AM2315C DHT(&Wire1);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AM2315C LIBRARY VERSION: ");
  Serial.println(AM2315C_LIB_VERSION);
  Serial.println();

  Wire1.begin(12, 13);    //  ESP32 default pins 21 22
  Wire1.setClock(400000);
  
  DHT.begin();

  delay(2000);

  Serial.println("Type,\tStatus,\tHumidity (%),\tTemperature (C)");
}


void loop()
{
  //  READ DATA
  Serial.print("AM2315C, \t");
  int status = DHT.read();
  switch (status)
  {
  case AM2315C_OK:
    Serial.print("OK,\t");
    break;
  case AM2315C_ERROR_CHECKSUM:
    Serial.print("Checksum error,\t");
    break;
  case AM2315C_ERROR_CONNECT:
    Serial.print("Connect error,\t");
    break;
  case AM2315C_MISSING_BYTES:
    Serial.print("Missing bytes,\t");
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
    Serial.print("Unknown error,\t");
    break;
  }

  //  DISPLAY DATA, sensor has only one decimal.
  Serial.print(DHT.getHumidity(), 1);
  Serial.print(",\t");
  Serial.println(DHT.getTemperature(), 1);

  delay(2000);
}


//  -- END OF FILE --
