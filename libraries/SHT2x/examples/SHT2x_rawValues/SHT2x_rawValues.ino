//
//    FILE: SHT2x_raw_values.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo raw
//     URL: https://github.com/RobTillaart/SHT2x


#include "Wire.h"
#include "SHT2x.h"

uint32_t start, stop;

SHT2x sht;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT2x_LIB_VERSION: \t");
  Serial.println(SHT2x_LIB_VERSION);

  Wire.begin();
  sht.begin();

  uint8_t stat = sht.getStatus();
  Serial.print(stat, HEX);
  Serial.println();
}


void loop()
{
  uint16_t rawTemperature;
  uint16_t rawHumidity;

  start = micros();
  bool success  = sht.read();
  stop = micros();
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  if (success == false)
  {
    Serial.println("Failed read");
  }
  else
  {
    rawTemperature = sht.getRawTemperature();
    rawHumidity = sht.getRawHumidity();
    Serial.print(rawTemperature, HEX);
    Serial.print(" = ");
    Serial.print(sht.getTemperature(), 1);
    Serial.print("°C\t");
    Serial.print(rawHumidity, HEX);
    Serial.print(" = ");
    Serial.print(sht.getHumidity(), 1);
    Serial.print("%\t");
    Serial.println();
  }

  delay(1000);
}


//  -- END OF FILE --
