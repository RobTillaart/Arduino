//
//    FILE: TLC5917_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test performance main functions.
//     URL: https://github.com/RobTillaart/TLC5917


#include "TLC5917.h"


const int DEVICES = 100;
const int CLOCK   = 13;
const int DATA    = 12;
const int LATCH   = 11;
const int ENABLE  = 10;

TLC5916 tlc(DEVICES, CLOCK, DATA, LATCH, ENABLE);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5917_LIB_VERSION: \t");
  Serial.println(TLC5917_LIB_VERSION);
  Serial.println();

  if (tlc.begin() == false)
  {
    Serial.println("Error");
    while (1);
  }

  Serial.print("Channels:\t\t");
  Serial.println(tlc.channelCount());

  tlc.enable();

  testSetChannel();
  testWrite();

  Serial.println("\nDone...");
}


void loop()
{
}


void testSetChannel()
{
  delay(100);
  int channels = tlc.channelCount();
  start = micros();
  for (int channel = 0; channel < channels; channel++)
  {
    tlc.setChannel(channel, true);
  }
  stop = micros();
  Serial.print("SETCHANNEL TRUE:\t");
  Serial.println(stop - start);
  tlc.write();
  delay(100);

  start = micros();
  for (int channel = 0; channel < channels; channel++)
  {
    tlc.setChannel(channel, false);
  }
  stop = micros();
  Serial.print("SETCHANNEL FALSE:\t");
  Serial.println(stop - start);
  tlc.write();
  delay(100);

  start = micros();
  tlc.setAll(true);
  stop = micros();
  Serial.print("SETALL TRUE:\t\t");
  Serial.println(stop - start);
  tlc.write();
  delay(100);

  start = micros();
  tlc.setAll(false);
  stop = micros();
  Serial.print("SETALL FALSE:\t\t");
  Serial.println(stop - start);
  tlc.write();
  delay(100);
}


void testWrite()
{
  delay(100);
  start = micros();
  tlc.write();
  stop = micros();
  Serial.print("WRITE:\t\t\t");
  Serial.println(stop - start);
  delay(100);
}


//  -- END OF FILE --
