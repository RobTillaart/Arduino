//
//    FILE: M5ROTATE8_button_toggle_count.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo firmware V2 function
//     URL: https://github.com/RobTillaart/M5ROTATE8


#include "m5rotate8.h"


M5ROTATE8 MM;

int sum = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("M5ROTATE8_LIB_VERSION: ");
  Serial.println(M5ROTATE8_LIB_VERSION);
  delay(100);

  Wire.begin();
  MM.begin();
}


void loop()
{
  for (int channel = 0; channel < 8; channel++)
  {
    int x = MM.getButtonToggleCount(channel);
    sum += x;
    Serial.print(x);
    Serial.print("\t");
    delay(125);
  }
  Serial.println();

  //  time to reset?
  if (sum >= 25)  //  arbitrary condition.
  {
    sum = 0;
    for (int channel = 0; channel < 8; channel++)
    {
      MM.setButtonToggleCount(channel, 0);  //  explicit value
    }
  }
}


//  -- END OF FILE --
