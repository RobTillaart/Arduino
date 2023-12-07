//
//    FILE: SHT2x_demo_ESP32_2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo usage 2 I2C ports + SHT2X
//     URL: https://github.com/RobTillaart/SHT2x
//
// ESP32 specific - see issue #7


#include "Wire.h"
#include "SHT2x.h"


#define SDA_1   21
#define SCL_1   22
#define SDA_2   33
#define SCL_2   32

SHT2x internal(&Wire);
SHT2x external(&Wire1);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT2x_LIB_VERSION: \t");
  Serial.println(SHT2x_LIB_VERSION);

  Wire.begin(SDA_1, SCL_1);
  Wire1.begin(SDA_2, SCL_2);

  internal.begin();
  external.begin();

  uint8_t stat = internal.getStatus();
  Serial.print(stat, HEX);
  Serial.println();
  stat = external.getStatus();
  Serial.print(stat, HEX);
  Serial.println();
  Serial.println();
}


void loop()
{
  start = micros();
  internal.read();
  external.read();
  stop = micros();

  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(internal.getTemperature(), 1);
  Serial.print("\t");
  Serial.print(internal.getHumidity(), 1);
  Serial.print("\t");
  Serial.print(external.getTemperature(), 1);
  Serial.print("\t");
  Serial.println(external.getHumidity(), 1);
  delay(1000);
}


//  -- END OF FILE --
