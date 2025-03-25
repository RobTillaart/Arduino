//
//    FILE: PCA9671_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo array of PCA - not tested
//     URL: https://github.com/RobTillaart/PCA9671


#include "PCA9671.h"

//  adjust addresses if needed
PCA9671 A(0x20);
PCA9671 B(0x21);
PCA9671 C(0x22);

PCA9671 PCA[3] = { A, B, C };


void setup()
{
  //  while(!Serial);  //  uncomment when needed
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9671_LIB_VERSION:\t");
  Serial.println(PCA9671_LIB_VERSION);
  Serial.println();

  Wire.begin();

  for (int i = 0; i < 3; i++)
  {
    PCA[i].begin();
  }
}


void loop()
{
  for (int i = 0; i < 3; i++)
  {
    for (uint8_t port = 0; port < 16; port++)
    {
      PCA[i].write(port, 1);
      delay(200);
    }
  }

  for (int i = 0; i < 3; i++)
  {
    for (uint8_t port = 0; port < 16; port++)
    {
      PCA[i].write(port, 0);
      delay(400);
    }
  }

}


//  -- END OF FILE --

