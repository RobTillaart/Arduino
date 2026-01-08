//
//    FILE: SD2405_test_RCTF.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test RTCF function
//     URL: https://github.com/RobTillaart/SD2405
//
//  To elaborate


#include "SD2405.h"

SD2405 rtc;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SD2405_LIB_VERSION: ");
  Serial.println(SD2405_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (rtc.begin() != SD2405_OK)
  {
    Serial.println("could not connect, check wires etc");
    // while (1);
  }

}


void loop()
{
  int x = rtc.getRCTF();
  Serial.println(x);
  delay(5000);
}


//  --  END OF FILE  --