//    FILE: NC_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: pseudo random noise from analogWrite + Neumann Corrector
//     URL: https://github.com/RobTillaart/NeumannCorrector


#include "NeumannCorrector.h"

NeumannCorrector NC;
uint32_t start, stop;

volatile uint32_t x;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("NEUMANNCORRECTOR_LIB_VERSION: ");
  Serial.println(NEUMANNCORRECTOR_LIB_VERSION);
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    NC.add(i);
  }
  stop = micros();
  Serial.print("ADD:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = NC.get();
  }
  stop = micros();
  Serial.print("GET:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = NC.get16();
  }
  stop = micros();
  Serial.print("GET16:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = NC.get32();
  }
  stop = micros();
  Serial.print("GET32:\t");
  Serial.println((stop - start) * 0.001);

  Serial.println("\ndone...");
}

void loop()
{

}


//  -- END OF FILE --
