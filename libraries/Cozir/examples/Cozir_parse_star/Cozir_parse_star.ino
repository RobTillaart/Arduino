//
//    FILE: Cozir_parse_star.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir sensor
//     URL: https://github.com/RobTillaart/Cozir
//
//    NOTE: this sketch needs a MEGA or a Teensy that supports a second
//          Serial port named Serial1


#include "Arduino.h"
#include "cozir.h"    //  not mandatory

COZIR czr(&Serial1);


void setup()
{
  Serial1.begin(9600);

  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("COZIR_LIB_VERSION: ");
  Serial.println(COZIR_LIB_VERSION);
  Serial.println();

}


void loop()
{
  if (Serial.available())
  {
    Serial1.write(Serial.read());
  }
  if (Serial1.available())
  {
    Serial.write(Serial1.read());
  }
}


uint32_t get_field(char* buffer, char * field)
{

  //  TODO

  return 0;
}

//  -- END OF FILE --


