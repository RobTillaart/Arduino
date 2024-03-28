//
//    FILE: KT0803_up_down.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//     URL: https://github.com/RobTillaart/KT0803


#include "Arduino.h"
#include "Wire.h"
#include "KT0803.h"


KT0803 FM_SEND;

//  connect two buttons to GND
//  adjust pins to your needs,
uint8_t UP_PIN = 6;
uint8_t DOWN_PIN = 7;
float freq = 100.0;
float newFreq = 100.0;


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  Wire.begin();

  FM_SEND.begin(freq, false);
}


void loop()
{
  //  adjust frequency with up and down button.
  uint8_t u = digitalRead(UP_PIN);
  uint8_t d = digitalRead(DOWN_PIN);
  if ((u == 0) && (d == 0))
  {
    newFreq = 100.0;
  }
  else if (u == 0)
  {
    newFreq += 0.1;
    if (newFreq > 108.0) newFreq = 108.0;
  }
  else if (d == 0)
  {
    newFreq -= 0.1;
    if (newFreq < 88.0) newFreq = 88.0;
  }
  if (newFreq != freq)
  {
    freq = newFreq;
    FM_SEND.setFrequency(freq);

    Serial.print("Freq: ");
    Serial.print(FM_SEND.getFrequency());
    Serial.print("\t");
    Serial.println(FM_SEND.getChannel());

    delay(100);
  }
}


//  -- END OF FILE --
