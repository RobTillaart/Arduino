//
//    FILE: TLC5947_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test performance main functions.
//     URL: https://github.com/RobTillaart/TLC5947


#include "TLC5947.h"

//  UNO can do ~30,  ESP32 can do 200++
const int DEVICES = 1;
const int CLOCK = 13;
const int DATA  = 12;
const int LATCH = 11;
const int BLANK = 10;

TLC5947 tlc(DEVICES, CLOCK, DATA, LATCH, BLANK);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5947_LIB_VERSION: \t");
  Serial.println(TLC5947_LIB_VERSION);

  if (tlc.begin() == false)
  {
    Serial.println("error");
    while (1);
  }

  Serial.print("Channels: ");
  Serial.println(tlc.getChannels());

  tlc.enable();

  testSetPWM();
  testSetRGB();
  testWrite();

  Serial.println("\nDone...");
}


void loop()
{
}


void testSetPWM()
{
  delay(100);
  int channels = tlc.getChannels();
  start = micros();
  for (int channel = 0; channel < channels; channel++)
  {
    tlc.setPWM(channel, 42);
  }
  stop = micros();
  Serial.print("SETPWM\t");
  Serial.println(stop - start);
}


void testSetRGB()
{
  delay(100);
  int leds = tlc.getChannels() / 3;
  start = micros();
  for (int led = 0; led < leds; led++)
  {
    tlc.setRGB(led, 42, 185, 17);
  }
  stop = micros();
  Serial.print("SETRGB\t");
  Serial.println(stop - start);
}


void testWrite()
{
  delay(100);
  start = micros();
  tlc.write();
  stop = micros();
  Serial.print("WRITE\t");
  Serial.println(stop - start);
}


//  -- END OF FILE --
