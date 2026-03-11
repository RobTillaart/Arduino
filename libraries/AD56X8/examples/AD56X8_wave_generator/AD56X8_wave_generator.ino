//
//    FILE: AD56X8_wave_generator.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo function generators
//     URL: https://github.com/RobTillaart/AD56X8
//     URL: https://github.com/RobTillaart/FunctionGenerator
//
//  depending on the platform, the range of "smooth" sinus is limited.
//  other signals are less difficult so have a slightly larger range.
//
//  PLATFORM     SINUS    SQUARE  SAWTOOTH  TRIANGLE
//  UNO
//  ESP32
//


#include "AD56X8.h"

AD56X8 AD16_SW(9, 10, 11);  //  SW SPI


//  frequency
//  use + - * /  to control it
uint16_t   freq = 100;
uint32_t period = 0;
uint32_t halvePeriod = 0;

//  amplitide
uint16_t maxAmplitude  = 32767;
uint16_t halfAmplitude = 16383;

//  q = square       z = zero
//  s = sinus        m = mid
//  w = sawtooth     h = high
//  t = stair
//  r = random
char waveFrom = 'q';

int channel = 0;
const int channelMax = 8;

uint16_t count;
uint32_t lastTime = 0;


//  LOOKUP TABLE SINE
uint16_t sine[361];


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD56X8_LIB_VERSION: ");
  Serial.println(AD56X8_LIB_VERSION);
  Serial.println();

  //  fill table
  for (int i = 0; i < 361; i++)
  {
    sine[i] = halfAmplitude + round(halfAmplitude * sin(i * PI / 180));
  }

  AD16_SW.begin();

  AD16_SW.setValue(channel, 0);

  period = 1e6 / freq;
  halvePeriod = period / 2;

  while (1)
  {
    yield();
    uint32_t now = micros();

    count++;

    if (now - lastTime > 100000)
    {
      lastTime = now;
      //  show # updates per 0.1 second
      //  Serial.println(count);
      count = 0;
      if (Serial.available())
      {
        int c = Serial.read();
        switch (c)
        {
          case '+':
            freq++;
            break;
          case '-':
            freq--;
            break;
          case '*':
            freq *= 10;
            break;
          case '/':
            freq /= 10;
            break;
          case '0' ... '9':
            freq *= 10;
            freq += (c - '0');
            break;
          case 'c':
            freq = 0;
            break;
          case 'C':
            channel = channel + 1;
            if (channel >= channelMax) channel = 0;
            break;
          case 'A':
            break;
          case 'a':
            break;
          case 'q':
          case 's':
          case 'w':
          case 't':
          case 'r':
          case 'z':
          case 'm':
          case 'h':
            waveFrom = c;
            break;
          default:
            break;
        }
        period = 1e6 / freq;
        halvePeriod = period / 2;
        Serial.print(freq);
        //        Serial.print('\t');
        //        Serial.print(period);
        //        Serial.print('\t');
        //        Serial.print(halvePeriod);
        Serial.println();
      }
    }

    uint32_t t = now % period;

    switch (waveFrom)
    {
      case 'q':
        if (t < halvePeriod ) AD16_SW.setValue(channel, maxAmplitude);
        else AD16_SW.setValue(channel, 0);
        break;
      case 'w':
        AD16_SW.setValue(channel, t * maxAmplitude / period );
        break;
      case 't':
        if (t < halvePeriod) AD16_SW.setValue(channel, t * maxAmplitude / halvePeriod);
        else AD16_SW.setValue(channel, (period - t) * maxAmplitude / halvePeriod );
        break;
      case 'r':
        AD16_SW.setValue(channel, random(4096));
        break;
      case 'z':  //  zero
        AD16_SW.setValue(channel, 0);
        break;
      case 'h':  //  high
        AD16_SW.setValue(channel, maxAmplitude);
        break;
      case 'm':  //  mid
        AD16_SW.setValue(channel, halfAmplitude);
        break;
      default:
      case 's':
        //  reference
        //  float f = ((PI * 2) * t)/period;
        //  AD16_SW.setValue(halfAmplitude + halfAmplitude * sin(f));
        //
        int idx = (360 * t) / period;
        AD16_SW.setValue(channel, sine[idx]);   //  fetch from lookup table
        break;
    }
  }
}


void loop()
{
}


//  -- END OF FILE --
