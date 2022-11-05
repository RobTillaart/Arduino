//
//    FILE: fastShiftIn_test_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test sketch
//     URL: https://github.com/RobTillaart/FastShiftIn


#include "FastShiftIn.h"

FastShiftIn FSI(8, 9);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(FASTSHIFTIN_LIB_VERSION);

  uint8_t x = FSI.read();
  Serial.println(x, HEX);
  
  x = FSI.readLSBFIRST();
  Serial.println(x, HEX);

  x = FSI.readMSBFIRST();
  Serial.println(x, HEX);

  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --
