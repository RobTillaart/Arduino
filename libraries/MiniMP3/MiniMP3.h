#pragma once
//
//    FILE: MiniMP3.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino library for DFRobotics MP3 player and compatibles.
//     URL: https://github.com/RobTillaart/MINIMP3


#include "Arduino.h"

#define MINIMP3_LIB_VERSION     (F("0.1.3"))


//  EQUALIZER MODI
#define MP3_EQ_NORMAL           0
#define MP3_EQ_POP              1
#define MP3_EQ_ROCK             2
#define MP3_EQ_JAZZ             3
#define MP3_EQ_CLASSIC          4
#define MP3_EQ_BASS             5


//  PLAYBACK MODI
//  to be implemented
#define MP3_MODE_REPEAT         0
#define MP3_MODE_FREPEAT        1
#define MP3_MODE_SREPEAT        2
#define MP3_MODE_RANDOM         3


//  PLAYBACK SOURCE
//  to be implemented?
#define MP3_DEVICE_U            0
#define MP3_DEVICE_TF           1
#define MP3_DEVICE_AUX          2
#define MP3_DEVICE_SLEEP        3
#define MP3_DEVICE_FLASH        4


class MINIMP3
{
public:
  MINIMP3(Stream * stream = &Serial);

  //  plays SD:/MP3/####.mp3
  void play(uint16_t track);
  //  void playFolder(uint8_t folder, uint8_t track);
  void next();
  void prev();
  void stop();
  void pause();

  void reset();
  void lowPower();

  //  volume = 0.. 30
  void volume(uint16_t vol = 0);
  void volumeUp();
  void volumeDown();

  //  mode = 0..5
  void equalizer(uint8_t mode = MP3_EQ_NORMAL);


private:
  Stream  * _stream;

  void command(uint8_t cmd, uint16_t arg = 0x0000);
  void command(uint8_t cmd, uint8_t arg1, uint8_t arg2);
};


//  -- END OF FILE --

