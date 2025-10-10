//
//    FILE: SHT4x_rawValues.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo reading raw data
//     URL: https://github.com/RobTillaart/SHT4x

/*
For async call:
requestData(measurementType = SHT4x_MEASUREMENT_SLOW);

For sync call:
read(uint8_t measurementType = SHT4x_MEASUREMENT_SLOW, bool errorCheck = true);

| measurement type                    |  duration  |  heater  |  power   |  notes  |
|:-----------------------------------:|:----------:|:--------:|:--------:|:-------:|
| SHT4x_MEASUREMENT_SLOW              |     9 ms   |     N    |     -    | default |
| SHT4x_MEASUREMENT_MEDIUM            |     5 ms   |     N    |     -    |
| SHT4x_MEASUREMENT_FAST              |     2 ms   |     N    |     -    |
| SHT4x_MEASUREMENT_LONG_HIGH_HEAT    |  1100 ms   |     Y    |  200 mW  |
| SHT4x_MEASUREMENT_LONG_MEDIUM_HEAT  |  1100 ms   |     Y    |  110 mW  |
| SHT4x_MEASUREMENT_LONG_LOW_HEAT     |  1100 ms   |     Y    |   20 mW  |
| SHT4x_MEASUREMENT_SHORT_HIGH_HEAT   |   110 ms   |     Y    |  200 mW  |
| SHT4x_MEASUREMENT_SHORT_MEDIUM_HEAT |   110 ms   |     Y    |  110 mW  |
| SHT4x_MEASUREMENT_SHORT_LOW_HEAT    |   110 ms   |     Y    |   20 mW  |

*/

#include "Wire.h"
#include "SHT4x.h"

#define SHT_DEFAULT_ADDRESS   0x44

uint32_t start;
uint32_t stop;
uint32_t cnt;

SHT4x sht(SHT_DEFAULT_ADDRESS);  //  uses explicit address


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SHT4x_LIB_VERSION: \t");
  Serial.println(SHT4x_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  sht.begin();

  sht.requestData();
  cnt = 0;
}


void loop()
{
  uint16_t rawTemperature;
  uint16_t rawHumidity;

  if (sht.dataReady())
  {
    start = micros();
    bool success  = sht.readData(); //  default = true for CRC check
    stop = micros();
    sht.requestData();  //  default SHT4x_MEASUREMENT_SLOW, request next sample

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

      //  This formula comes from page 12 of the SHT4x datasheet
      Serial.print(rawTemperature * (175.0 / 65535) - 45, 1);
      Serial.print("°C\t");
      Serial.print(sht.getRawHumidity(), HEX);
      Serial.print(" = ");

      //  This formula comes from page 12 of the SHT4x datasheet
      Serial.print(rawHumidity * (125.0 / 65535) - 6, 1);
      Serial.print("%\t");
      Serial.println(cnt);
      cnt = 0;
    }
  }
  cnt++;  //  simulate other activity
}


//  -- END OF FILE --

