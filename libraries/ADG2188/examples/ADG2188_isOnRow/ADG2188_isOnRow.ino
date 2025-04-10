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
  //  switch one random switch on
  //  and switch one random switch off
  //  should give a dynamic matrix
  sw.on(random(64));
  sw.off(random(64));

  for (int row = 0; row < 8; row++)
  {
    printMask(sw.isOnRow(row));
  }
  Serial.println();
  Serial.println();

  delay(2000);
}


void printMask(uint8_t value)
{
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    if (value & mask) Serial.print(1);
    else Serial.print(0);
  }
  Serial.println();
}

//  -- END OF FILE --
