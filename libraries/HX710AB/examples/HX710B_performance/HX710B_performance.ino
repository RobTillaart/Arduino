//
//    FILE: HX710B_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic performance sync and async api
//          async api uses much less cpu cycles.
//     URL: https://github.com/RobTillaart/HX710AB


#include "HX710AB.h"

//  adjust pins to your setup
uint8_t dataPin = 6;
uint8_t clockPin = 7;

HX710B HX(dataPin, clockPin);

uint32_t start, stop;
volatile int32_t value;
volatile bool b;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HX710AB_LIB_VERSION: ");
  Serial.println(HX710AB_LIB_VERSION);
  Serial.println();
  Serial.println("test takes about 6 seconds.");
  Serial.println("times in micros, average 100x read");
  Serial.println();


  Serial.println("SYNCHRONOUS API");
  HX.begin(false);  //  fastprocessor flag
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    value = HX.read();
  }
  stop = micros();
  Serial.println("FPROC: \tfalse");
  Serial.print("READ: \t");
  Serial.println((stop - start) * 0.01);

  HX.begin(true);  //  fastprocessor flag
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    value = HX.read();
  }
  stop = micros();
  Serial.println("FPROC: \ttrue");
  Serial.print("READ: \t");
  Serial.println((stop - start) * 0.01);

  //////////////////////////////////////////////////////////
  Serial.println();
  Serial.println("A_SYNCHRONOUS API");
  float totalAsync = 0;
  HX.begin(true);  //  fastprocessor flag
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    HX.request();
  }
  stop = micros();
  Serial.print("REQUEST: \t");
  Serial.println((stop - start) * 0.01);
  totalAsync += ((stop - start) * 0.01);
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    b = HX.is_ready();
  }
  stop = micros();
  Serial.print("ISREADY: \t");
  Serial.println((stop - start) * 0.01);
  totalAsync += ((stop - start) * 0.01);
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    value = HX.fetch();
  }
  stop = micros();
  Serial.print("FETCH: \t\t");
  Serial.println((stop - start) * 0.01);
  totalAsync += ((stop - start) * 0.01);
  delay(100);

  Serial.print("TOTAL ASYNC: \t");
  Serial.println(totalAsync);
  delay(100);


  //////////////////////////////////////////////////////////
  Serial.println();
  Serial.println("CALIBRATE");
  HX.begin(true);  //  fastprocessor flag
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    HX.calibrate(50, 50, 100, 80);
  }
  stop = micros();
  Serial.print("CALIBRATE: \t");
  Serial.println((stop - start) * 0.01);
  Serial.println(HX.get_offset());
  Serial.println(HX.get_scale());
  delay(100);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
