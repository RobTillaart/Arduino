//
//    FILE: mcp4725_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.04
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

  for (int i=0; i<4; i++)
  {
    Serial.print("DAC.writePowerDownMode(");
    Serial.print(i);
    Serial.println(")");
    DAC.writePowerDownMode(i);
    Serial.print("EPR PDM Value:\t");
    Serial.println(DAC.readPowerDownModeEEPROM());
    Serial.println();
  }

  Serial.println("EXPERIMENTAL");
  Serial.println("DAC.writePowerDownMode(3)");
  DAC.writePowerDownMode(3);
  DAC.writeDAC(305);
  Serial.print("Value:\t");
  Serial.println(DAC.getValue());
  Serial.println("DAC.powerOnReset()");
  Serial.println("Before");
  Serial.print("DAC PDM Value:\t");
  Serial.println(DAC.readPowerDownModeDAC());
  Serial.print("EPR PDM Value:\t");
  Serial.println(DAC.readPowerDownModeEEPROM());
  Serial.print("DACValue:\t");
  Serial.println(DAC.readDAC());
  Serial.print("EEValue:\t");
  Serial.println(DAC.readEEPROM());  
  DAC.powerOnReset();
  Serial.println("After");
  Serial.print("DAC PDM Value:\t");
  Serial.println(DAC.readPowerDownModeDAC());
  Serial.print("EPR PDM Value:\t");
  Serial.println(DAC.readPowerDownModeEEPROM());
  Serial.print("DACValue:\t");
  Serial.println(DAC.readDAC());
  Serial.print("EEValue:\t");
  Serial.println(DAC.readEEPROM());  
  Serial.print("Value:\t");
  Serial.println(DAC.getValue());
  Serial.println();


  Serial.println("EXPERIMENTAL");
  Serial.println("DAC.writePowerDownMode(2)");
  DAC.writePowerDownMode(2);
  DAC.writeDAC(405);
  Serial.print("Value:\t");
  Serial.println(DAC.getValue());
  Serial.println("DAC.powerOnWakeUp()");
  Serial.println("Before");
  Serial.print("DAC PDM Value:\t");
  Serial.println(DAC.readPowerDownModeDAC());
  Serial.print("EPR PDM Value:\t");
  Serial.println(DAC.readPowerDownModeEEPROM());
  Serial.print("DACValue:\t");
  Serial.println(DAC.readDAC());
  Serial.print("EEValue:\t");
  Serial.println(DAC.readEEPROM());  
  DAC.powerOnWakeUp();
  Serial.println("after");
  Serial.print("DAC PDM Value:\t");
  Serial.println(DAC.readPowerDownModeDAC());
  Serial.print("EPR PDM Value:\t");
  Serial.println(DAC.readPowerDownModeEEPROM());
  Serial.print("DACValue:\t");
  Serial.println(DAC.readDAC());
  Serial.print("EEValue:\t");
  Serial.println(DAC.readEEPROM());  
  Serial.print("Value:\t");
  Serial.println(DAC.getValue());
  Serial.println();

#endif

  //////////////////////////////////////////////////
  Serial.println("\n\nPERFORMANCE");
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

  Serial.println("\nEXPERIMENTAL");

  start = micros();
  for (int i=0; i< 10; i++)
  {
    volatile int x = DAC.readPowerDownModeDAC();
  }
  end = micros();
  Serial.print("10x DAC.readPowerDownModeDAC():\t\t");
  Serial.println(end - start);

  start = micros();
  for (int i=0; i< 10; i++)
  {
    volatile int x = DAC.readPowerDownModeEEPROM();
  }
  end = micros();
  Serial.print("10x DAC.readPowerDownModeEEPROM():\t");
  Serial.println(end - start);

  start = micros();
  for (int i=0; i< 10; i++)
  {
    volatile int x = DAC.writePowerDownMode(i & 0x03);
  }
  end = micros();
  Serial.print("10x DAC.writePowerDownMode(i):\t\t");
  Serial.println(end - start);

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




