//
//    FILE: ADG2128_latch_mode.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ADG2128


#include "ADG2128.h"


ADG2128 sw(0x70);  //  explicit address

//  switches to set simultaneously
int switches[10] = { 2,3,5,7, 11,13,17,19, 23,29 };


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ADG2128_LIB_VERSION: ");
  Serial.println(ADG2128_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (sw.begin() == false)
  {
    Serial.println("Error connecting to device");
    while(1);
  }
}


void loop()
{
  //  should switch immediately on per second.
  sw.setDirectMode();
  for (int p = 0; p < 10; p++)
  {
    sw.on(switches[p]);
    delay(1000);
  }
  for (int p = 0; p < 10; p++)
  {
    sw.off(switches[p]);
    delay(1000);
  }


  //  should switch all after 5 seconds
  sw.setLatchMode();
  for (int p = 0; p < 10; p++)
  {
    sw.on(switches[p]);
  }
  delay(5000);
  //  use direct mode to set all switches latched
  //  might need to find a better way.
  sw.setDirectMode();
  sw.on(switches[9]);
  sw.setLatchMode();
  for (int p = 0; p < 10; p++)
  {
    sw.off(switches[p]);
  }
   delay(5000);
  //  use direct mode to set all switches
  sw.setDirectMode();
  sw.off(switches[9]);
}


//  -- END OF FILE --
