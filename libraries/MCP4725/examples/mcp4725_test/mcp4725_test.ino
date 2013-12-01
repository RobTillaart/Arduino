//
//    FILE: mcp4725_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: test mcp4725 lib
//    DATE: 2013-11-24
//     URL:
//
// Released to the public domain
//

#include <Wire.h>
#include "MCP4725.h"

MCP4725 DAC(0x62);  // 0x62 or 0x63

void setup() 
{
  Serial.begin(115200);

  Serial.print("MCP4725 test program: ");
  Serial.println(MCP4725_VERSION);

  DAC.begin();

  Serial.print("\nValue:\t");
  Serial.println(DAC.getValue());
  Serial.println();

  for (int i=100; i<500; i+=100)
  {
    Serial.print("setValue(");
    Serial.print(i);
    Serial.print(")\n");
    DAC.setValue(i);
    Serial.print("Value:\t");
    Serial.println(DAC.getValue());
  }
  Serial.println();

#ifdef MCP4725_EXTENDED
  Serial.println("\n\nMCP4725_EXTENDED\n\n");

  Serial.println("smooth2Value(2000, 10)");
  DAC.smooth2Value(2000, 10);
  Serial.print("Value:\t");
  Serial.println(DAC.getValue());
  Serial.println();

  for (int i=100; i<500; i+=100)
  {
    Serial.print("writeDAC(");
    Serial.print(i);
    Serial.print(")\n");
    DAC.writeDAC(i);
    Serial.print("DACValue:\t");
    Serial.println(DAC.readDAC());
    Serial.print("EEValue:\t");
    Serial.println(DAC.readEEPROM());  
  }
  Serial.println();

  for (int i=100; i<500; i+=100)
  {
    Serial.print("writeDAC(");
    Serial.print(i);
    Serial.print(", true)\n");
    DAC.writeDAC(i, true);
    Serial.print("DACValue:\t");
    Serial.println(DAC.readDAC());
    Serial.print("EEValue:\t");
    Serial.println(DAC.readEEPROM());  
  }
  Serial.println();

  Serial.println("writeDAC(200)");
  DAC.writeDAC(200);
  Serial.print("DACValue:\t");
  Serial.println(DAC.readDAC());
  Serial.print("EEValue:\t");
  Serial.println(DAC.readEEPROM());  
  Serial.println();

#endif

#ifdef MCP4725_POWERDOWNMODE
  Serial.println("\n\nMCP4725_POWERDOWNMODE\n\n");

  /*
    int writePowerDownMode(uint8_t PDM);
   uint8_t readPowerDownMode();
   int powerOnReset();
   int powerOnWakeUp();
   */

#endif

  //////////////////////////////////////////////////
  Serial.println("\n\nPERFORMANCE\n");
  Serial.print("TWBR:\t");
  Serial.println(TWBR);
  Serial.println();

  uint32_t start = micros();
  for (int i=0; i< 1000; i++)
  {
    volatile int x = DAC.getValue();
  }
  uint32_t end = micros();
  Serial.print("1000x DAC.getValue():\t\t");
  Serial.println(end - start);

  start = micros();
  for (int i=0; i< 1000; i++)
  {
    DAC.setValue(i);
  }
  end = micros();
  Serial.print("1000x DAC.setValue(i):\t\t");
  Serial.println(end - start);

  start = micros();
  for (int i=0; i< 1000; i++)
  {
    DAC.setValue(1000);
  }
  end = micros();
  Serial.print("1000x DAC.setValue(1000):\t");
  Serial.println(end - start);


#ifdef MCP4725_EXTENDED

  //  start = micros();
  //  for (int i=0; i< 100; i++)
  //  {
  //    DAC.smooth2Value(i*10, 10);
  //  }
  //  end = micros();
  //  Serial.print("100x  DAC.smooth2Value(i*10, 10):\t");
  //  Serial.println(end - start);

  start = micros();
  for (int i=0; i< 1000; i++)
  {
    volatile int x = DAC.readDAC();
  }
  end = micros();
  Serial.print("1000x DAC.readDAC():\t\t");
  Serial.println(end - start);

  start = micros();
  for (int i=0; i< 1000; i++)
  {
    volatile int x = DAC.writeDAC(i);
  }
  end = micros();
  Serial.print("1000x DAC.writeDAC(i):\t\t");
  Serial.println(end - start);

  start = micros();
  for (int i=0; i< 10; i++)
  {
    volatile int x = DAC.writeDAC(i, true);
  }
  end = micros();
  Serial.print("10x   DAC.writeDAC(i, true):\t");
  Serial.println(end - start);

  start = micros();
  for (int i=0; i< 1000; i++)
  {
    volatile int x = DAC.RDY();
  }
  end = micros();
  Serial.print("1000x DAC.RDY():\t\t");
  Serial.println(end - start);

  while (!DAC.RDY());
  DAC.writeDAC(0, true);
  start = micros();
  while (!DAC.RDY());
  end = micros();
  Serial.print("EEPROM write latency:\t\t");
  Serial.println(end - start);

#endif

#ifdef MCP4725_POWERDOWNMODE

  // TODO TIMING TEST

#endif


  Serial.print("\nDone... (start triangle mode)");
}

void loop() 
{
  for (int i=0; i< 4096; i++)
  {
    DAC.setValue(i);
    delay(10);
  }
  for (int i=0; i< 4096; i++)
  {
    DAC.setValue(4096 - i);
    delay(10);
  }
}






