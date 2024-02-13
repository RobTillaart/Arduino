//
//    FILE: TLC5947_percentage.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo percentage interface
//     URL: https://github.com/RobTillaart/TLC5947


#include "TLC5947.h"

const int DEVICES = 2;
const int CLOCK = 13;
const int DATA  = 12;
const int LATCH = 11;
const int BLANK = 10;

TLC5947 tlc(DEVICES, CLOCK, DATA, LATCH, BLANK);


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

  for (int channel = 0; channel < tlc.getChannels(); channel++)
  {
    int pwm = random(4096);
    tlc.setPWM(channel, pwm);
    Serial.print(channel);
    Serial.print('\t');
    Serial.print(pwm);
    Serial.print('\t');
    Serial.print(tlc.getPWM(channel));
    Serial.println();
  }
  Serial.println();

  for (int channel = 0; channel < tlc.getChannels(); channel++)
  {
    float percentage = random(10000) * 0.01;
    tlc.setPercentage(channel, percentage);
    Serial.print(channel);
    Serial.print('\t');
    Serial.print(percentage);
    Serial.print('\t');
    Serial.print(tlc.getPercentage(channel));
    Serial.println();
  }
  tlc.write();

  Serial.println("\ndone...");
}


void loop()
{

}


//  -- END OF FILE --
