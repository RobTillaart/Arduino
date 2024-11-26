//
//    FILE: PCA9632_test.ino
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

  //  test all channel, all levels
  for (int channel = 0; channel < 4; channel++)
  {
    for (int brightness = 0; brightness < 256; brightness++)
    {
      pca.write(channel, brightness);
      delay(10);
    }
    pca.write(channel, 0);
  }
  delay(1000);

  //  blink 5 times
  for (int i = 0; i < 5; i++)
  {
    pca.setLedDriverModeAll(PCA9632_LEDON);
    delay(500);
    pca.setLedDriverModeAll(PCA9632_LEDOFF);
    delay(500);
  }
  delay(1000);


  pca.setLedDriverModeAll(PCA9632_LEDPWM);
}


void loop()
{
  //  random colours
  pca.writeR(random(255));
  pca.writeG(random(255));
  pca.writeB(random(255));
  pca.writeW(random(255));
  delay(1000);
}


//  -- END OF FILE --
