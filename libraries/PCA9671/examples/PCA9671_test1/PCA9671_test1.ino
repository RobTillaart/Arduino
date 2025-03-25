//
//    FILE: test1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PCA9671


#include "PCA9671.h"

//  adjust addresses if needed
PCA9671 PCA_20(0x20);  //  add switches to lines  (used as input)
PCA9671 PCA_21(0x21);  //  add LEDs to lines      (used as output)


void setup()
{
  //  while(!Serial);  //  uncomment when needed
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9671_LIB_VERSION:\t");
  Serial.println(PCA9671_LIB_VERSION);
  Serial.println();

  Wire.begin();

  PCA_20.begin();
  PCA_21.begin();

  uint16_t value = PCA_20.read16();
  Serial.print("#38:\t");
  Serial.println(value);

  for (int i = 0; i < 255; i++)
  {
    PCA_21.write16(i);
    delay(100);
  }

  PCA_21.write(0, 1);
  for (int i = 0; i < 15; i++)
  {
    PCA_21.shiftLeft();
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    PCA_21.shiftRight();
    delay(100);
  }

  for (int i = 0; i < 16; i++)
  {
    PCA_21.write(i, 1);
    delay(100);
    PCA_21.write(i, 0);
    delay(100);
  }

  for (int i = 0; i < 16; i++)
  {
    PCA_21.toggle(i);
    delay(100);
    PCA_21.toggle(i);
    delay(100);
  }
}


void loop()
{
  //  echoes the lines
  uint16_t value = PCA_20.read16();
  PCA_21.write16(value);
  delay(100);
}


//  -- END OF FILE --

