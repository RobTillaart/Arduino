//
//    FILE: Vibration_plot_graph.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Vibration
//
//  used for plotter

#include "Vibration.h"

VibrationSensor VBS(A0);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("VIBRATION_LIB_VERSION: ");
  Serial.println(VIBRATION_LIB_VERSION);
  Serial.println();

  Serial.println("samples\t zero\t max\t avg\t sum");
}


void loop()
{
  //  measure 10 milliseconds.
  VBS.measure(10000);
  Serial.print(VBS.sampleCount());
  Serial.print('\t');
  Serial.print(VBS.zeroCount(), 1);
  Serial.print('\t');
  Serial.print(VBS.maxValue());
  Serial.print('\t');
  Serial.print(VBS.average(), 1);
  Serial.print('\t');
  Serial.print(VBS.sum());
  Serial.println();
}


//  -- END OF FILE --
