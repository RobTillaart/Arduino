//
//    FILE: DS3502_wave_generator.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo function generators
//     URL: https://github.com/RobTillaart/DS3502
//     URL: https://github.com/RobTillaart/FunctionGenerator
//
//  depending on the platform, the range of "smooth" sinus is limited.
//  other signals are less difficult so have a slightly larger range.
//


#include "DS3502.h"
#include "Wire.h"

//  frequency
//  use + - * /  to control it
uint16_t   freq = 100;
uint32_t period = 0;
uint32_t halvePeriod = 0;


//  q = square       z = zero
//  s = sinus        m = mid
//  w = sawtooth     h = high
//  t = stair
//  r = random
char waveFrom = 'q';


DS3502 DS(0x28);
uint16_t count;
uint32_t lastTime = 0;


//  LOOKUP TABLE SINE
uint16_t sine[361];

const uint8_t MAX_VALUE = 127;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS3502_LIB_VERSION: ");
  Serial.println(DS3502_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);

  //  fill table
  for (int i = 0; i < 361; i++)
  {
    sine[i] = MAX_VALUE / 2 + round(MAX_VALUE / 2 * sin(i * PI / 180));
  }

  while (!DS.begin())
  {
    Serial.println("Error connect.");
    delay(100);
  }
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
        if (t < halvePeriod ) DS.setValue(MAX_VALUE);
        else DS.setValue(0);
        break;
      case 'w':
        DS.setValue(t * MAX_VALUE / period );
        break;
      case 't':
        if (t < halvePeriod) DS.setValue(t * MAX_VALUE / halvePeriod);
        else DS.setValue( (period - t) * MAX_VALUE / halvePeriod );
        break;
      case 'r':
        DS.setValue(random(MAX_VALUE));
        break;
      case 'z':  //  zero
        DS.setValue(0);
        break;
      case 'h':  //  high
        DS.setValue(MAX_VALUE);
        break;
      case 'm':  //  mid
        DS.setValue(MAX_VALUE / 2);
        break;
      default:
      case 's':
        //  reference
        //  float f = ((PI * 2) * t)/period;
        //  DS.setValue(MAX_VALUE/2 + MAX_VALUE/2 * sin(f));
        //
        int idx = (360 * t) / period;
        DS.setValue(sine[idx]);   //  fetch from lookup table
        break;
    }
  }
}


void loop()
{
}


//  -- END OF FILE --
