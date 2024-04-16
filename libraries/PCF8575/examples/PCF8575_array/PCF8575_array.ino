//
//    FILE: PCF8575_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo array of PCF - not tested
//     URL: https://github.com/RobTillaart/PCF8575


#include "PCF8575.h"

//  adjust addresses if needed
PCF8575 A(0x20);
PCF8575 B(0x21);
PCF8575 C(0x22);

PCF8575 PCF[3] = { A, B, C };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8575_LIB_VERSION:\t");
  Serial.println(PCF8575_LIB_VERSION);

  Wire.begin();

  for (int i = 0; i < 3; i++)
  {
    PCF[i].begin();
  }
}


void loop()
{
  for (int i = 0; i < 3; i++)
  {
    for (uint8_t port = 0; port < 16; port++)
    {
      PCF[i].write(port, 1);
      delay(200);
    }
  }

  for (int i = 0; i < 3; i++)
  {
    for (uint8_t port = 0; port < 16; port++)
    {
      PCF[i].write(port, 0);
      delay(400);
    }
  }

}


//  -- END OF FILE --

