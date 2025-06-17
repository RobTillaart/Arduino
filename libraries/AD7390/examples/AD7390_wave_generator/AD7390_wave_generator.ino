//
//    FILE: AD7390_wave_generator.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo function generators
//     URL: https://github.com/RobTillaart/AD7390
//     URL: https://github.com/RobTillaart/FunctionGenerator
//
//  depending on the platform, the range of "smooth" sinus is limited.
//  other signals are less difficult so have a slightly larger range.
//
//  PLATFORM     SINUS    SQUARE  SAWTOOTH  TRIANGLE
//  UNO          -100 Hz
//  ESP32        -200 Hz  -1000   -250      -100


#include "AD7390.h"


uint16_t     freq = 10;
uint32_t   period = 0;
uint32_t   halvePeriod = 0;


//  q = square
//  s = sinus
//  w = sawtooth
//  t = triangle
//  r = random
char mode = 'q';


//  select, reset, data, clock == SOFTWARE SPI
//  AD7390 myDAC(6, 7, 11, 13);

//  select, reset, &SPI === HW SPI UNO clock = 13, data = 11
AD7390 myDAC(6, 7, &SPI);

uint16_t count;
uint32_t lastTime = 0;


// LOOKUP TABLE SINE
uint16_t sine[361];


void setup()
{
  Serial.begin(115200);

  //  fill table with sinus values for fast lookup
  for (int i = 0; i < 361; i++)
  {
    sine[i] = 2047 + round(2047 * sin(i * PI / 180));
  }

  SPI.begin();

  myDAC.begin(0);
  myDAC.setValue(0);

  period = 1e6 / freq;
  halvePeriod = period / 2;

  while (1)
  {
    //  Serial.println(analogRead(A0));   //  read output back via A0.
    yield();
    uint32_t now = micros();

    count++;

    if (now - lastTime > 100000)
    {
      lastTime = now;
      //  Serial.println(count);  //  show # updates per 0.1 second
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
            mode = c;
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

    switch (mode)
    {
      case 'q':
        if (t < halvePeriod ) myDAC.setValue(4095);
        else myDAC.setValue(0);
        break;
      case 'w':
        myDAC.setValue(t * 4095 / period );
        break;
      case 't':
        if (t < halvePeriod) myDAC.setValue(t * 4095 / halvePeriod);
        else myDAC.setValue( (period - t) * 4095 / halvePeriod );
        break;
      case 'r':
        myDAC.setValue(random(4096));
        break;
      case 'z':  //  zero
        myDAC.setValue(0);
        break;
      case 'h':  //  high
        myDAC.setValue(4095);
        break;
      case 'm':  //  mid
        myDAC.setValue(2047);
        break;
      default:
      case 's':
        //  reference
        //  float f = ((PI * 2) * t)/period;
        //  myDAC.setValue(2047 + 2047 * sin(f));
        //
        int idx = (360 * t) / period;
        myDAC.setValue(sine[idx]);  //  lookup table
        break;
    }
  }
}


void loop()
{
}


//  -- END OF FILE --
