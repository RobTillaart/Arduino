//
//    FILE: FastShiftInOut_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test sketch
//     URL: https://github.com/RobTillaart/FastShiftInOut
//
//  loopback test
//  connect pin 8 and 9 by a wire
//  ==> the send and recv bytes should be identical


#include "FastShiftInOut.h"


FastShiftInOut FSIO(8, 9, 10, LSBFIRST);


void setup()
{
  Serial.begin(115200);
  Serial.print("\nFASTSHIFTINOUT_LIB_VERSION: ");
  Serial.println(FASTSHIFTINOUT_LIB_VERSION);


  Serial.println("\nwrite");
  uint8_t recv = 0;
  for (int send = 0; send < 256; send++)
  {
    recv = FSIO.write(send);
    Serial.print(send, HEX);
    Serial.print("\t");
    Serial.print(recv, HEX);
    Serial.println();
  }


  Serial.println("\nwriteLSBFIRST");
  recv = 0;
  for (int send = 0; send < 256; send++)
  {
    recv = FSIO.writeLSBFIRST(send);
    Serial.print(send, HEX);
    Serial.print("\t");
    Serial.print(recv, HEX);
    Serial.println();
  }


  Serial.println("\nwriteMSBFIRST");
  recv = 0;
  for (int send = 0; send < 256; send++)
  {
    recv = FSIO.writeMSBFIRST(send);
    Serial.print(send, HEX);
    Serial.print("\t");
    Serial.print(recv, HEX);
    Serial.println();
  }

  Serial.println("\ndone ...");
}


void loop()
{
}


//  -- END OF FILE --

