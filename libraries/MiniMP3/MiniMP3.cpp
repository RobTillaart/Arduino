//
//    FILE: MiniMP3.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino library for DFRobotics MP3 player and compatibles.


#include "MiniMP3.h"


//  CONSTANTS
#define MP3_MAX_VOLUME      30


//  COMMANDS
#define MP3_NEXT            0x01
#define MP3_PREV            0x02
#define MP3_PLAY            0x03
#define MP3_VOL_INCR        0x04
#define MP3_VOL_DECR        0x05
#define MP3_VOL_SET         0x06
#define MP3_EQUAL           0x07
#define MP3_PLAYMODE        0x08
#define MP3_PLAYSOURCE      0x09
#define MP3_LOWPOWER        0x0A
#define MP3_POWER           0x0B
#define MP3_RESET           0x0C
#define MP3_PLAYBACK        0x0D
#define MP3_PAUSE           0x0E
#define MP3_PLAY_FOLDER     0x0F
#define MP3_VOL_ADJUST_SET  0x10
#define MP3_REPEAT          0x11


//  QUERIES
//  not supported (yet)



/////////////////////////////////////////////////////
//
// PUBLIC
//
MINIMP3::MINIMP3(Stream * stream)
{
  _stream = stream;
}


/////////////////////////////////////////////////////
//
//  PLAY
//
void MINIMP3::play(uint16_t track)
{
  command(MP3_PLAY, track);
}

// void MINIMP3::playFolder(uint8_t folder, uint8_t track)
// {
  // command(MP3_PLAY_FOLDER, folder, track);
// }

void MINIMP3::next()
{
  command(MP3_NEXT);
}

void MINIMP3::prev()
{
  command(MP3_PREV);
}

void MINIMP3::stop()
{
  command(0x15);
}


/////////////////////////////////////////////////////
//
//  CONTROL
//
void MINIMP3::pause()
{
  command(MP3_PAUSE);
}

void MINIMP3::reset()
{
  command(MP3_RESET);
}

void MINIMP3::lowPower()
{
  command(MP3_LOWPOWER);
}


/////////////////////////////////////////////////////
//
//  VOLUME
//
void MINIMP3::volume(uint16_t vol)
{
  if (vol > MP3_MAX_VOLUME) vol = MP3_MAX_VOLUME;
  command(MP3_VOL_SET, 256 + vol);
}

void MINIMP3::volumeUp()
{
  command(MP3_VOL_INCR);
}

void MINIMP3::volumeDown()
{
  command(MP3_VOL_DECR);
}


/////////////////////////////////////////////////////
//
//  EQUALIZER
//
void MINIMP3::equalizer(uint8_t mode)
{
  if (mode > 5) mode = MP3_EQ_NORMAL;
  command(MP3_EQUAL, mode);
}



/////////////////////////////////////////////////////
//
//  PRIVATE
//
void MINIMP3::command(uint8_t cmd, uint16_t arg)
{
  uint8_t arg2 = arg & 0xFF;
  uint8_t arg1 = arg >> 8;
  command(cmd, arg1, arg2);
}


void MINIMP3::command(uint8_t cmd, uint8_t arg1, uint8_t arg2)
{
  uint8_t buffer[10] = {0x7E,    //  Start == $
                        0xFF,    //  version
                        0x06,    //  length
                        cmd,
                        0x00,    //  0 = no feedback
                        arg1,    //  param 1
                        arg2,    //  param 2
                        0x00,    //  CheckSumHigh
                        0x00,    //  CheckSumLow
                        0xEF     //  End Byte
                        };

  uint16_t chksum  = 0;
  for (int i = 1; i < 7; i++ )
  {
    chksum += buffer[i];
  }
  chksum = -chksum;
  buffer[7] = (chksum >> 8);      //  CheckSumHigh
  buffer[8] = (chksum & 0xFF);    //  CheckSumLow

  _stream->write(buffer, 10);
}


//  --  END OF FILE  --

