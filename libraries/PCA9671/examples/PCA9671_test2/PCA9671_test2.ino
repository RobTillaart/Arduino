//
//    FILE: PCA9671_test2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo rotateLeft, -Right and toggleMask
//     URL: https://github.com/RobTillaart/PCA9671


#include "PCA9671.h"

//  adjust addresses if needed
PCA9671 PCA(0x20);  //  add LEDs to lines      (used as output)


void setup()
{
  //  while(!Serial);  //  uncomment when needed
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9671_LIB_VERSION:\t");
  Serial.println(PCA9671_LIB_VERSION);
  Serial.println();

  Wire.begin();

  PCA.begin();

  PCA.write(0, 1);
  for (int i = 0; i < 15; i++)
  {
    PCA.rotateLeft();
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    PCA.rotateRight();
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    PCA.rotateLeft(3);
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    PCA.rotateRight(2);
    delay(100);
  }

  for (uint16_t i = 0; i < 65535; i += 253)
  {
    PCA.toggleMask(i);
    delay(100);
  }

  //  0010 0111  -> 0x27
  //  1110 0100
  PCA.write16(0x2755);
  for (int i = 0; i < 255; i++)
  {
    PCA.reverse();
    delay(100);
  }
}


void loop()
{
}


//  -- END OF FILE --

