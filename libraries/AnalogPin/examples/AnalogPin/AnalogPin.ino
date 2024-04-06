//
//    FILE: AnalogPin.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: example sketch
//     URL: https://github.com/RobTillaart/AnalogPin


#include "AnalogPin.h"

AnalogPin INA(A0);
AnalogPin INB(A1);

uint32_t start, stop;
uint32_t val;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ANALOGPIN_LIB_VERSION: ");
  Serial.println(ANALOGPIN_LIB_VERSION);
  Serial.println();

  Serial.println("time in msec");

  INB.setPrescaler(5);  // fast sampling

  Serial.println("\nINA.read()");
  val = 0;
  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    val += INA.read();
  }
  stop = millis();
  Serial.print("TIME:\t ");
  Serial.println(stop - start);
  Serial.print("VALUE:\t ");
  Serial.println(val / 1000);


  Serial.println("\nINA.read()  noise filtering");
  val = 0;
  INA.setNoiseThreshold(10);
  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    val += INA.read();
  }
  stop = millis();
  Serial.print("TIME:\t ");
  Serial.println(stop - start);
  Serial.print("VALUE:\t ");
  Serial.println(val / 1000);


  Serial.println("\nINA.readSmoothed()  alpha = 16/32");
  val = 0;
  INA.setSmoothWeight(16);
  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    val += INA.readSmoothed();
  }
  stop = millis();
  Serial.print("TIME:\t ");
  Serial.println(stop - start);
  Serial.print("VALUE:\t ");
  Serial.println(val / 1000);

  Serial.println("\nINB.read() - prescale = 5");
  val = 0;
  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    val += INB.read();
  }
  stop = millis();
  Serial.print("TIME:\t ");
  Serial.println(stop - start);
  Serial.print("VALUE:\t ");
  Serial.println(val / 1000);
  Serial.println();
  delay(1000);
}


void loop()
{
  Serial.print(INA.read());
  Serial.print('\t');
  Serial.print(INA.read());
  Serial.print('\t');
  Serial.print(INA.readSmoothed());
  Serial.println();
  delay(1000);
}


// -- END OF FILE --

