//
//    FILE: mcp4725_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test mcp4725 lib
//     URL: https://github.com/RobTillaart/MCP4725


#include "Wire.h"
#include "MCP4725.h"

MCP4725 MCP(0x62);

volatile int x;
uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP4725_VERSION: ");
  Serial.println(MCP4725_VERSION);

  Wire.begin();
  Wire.setClock(100000);

  MCP.begin();
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
}


void test1()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.print("Value:\t");
  Serial.println(MCP.getValue());
  Serial.println();

  for (int i = 100; i < 500; i += 100)
  {
    Serial.print("setValue(");
    Serial.print(i);
    Serial.print(")\n");
    MCP.setValue(i);
    Serial.print("Value:\t");
    Serial.println(MCP.getValue());
  }
  Serial.println();
}


void test2()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.println("MCP4725_II\n\n");

  for (int i = 100; i < 500; i += 100)
  {
    Serial.print("writeDAC(");
    Serial.print(i);
    Serial.print(")\n");
    MCP.writeDAC(i);
    Serial.print("MCPValue:\t");
    Serial.println(MCP.readDAC());
    Serial.print("EEValue:\t");
    Serial.println(MCP.readEEPROM());
  }
  Serial.println();

  for (int i = 100; i < 500; i += 100)
  {
    Serial.print("writeDAC(");
    Serial.print(i);
    Serial.print(", true)\n");
    MCP.writeDAC(i, true);
    Serial.print("MCPValue:\t");
    Serial.println(MCP.readDAC());
    Serial.print("EEValue:\t");
    Serial.println(MCP.readEEPROM());
  }
  Serial.println();

  Serial.println("writeDAC(200)");
  MCP.writeDAC(200);
  Serial.print("MCPValue:\t");
  Serial.println(MCP.readDAC());
  Serial.print("EEValue:\t");
  Serial.println(MCP.readEEPROM());
  Serial.println();
}


void test3()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.println("MCP4725_POWERDOWNMODE\n\n");

  for (int i = 0; i < 4; i++)
  {
    Serial.print("MCP.writePowerDownMode(");
    Serial.print(i);
    Serial.println(")");
    MCP.writePowerDownMode(i);
    Serial.print("EPR PDM Value:\t");
    Serial.println(MCP.readPowerDownModeEEPROM());
    Serial.println();
  }

  Serial.println("\n\nEXPERIMENTAL");
  Serial.println("MCP.writePowerDownMode(3)");
  MCP.writePowerDownMode(3);
  MCP.writeDAC(305);
  Serial.print("Value:\t");
  Serial.println(MCP.getValue());
  Serial.println("MCP.powerOnReset()");
  Serial.println("Before");
  Serial.print("MCP PDM Value:\t");
  Serial.println(MCP.readPowerDownModeDAC());
  Serial.print("EPR PDM Value:\t");
  Serial.println(MCP.readPowerDownModeEEPROM());
  Serial.print("MCPValue:\t");
  Serial.println(MCP.readDAC());
  Serial.print("EEValue:\t");
  Serial.println(MCP.readEEPROM());
  MCP.powerOnReset();
  Serial.println("After");
  Serial.print("MCP PDM Value:\t");
  Serial.println(MCP.readPowerDownModeDAC());
  Serial.print("EPR PDM Value:\t");
  Serial.println(MCP.readPowerDownModeEEPROM());
  Serial.print("MCPValue:\t");
  Serial.println(MCP.readDAC());
  Serial.print("EEValue:\t");
  Serial.println(MCP.readEEPROM());
  Serial.print("Value:\t");
  Serial.println(MCP.getValue());
  Serial.println();
}


void test4()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.println("EXPERIMENTAL");
  Serial.println("MCP.writePowerDownMode(2)");
  MCP.writePowerDownMode(2);
  MCP.writeDAC(405);
  Serial.print("Value:\t");
  Serial.println(MCP.getValue());
  Serial.println("MCP.powerOnWakeUp()");
  Serial.println("Before");
  Serial.print("MCP PDM Value:\t");
  Serial.println(MCP.readPowerDownModeDAC());
  Serial.print("EPR PDM Value:\t");
  Serial.println(MCP.readPowerDownModeEEPROM());
  Serial.print("MCPValue:\t");
  Serial.println(MCP.readDAC());
  Serial.print("EEValue:\t");
  Serial.println(MCP.readEEPROM());

  MCP.powerOnWakeUp();
  Serial.println("after");
  Serial.print("MCP PDM Value:\t");
  Serial.println(MCP.readPowerDownModeDAC());
  Serial.print("EPR PDM Value:\t");
  Serial.println(MCP.readPowerDownModeEEPROM());
  Serial.print("MCPValue:\t");
  Serial.println(MCP.readDAC());
  Serial.print("EEValue:\t");
  Serial.println(MCP.readEEPROM());
  Serial.print("Value:\t");
  Serial.println(MCP.getValue());
  Serial.println();
}


void test5()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.println("PERFORMANCE");
  Serial.println();

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = MCP.getValue();
  }
  stop = micros();
  Serial.print("1000x MCP.getValue():\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    MCP.setValue(i);
  }
  stop = micros();
  Serial.print("1000x MCP.setValue(i):\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    MCP.setValue(1000);
  }
  stop = micros();
  Serial.print("1000x MCP.setValue(1000):\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = MCP.readDAC();
  }
  stop = micros();
  Serial.print("1000x MCP.readDAC():\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = MCP.writeDAC(i);
  }
  stop = micros();
  Serial.print("1000x MCP.writeDAC(i):\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 10; i++)
  {
    x = MCP.writeDAC(i, true);
  }
  stop = micros();
  Serial.print("10x   MCP.writeDAC(i, true):\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = MCP.ready();
  }
  stop = micros();
  Serial.print("1000x MCP.ready():\t\t");
  Serial.println(stop - start);

  while (!MCP.ready());
  MCP.writeDAC(0, true);
  start = micros();
  while (!MCP.ready());
  stop = micros();
  Serial.print("EEPROM write latency:\t\t");
  Serial.println(stop - start);
}


void test6()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.println("EXPERIMENTAL II");

  start = micros();
  for (int i = 0; i < 10; i++)
  {
    x = MCP.readPowerDownModeDAC();
  }
  stop = micros();
  Serial.print("10x MCP.readPowerDownModeDAC():\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 10; i++)
  {
    x = MCP.readPowerDownModeEEPROM();
  }
  stop = micros();
  Serial.print("10x MCP.readPowerDownModeEEPROM():\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 10; i++)
  {
    x = MCP.writePowerDownMode(i & 0x03);
  }
  stop = micros();
  Serial.print("10x MCP.writePowerDownMode(i):\t\t");
  Serial.println(stop - start);

  Serial.print("\nDone... (start triangle mode)");
}


void loop()
{
  for (uint16_t i = 0; i < 4096; i++)
  {
    MCP.setValue(i);
    delay(10);
  }
  for (uint16_t i = 0; i < 4096; i++)
  {
    MCP.setValue(4096 - i);
    delay(10);
  }
}


//  -- END OF FILE --
