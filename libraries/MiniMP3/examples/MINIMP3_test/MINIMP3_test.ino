//    FILE: MINIMP3_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
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

uint8_t vol = 10;
uint8_t eq = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);

  sws.begin(9600);

  MP3.reset();
  delay(3000);
  MP3.play(1);
  MP3.volume(10);
}


void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();
    switch (c)
    {
      case '0'...'9':
        MP3.play(c - '0');
        break;
      case 'n':
        MP3.next();
        break;
      case 'p':
        MP3.prev();
        break;
      case '+':
        if (vol < 20) vol++;
        MP3.volume(vol);
        break;
      case '-':
        if (vol > 0) vol--;
        MP3.volume(vol);
        break;
      case 'e':
        if (eq > 5) eq = 0;
        MP3.equalizer(eq);
        break;
      case 's':
        MP3.pause();
        break;
      case '?':
        Serial.println("0..9 play song");
        Serial.println("n = next");
        Serial.println("p = previous");
        Serial.println("+ = volume up");
        Serial.println("- = volume down");
        Serial.println("e = next equalizer");
        Serial.println("s = stop");
        break;
    }
  }
}


//  -- END OF FILE --
