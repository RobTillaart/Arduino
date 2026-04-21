//
//    FILE: FSLP_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test performance
//     URL: https://github.com/RobTillaart/FSLP


#include "FSLP.h"

//
//  FSLP(pin1, pin2, pin3, extraPin)
//  pin1 = GPIO/ADC
//  pin2 = GPIO
//  pin3 = GPIO/ADC
//  ePin = GPIO
//
//  FSLP(uint8_t sense, uint8_t drive1, uint8_t drive2, uint8_t gpio)
//
FSLP fslp(14, 4, 15, 5);

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FSLP_LIB_VERSION: ");
  Serial.println(FSLP_LIB_VERSION);
  Serial.println();
  delay(100);

  //  optional tuning.
  //  fslp.setStabilizationDelay(5);
  //  fslp.setPressureFactor(32);
}


void loop()
{
  for (int times = 1; times < 6; times++)
  {
    start = micros();
    float pos = fslp.readPosition(times);
    stop = micros();
    Serial.print(times);    
    Serial.print("\tTIME POS:\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.println(pos);
    delay(10);

    start = micros();
    float pres = fslp.readPressure(times);
    stop = micros();
    Serial.print(times);    
    Serial.print("\tTIME PRES:\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.println(pres);
    delay(10);
  }

  Serial.println();
  delay(1000);

}


//  -- END OF FILE --
