//
//    FILE: functionGenerator_MCP4725.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo function generators
//    DATE: 2021-01-06
//     URL: https://github.com/RobTillaart/FunctionGenerator
//
//  depending on the platform, the range of "smooth" sinus is limited.
//  other signals are less difficult so have a slightly larger range.
//  
//  PLATFORM     RANGE          Points/sec    Points/period
//  UNO          - 25 Hz        ~1900         ~75
//  ESP32        to be tested
//

#include "functionGenerator.h"
#include "MCP4725.h"
#include "Wire.h"

funcgen gen;
float val   = 0;
float freq = 40;
float amp  = 1.0;

// q = square
// s = sinus
// w = sawtooth
// t = stair
// r = random
char mode = 's';

MCP4725 MCP(0x63);
uint32_t count;
uint32_t lastTime = 0;

void setup()
{
  Serial.begin(230400);
  gen.setAmplitude(1);
  gen.setYShift(1);
  gen.setFrequency(freq);
  val = 0;

  Wire.begin();
  MCP.begin();
  Wire.setClock(100000);

  MCP.setValue(0);
  if (!MCP.isConnected())
  {
    Serial.println("err");
    while (1);
  }

  while (1)
  {
    count++;
    float t = micros() * 0.000001;
    if (millis() - lastTime > 1000)
    {
      Serial.println(count);
      count = 0;
      lastTime = millis();
    }

    if (Serial.available())
    {
      int c = Serial.read();
      switch (c)
      {
        case '+':
          freq += 0.01;
          break;
        case '-':
          freq -= 0.01;
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
          mode = c;
          break;
        default:
          break;
      }
      gen.setFrequency(freq);
      Serial.println(freq);
    }

    switch (mode)
    {
      case 'q':
        val = 2047 * gen.square(t);
        break;
      case 'w':
        val = 2047 * gen.sawtooth(t);
        break;
      case 't':
        val = 2047 * gen.triangle(t);
        break;
      case 'r':
        val = 2047 * gen.random();
        break;
      default:
      case 's':
        val = 2047 *  gen.sinus(t);
        break;
    }
    MCP.setValue(val);
  }
}


void loop()
{
}

// END OF FILE
