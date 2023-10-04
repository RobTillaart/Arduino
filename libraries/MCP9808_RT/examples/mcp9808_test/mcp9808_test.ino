//
//    FILE: mcp9808_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-05-03


#include "mcp9808.h"

MCP9808 ts(24);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP9808_LIB_VERSION: ");
  Serial.println(MCP9808_LIB_VERSION);

  Wire.begin();

  test_0();
  test_1();
  test_2();
  test_3();
}


void test_0()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  Serial.print("CONFIG:   ");
  Serial.println(ts.getConfigRegister(), HEX);
  Serial.print("TUPPER:   ");
  Serial.println(ts.getTupper());
  Serial.print("TLOWER:   ");
  Serial.println(ts.getTlower());
  Serial.print("TCRIT:    ");
  Serial.println(ts.getTcritical());
  Serial.print("TAMBIENT: ");
  Serial.println(ts.getTemperature());
  Serial.print("Resolut:  ");
  Serial.println(ts.getResolution());
  Serial.print("Manufact: ");
  Serial.println(ts.getManufacturerID());
  Serial.print("DeviceID: ");
  Serial.println(ts.getDeviceID());
  Serial.print("Revision: ");
  Serial.println(ts.getRevision());
  Serial.print("RFU:      ");
  Serial.println(ts.getRFU());
  Serial.println();
}


void test_1()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  for (int i = 0; i < 10; i++)
  {
    Serial.print(ts.getTemperature(), 4);
    Serial.print('\t');
    Serial.print(ts.getStatus(), HEX);
    Serial.print('\t');
    Serial.println();
  }
}


void test_2()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  for (int i = 0; i < 10; i++)
  {
    ts.setTlower(i * PI);
    Serial.print(ts.getTlower(), 4);
    Serial.print('\t');
    Serial.print(ts.getTemperature(), 4);
    Serial.print('\t');
    Serial.print(ts.getStatus(), HEX);
    Serial.print('\t');
    Serial.println();
  }
  ts.setTlower(0);
  Serial.println();

  for (int i = 0; i < 10; i++)
  {
    ts.setTupper(i * PI);
    Serial.print(ts.getTupper(), 4);
    Serial.print('\t');
    Serial.print(ts.getTemperature(), 4);
    Serial.print('\t');
    Serial.print(ts.getStatus(), HEX);
    Serial.print('\t');
    Serial.println();
  }
  ts.setTupper(0);
  Serial.println();

  for (int i = 0; i < 10; i++)
  {
    ts.setTcritical(i * 4);
    Serial.print(ts.getTcritical(), 4);
    Serial.print('\t');
    Serial.print(ts.getTemperature(), 4);
    Serial.print('\t');
    Serial.print(ts.getStatus(), HEX);
    Serial.print('\t');
    Serial.println();
  }
  ts.setTcritical(0);
  Serial.println();
}


void test_3()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  for (int i = 0; i < 4; i++)
  {
    ts.setResolution(i);
    Serial.print(i);
    Serial.print('\t');
    Serial.print(ts.getResolution());
    Serial.println();
  }
  ts.setResolution(3);
  Serial.println();
}


void loop()
{
}


// -- END OF FILE --
