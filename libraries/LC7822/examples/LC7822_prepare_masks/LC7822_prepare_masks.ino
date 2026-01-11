//
//    FILE: LC7822_prepare_masks.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo masks
//     URL: https://github.com/RobTillaart/LC7822
//
//  Has an array of prepared masks which will be walked
//  through after receiving a byte over Serial.


#include "LC7822.h"

//  LC7822(dataPin, clockPin, cePin, sPin, resetPin);
LC7822 LC(4,5,6,7);  //  no reset Pin.

//  prepared masks
uint8_t masks[10] = { 0x00, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xFF, 0x55};
uint8_t idx = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LC7822_LIB_VERSION: ");
  Serial.println(LC7822_LIB_VERSION);
  Serial.println();

  if (LC.begin() == false)
  {
    Serial.println("error begin()");
  }
  //  tune timing.
  LC.setMicroDelay(10);
}


void loop()
{
  if (Serial.available())
  {
    Serial.read();
    LC.setAll(masks[idx]);
    idx++;
    if (idx >= 10) idx = 0;
  }
}


//  -- END OF FILE --
