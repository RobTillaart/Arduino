//
//    FILE: functionGenerator_double_MCP4725.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo function generators
//     URL: https://github.com/RobTillaart/FunctionGenerator
//
//  depending on the platform, the range of "smooth" sinus is limited.
//  other signals are less difficult so have a slightly larger range.
//  see readme.md for mac frequency table.


#include "functionGenerator.h"
#include "MCP4725.h"
#include "Wire.h"


//  two generators
funcgen gen1;
funcgen gen2;

//  two ADC
MCP4725 MCP1(0x63);
MCP4725 MCP2(0x64);

uint32_t count = 0;
uint32_t lastTime = 0;
uint32_t t = 0;

void setup()
{
  Serial.begin(230400);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();

  Wire.begin();
  MCP1.begin();
  MCP2.begin();
  Wire.setClock(100000);

//  if (!MCP1.isConnected())
//  {
//    Serial.println("error 1!");
//    while (1);
//  }
  MCP1.setValue(0);

//  if (!MCP2.isConnected())
//  {
//    Serial.println("error 2!");
//    while (1);
//  }
  MCP2.setValue(0);

  //  set 5 Hz
  gen1.setAmplitude(1023);
  gen1.setYShift(1023);
  gen1.setFrequency(5);

  //  set 10 Hz
  gen2.setAmplitude(1023);
  gen2.setYShift(1023);
  gen2.setFrequency(10);
  gen2.setPhase(0.025);
}


void loop()
{
  uint32_t now = micros();
  if (now - lastTime >= 1000)
  {
    lastTime = now;
    float t = millis() * 0.0001;
    MCP1.setValue(gen1.square(t));
    MCP2.setValue(gen2.sinus(t));

//    Serial.print(gen1.square(t));
//    Serial.print("\t");
//    Serial.print(gen2.sinus(t));
//    Serial.println();
  }
}


//  -- END OF FILE --
