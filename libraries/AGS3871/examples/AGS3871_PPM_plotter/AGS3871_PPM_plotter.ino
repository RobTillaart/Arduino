//
//    FILE: AGS3871_PPM_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: show data + running average in plotter.
//     URL: https://github.com/RobTillaart/AGS3871
//
//  to be used with Serial plotter


#include "AGS3871.h"


AGS3871 AGS;

float average = 0;
float alpha = 0.85;  //  0.0 = slowest  1.0 = fastest,  adjust if needed.


void setup()
{
  //  ESP devices typically miss the first serial log lines after flashing.
  //  Delay somewhat to include all output.
  delay(1000);

  Serial.begin(115200);
//  Serial.println(__FILE__);
//  Serial.print("AGS3871_LIB_VERSION: ");
//  Serial.println(AGS3871_LIB_VERSION);
//  Serial.println();

  Wire.begin();
  AGS.begin();
  //  note: pre-heating skipped

  //  HEADER
  Serial.println("PPM CO\tAVERAGE");
  //  start value for average
  delay(2000);
  average = AGS.readPPM();
}


void loop()
{
  delay(2000);
  int PPM = AGS.readPPM();
  average += alpha * (PPM - average);

  Serial.print(PPM);
  Serial.print("\t");
  Serial.print(average);
  Serial.println();
}


//  -- END OF FILE --
