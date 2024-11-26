//
//    FILE: PCA9632_simple.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PCA9632


#include "Wire.h"
#include "PCA9632.h"


PCA9633 pca(0x60, &Wire);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PCA9632_LIB_VERSION: ");
  Serial.println(PCA9632_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (pca.begin() == false)
  {
    Serial.println("Check wiring and reboot");
    while (1);
  }
}


void loop()
{
  pca.write(random(255), random(255), random(255), random(255));
  delay(1000);
}


//  -- END OF FILE --
