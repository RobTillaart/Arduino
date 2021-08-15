//
//    FILE: AGS02MA_minimal.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: test application
//    DATE: 2021-08-14
//     URL: https://github.com/RobTillaart/AGS02MA
//

// default register is 0x00 at start of the sensor
// datasheet states one can get the value with minimal interaction.
// note this sketch does not use the library!


#include "Wire.h"


uint8_t buffer[5];


void setup()
{
  Serial.begin(115200);

  Wire.begin();
  Wire.setClock(30400);      // lowest speed an UNO supports that works with sensor.
}


void loop()
{
  delay(3000);
  Wire.requestFrom(26, 5);
  for ( int i = 0; i < 5; i++)
  {
    buffer[i] = Wire.read();
    // Serial.print(buffer[i], HEX);  // for debugging.
    // Serial.print('\t');
  }
  Serial.println();

  // CONVERT RAW DATA
  Serial.print("STAT:\t");
  Serial.println(buffer[0]);
  Serial.println("PPB:\t");
  Serial.println(buffer[1] * 65536UL + buffer[2] * 256 + buffer[3]);
  Serial.println("CRC:\t");
  Serial.println(buffer[4]);
  Serial.println();

}

// -- END OF FILE --
