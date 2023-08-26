//
//    FILE: HX_loadcell_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711
//
//  TODO: test with hardware

#include "HX711.h"

HX711 scale0;
HX711 scale1;
HX711 scale2;
HX711 scale3;

HX711 scales[4] = { scale0, scale1, scale2, scale3 };

const uint8_t dataPin[4] = { 3, 4, 5, 6 };
const uint8_t clockPin = 7;

// TODO you need to adjust to your calibrate numbers
float calib[4] = { 420.0983, 421.365, 419.200, 410.236 };

uint32_t count = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  for (int i = 0; i < 4; i++)
  {
    scales[i].begin(dataPin[i], clockPin);
    scales[i].set_scale(calib[i]);
    // reset the scale to zero = 0
    scales[i].tare();
  }
}


void loop()
{
  count++;
  Serial.print(count);
  for (int i = 0; i < 4; i++)
  {
    Serial.print("\t");
    Serial.print(scales[i].get_units(5));
  }
  Serial.println();
  delay(250);
}


//  -- END OF FILE --
