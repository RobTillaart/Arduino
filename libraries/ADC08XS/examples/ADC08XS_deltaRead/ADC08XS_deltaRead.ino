//
//    FILE: ADC08XS_deltaRead.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ADC08XS


#include "ADC08XS.h"


ADC124S adc01(5, 6, 7);  //  use SWSPI

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADC08XS_LIB_VERSION: ");
  Serial.println(ADC08XS_LIB_VERSION);

  SPI.begin();
  adc01.begin(4);
}


void loop()
{

  //  ADC124S has several possible combinations for deltaRead
  //  including using the same channel twice.
  Serial.println("A\tB\tDelta");
  for (int A = 0; A < 4; A++)
  {
    for (int B = 0; B < 4; B++)
    {
      Serial.print(A);
      Serial.print("\t");
      Serial.print(B);
      Serial.print("\t");
      Serial.println(adc01.deltaRead(A, B));
      delay(10);
    }
  }
  Serial.println();
  Serial.println();
  delay(5000);
}


//  -- END OF FILE --
