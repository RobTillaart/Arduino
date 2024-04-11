//
//    FILE: Cozir_setOutputFields.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir lib
//     URL: https://github.com/RobTillaart/Cozir
//
//    NOTE: this sketch needs a MEGA or a Teensy that supports a second
//          Serial port named Serial1
//    NOTE: not all fields are supported by all COZIR sensors.


#include "Arduino.h"
#include "cozir.h"

COZIR czr(&Serial1);

uint16_t fields = 2;
uint8_t  count = 0;


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
      Serial.print(fields);   //  or print czr.getDigiFilter()
      Serial.print('\t');
      if (count >= 10)
      {
        count = 0;
        fields *= 2;
        if (fields == 16384) fields = 2;
        czr.setOutputFields(fields);
      }
    }
  }
}


//  -- END OF FILE --
