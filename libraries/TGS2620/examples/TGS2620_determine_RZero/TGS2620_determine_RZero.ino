//
//    FILE: TGS2620_determine_RZero.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TGS2620
//     URL: https://github.com/RobTillaart/printHelpers


#include "TGS2620.h"

//
//  5V-----[ SENSOR ]-----O------[ RL ]------ GND
//                        |
//                        |
//                        V
//                     analogRead
//
//  resistor values in Ohm
uint16_t RL   = 47000;  //  load = voltage divider with sensor

float voltage = 5.00;   //  voltage over Rs and Rload


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TGS2620_LIB_VERSION: ");
  Serial.println(TGS2620_LIB_VERSION);
  Serial.println();

  Serial.println("volt\traw\tRZero");
}


void loop()
{
  float sum = 0;
  //  make 10000 measurements to minimize noise
  for (int i = 0; i < 10000; i++)
  {
    sum += analogRead(A0);
  }
  float raw = sum * 0.0001;

  uint16_t RZero = RL * voltage / raw - RL;
  Serial.print(voltage);
  Serial.print("\t");
  Serial.print(raw);
  Serial.print("\t");
  Serial.println(RZero);
}


//  -- END OF FILE --
