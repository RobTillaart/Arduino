//
//    FILE: Cozir_setDigiFilter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir lib
//     URL: https://github.com/RobTillaart/Cozir
//
//    NOTE: this sketch needs a MEGA or a Teensy that supports a second
//          Serial port named Serial1


#include "Arduino.h"
#include "cozir.h"

COZIR czr(&Serial1);

uint8_t filter = 1;
uint8_t count = 0;


void setup()
{
  Serial1.begin(9600);
  czr.init();

  Serial.begin(115200);
  Serial.print("COZIR_LIB_VERSION: ");
  Serial.println(COZIR_LIB_VERSION);
  Serial.println();

  czr.setOperatingMode(CZR_STREAMING);
  delay(1000);
}


void loop()
{
  if (Serial1.available())
  {
    char c = Serial1.read();
    Serial.write(c);
    if (c == '\n')
    {
      count++;
      Serial.print(count);
      Serial.print('\t');
      Serial.print(filter);   //  or print czr.getDigiFilter() 
      Serial.print('\t');
      if (count >= 10)
      {
        count = 0;
        filter *= 2;
        if (filter == 0) filter = 1;
        czr.setDigiFilter(filter);
      }
    }
  }
}


//  -- END OF FILE --
