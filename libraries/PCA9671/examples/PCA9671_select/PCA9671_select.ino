//
//    FILE: PCA9671_select.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PCA9671 library select functions
//     URL: https://github.com/RobTillaart/PCA9671


#include "PCA9671.h"

PCA9671 PCA(0x20);

uint32_t start, stop;


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
  Serial.println(PCA.isConnected());
  Serial.println();

  PCA.selectAll();
  delay(1000);
  PCA.selectNone();
  delay(1000);

  //  VU meter up
  for (int i = 0; i < 15; i++)
  {
    PCA.selectN(i);
    delay(100);
  }

  //  VU meter down
  for (int i = 15; i >= 0; i--)
  {
    PCA.selectN(i);
    delay(100);
  }
}


void loop()
{
  //  night rider
  for (int i = 0; i < 15; i++)
  {
    PCA.select(i);
    delay(100);
  }
  for (int i = 15; i >= 0; i--)
  {
    PCA.select(i);
    delay(100);
  }
}


//  -- END OF FILE --

