//
//    FILE: HX_MP_calibrate.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711_MP


#include "HX711_MP.h"


//  2 calibration points
//  but not needed as we only read raw data here
HX711_MP scale(2);


//  adjust pins to your setup.
uint8_t dataPin = 16;
uint8_t clockPin = 17;


uint32_t start, stop;
volatile float f;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HX711_MP_LIB_VERSION: ");
  Serial.println(HX711_MP_LIB_VERSION);
  Serial.println();
  Serial.println("Get raw values for the calibration points.");
  Serial.println("Put weight on and wait for raw value to stabilize.");
  Serial.println("Write down the raw value and the used weight..");
  Serial.println();

  scale.begin(dataPin, clockPin);
  scale.set_average_mode();
}


void loop()
{
  f = scale.get_value(20);
  Serial.println(f);
  delay(1000);
}


//  -- END OF FILE --
