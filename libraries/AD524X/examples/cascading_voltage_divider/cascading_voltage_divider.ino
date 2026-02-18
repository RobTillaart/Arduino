//    FILE: cascading_voltage_divider.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-05
// PURPOSE: demo, calculates voltage out for two cascaded potentiometers
//     URL: https://github.com/RobTillaart/AD524X/issues/26
//
//  Experimental
//  precission is as good as the smallest potentiometer.
//  math needs actual LSB and include Rwiper.
//

#include "Arduino.h"

float Vcc = 5.0;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();

  //  r1 = coarse steps 
  //  r2 = fine steps
  for (int r1 = 0; r1 < 1; r1++)
  {
    float V1out = Vcc * ( 1 - r1 / 256.0);

    for (int r2 = 0; r2 < 256; r2++)
    {
      float V2out = V1out * ( 1 - r2 / 256.0);
      //Serial.print(r1);
      Serial.print('\t');
      Serial.print(V1out, 3);
      Serial.print('\t');
      //Serial.print(r2);
      Serial.print('\t');
      Serial.print(V2out, 3);
      Serial.println();
    }
  }

}


void loop()
{
}


void search(float voltage)
{
  //  werkvoltage Vout + 20%
  //  max Vcc
  //  set r1 op Vout + 20%
  //  set r2 op Vout
}


//  -- END OF FILE --
