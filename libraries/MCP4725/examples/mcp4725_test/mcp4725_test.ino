//
//    FILE: mcp4725_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
// PURPOSE: test mcp4725 lib
//    DATE: 2013-11-24
//     URL: https://github.com/RobTillaart/MCP4725
//

#include "Wire.h"
#include "MCP4725.h"

MCP4725 DAC(0x62);  // 0x62 or 0x63

volatile int x;
uint32_t start, stop;

void setup()
{
  Serial.begin(115200);

  Serial.print("MCP4725 test program: ");
  Serial.println(MCP4725_VERSION);

  DAC.begin();
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
}

void test1()
{
  Serial.print("\nValue:\t");
  Serial.println(DAC.getValue());
  Serial.println();

  for (int i = 100; i < 500; i += 100)
  {
    Serial.print("setValue(");
    Serial.print(i);
    Serial.print(")\n");
    DAC.setValue(i);
    Serial.print("Value:\t");
    Serial.println(DAC.getValue());
  }
  Serial.println();
}

void test2()
{
  Serial.println("\n\nMCP4725_II\n\n");

  for (int i = 100; i < 500; i += 100)
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

  for (int i = 100; i < 500; i += 100)
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
}

void test3()
{
  Serial.println("\n\nMCP4725_POWERDOWNMODE\n\n");

  for (int i = 0; i < 4; i++)
  {
    Serial.print("DAC.writePowerDownMode(");
    Serial.print(i);
    Serial.println(")");
    DAC.writePowerDownMode(i);
    Serial.print("EPR PDM Value:\t");
    Serial.println(DAC.readPowerDownModeEEPROM());
    Serial.println();
  }

  Serial.println("\n\nEXPERIMENTAL");
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
}

void test4()
{
  Serial.println("\n\nEXPERIMENTAL");
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
}

void test5()
{
  Serial.println("\n\nPERFORMANCE");
  Serial.println();

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = DAC.getValue();
  }
  stop = micros();
  Serial.print("1000x DAC.getValue():\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    DAC.setValue(i);
  }
  stop = micros();
  Serial.print("1000x DAC.setValue(i):\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    DAC.setValue(1000);
  }
  stop = micros();
  Serial.print("1000x DAC.setValue(1000):\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = DAC.readDAC();
  }
  stop = micros();
  Serial.print("1000x DAC.readDAC():\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = DAC.writeDAC(i);
  }
  stop = micros();
  Serial.print("1000x DAC.writeDAC(i):\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 10; i++)
  {
    x = DAC.writeDAC(i, true);
  }
  stop = micros();
  Serial.print("10x   DAC.writeDAC(i, true):\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = DAC.ready();
  }
  stop = micros();
  Serial.print("1000x DAC.ready():\t\t");
  Serial.println(stop - start);

  while (!DAC.ready());
  DAC.writeDAC(0, true);
  start = micros();
  while (!DAC.ready());
  stop = micros();
  Serial.print("EEPROM write latency:\t\t");
  Serial.println(stop - start);
}

void test6()
{
  Serial.println("\n\nEXPERIMENTAL II");

  start = micros();
  for (int i = 0; i < 10; i++)
  {
    x = DAC.readPowerDownModeDAC();
  }
  stop = micros();
  Serial.print("10x DAC.readPowerDownModeDAC():\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 10; i++)
  {
    x = DAC.readPowerDownModeEEPROM();
  }
  stop = micros();
  Serial.print("10x DAC.readPowerDownModeEEPROM():\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 10; i++)
  {
    x = DAC.writePowerDownMode(i & 0x03);
  }
  stop = micros();
  Serial.print("10x DAC.writePowerDownMode(i):\t\t");
  Serial.println(stop - start);

  Serial.print("\nDone... (start triangle mode)");
}

void loop()
{
  for (uint16_t i = 0; i < 4096; i++)
  {
    DAC.setValue(i);
    delay(10);
  }
  for (uint16_t i = 0; i < 4096; i++)
  {
    DAC.setValue(4096 - i);
    delay(10);
  }
}

// -- END OF FILE --
