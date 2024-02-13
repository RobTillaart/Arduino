//
//      FILE: TLC5947_Daisy_Chain.ino
//    AUTHOR: Ricardo Franke
// PUBLISHER: Rob Tillaart
//   PURPOSE: Daisy_Chain_Demo
//       URL: https://github.com/RobTillaart/TLC5947


#include "TLC5947.h"

int DEVICES = 1;                          //  set Amount of TLC5947 Boards

int led = 24 * DEVICES;                   //  this set Amount of LEDs per Board

int wait = 100;                           //  set time between channel control
  

const int CLOCK = 13;
const int DATA  = 12;
const int LATCH = 11;
const int BLANK = 10;

TLC5947 tlc(DEVICES, CLOCK, DATA, LATCH, BLANK);

const int ZERO_B = 0;                     //  zero brightness
const int MAX_B = 4095;                   //  100% brightness
int a = MAX_B;                            //  current brightness

void setup()
{
  Serial.begin(115200);                   //  initialize Serial Output
  Serial.println(__FILE__);
  Serial.print("TLC5947_LIB_VERSION: \t");
  Serial.println(TLC5947_LIB_VERSION);

  tlc.begin();                            //  initialize TLC5947 library
  tlc.enable();
}


void loop()
{
  for (int i = 0; i < led; i++)
  {
    tlc.setPWM(i, a);
    delay(wait);
    tlc.write();
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(a);
  }
  a = (a > ZERO_B) ? ZERO_B : MAX_B;
}


//  -- END OF FILE --

