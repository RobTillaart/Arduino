//
//    FILE: TRAFO_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TRAFO


#include "TRAFO.h"


TRAFO myTrafo;

uint32_t start, stop;
volatile int32_t raw = 0;
volatile float freq = 0;
volatile float volt = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TRAFO_LIB_VERSION: ");
  Serial.println(TRAFO_LIB_VERSION);
  Serial.println();

  myTrafo.begin(readADC, 1023, 5.0);

  delay(100);
  start = micros();
  raw = myTrafo.getADC();
  stop = micros();
  Serial.print("GET_ADC: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  freq = myTrafo.detectFrequency(1);
  stop = micros();
  Serial.print("DET_FREQ 1: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  freq = myTrafo.detectFrequency(10);
  stop = micros();
  Serial.print("DET_FREQ 10: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  volt = myTrafo.getRMS();
  stop = micros();
  Serial.print("GET_RMS: \t");
  Serial.println(stop - start);

  Serial.println("\ndone...");
}


void loop()
{
}


int32_t readADC()
{
  return (int32_t)analogRead(A0);
}


//  -- END OF FILE --
