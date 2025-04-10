//
//    FILE: ADG2188_isOnRow.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ADG2128


#include "ADG2188.h"


ADG2188 sw(0x70);  //  explicit address


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ADG2188_LIB_VERSION: ");
  Serial.println(ADG2188_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (sw.begin() == false)
  {
    Serial.println("Error connecting to device");
    while (1);
  }

}


void loop()
{
  int x = random(96);
  sw.on(x);

  //  not very efficient but it works.
  for (int i = 0; i < 64; i++)
  {
    if (sw.isOn(i))
    {
      Serial.print(i);
      Serial.println(" is on.");
    }
  }
  sw.off(x);

  delay(2000);
}


//  -- END OF FILE --
