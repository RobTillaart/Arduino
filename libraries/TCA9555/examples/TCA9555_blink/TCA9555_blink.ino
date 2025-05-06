//
//    FILE: TCA9555_blink.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: quick test TCA9555
//     URL: https://github.com/RobTillaart/TCA9555


#include "TCA9555.h"

//  adjust address if needed
TCA9555 TCA(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9555_LIB_VERSION: ");
  Serial.println(TCA9555_LIB_VERSION);
  Serial.println();

  Wire.begin();
  TCA.begin();

  Wire.setClock(50000);

  Serial.println("pinMode16(0x0000)");
  TCA.pinMode16(0x0000);
}


void loop()
{
  TCA.write16(0xFFFF);
  Serial.println("HIGH");
  delay(2000);

  TCA.write16(0x0000);
  Serial.println("LOW");
  delay(1000);
  Serial.println();
}


//  -- END OF FILE --
