//    FILE: MINIMP3_random.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: play random from SD card
//     URL: https://github.com/RobTillaart/MINIMP3
//
//
//            MINI MP3
//         +-----__-----+
//    VCC  |            |  BUSY
//     RX  |            |  USB-
//     TX  |            |  USB+
//  DAC_R  |            |  ADKEY_2
//  DAC_L  |  +------+  |  ADKEY_1
//  SPK_1  |  |      |  |  IO_2
//    GND  |  |  SD  |  |  GND
//  SPK_2  |  | CARD |  |  IO_1
//         +--+------+--+
//
//  When connecting to a 5V MCU, you need to add a 1K resistor between
//  the Serial TX and RX as the MINIMP3 is 3V3. Otherwise a big HUM.
//

#include "Arduino.h"
#include "MiniMP3.h"
#include "SoftwareSerial.h"

SoftwareSerial sws(6, 7);  //  RX, TX


MINIMP3 MP3(&sws);

//  adjust to SD card, 2999 is absolute max.
//  file layout SD:\xxxx.mp3
const uint16_t MAX_TRACK = 2999;
const int BUSY_PIN = 8;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);

  pinMode(BUSY_PIN, INPUT_PULLUP);
  sws.begin(9600);

  MP3.reset();
  delay(3000);
  MP3.volume(10);
}


void loop()
{
  if (digitalRead(BUSY_PIN) == HIGH)  //  LOW ==> playing
  {
    MP3.play(random(MAX_TRACK));
  }
}


//  -- END OF FILE --
