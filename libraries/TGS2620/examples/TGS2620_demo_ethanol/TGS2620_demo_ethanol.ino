//
//    FILE: TGS2620_demo_ethanol.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TGS2620
//     URL: https://github.com/RobTillaart/printHelpers


#include "TGS2620.h"
#include "printHelpers.h"

//
//  5V-----[ SENSOR ]-----O------[ RL ]------ GND
//                        |
//                        |
//                        V
//                     analogRead
//
//  resistor values in Ohm
uint16_t RL = 47000;  //  load = voltage divider with sensor
uint16_t RZ = 40000;  //  to be determined


//  calibration constants from readme.md,
//  Ethanol
float a = 320.799771;
float b = -1.5398176;

TGS2620 TGS(A0, 1023);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TGS2620_LIB_VERSION: ");
  Serial.println(TGS2620_LIB_VERSION);
  Serial.println();

  TGS.configure(RZ, RL);
  TGS.calibrate(a, b);

  Serial.println("Ethanol (PPM)");
}


void loop()
{
  Serial.println(TGS.getPPM(), 1);
  delay(100);
}


//  -- END OF FILE --
