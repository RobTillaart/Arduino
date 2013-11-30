//
//    FILE: mcp4725_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
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

  Serial.println("MCP4725 test program: ");
  Serial.println(MCP4725_VERSION);

  DAC.begin();

  Serial.print("Value:\t");
  Serial.println(DAC.getValue());
  Serial.println();

  Serial.println("setValue(100)");
  Serial.println(DAC.setValue(100));
  Serial.print("Value:\t");
  Serial.println(DAC.getValue());
  Serial.println();

  Serial.println("setValue(200)");
  Serial.println(DAC.setValue(200));
  Serial.print("Value:\t");
  Serial.println(DAC.getValue());
  Serial.println();

  Serial.println("smooth2Value(100, 10)");
  Serial.println(DAC.smooth2Value(100, 10));
  Serial.print("Value:\t");
  Serial.println(DAC.getValue());
  Serial.println();

#ifdef MCP4725_EXTENDED

  Serial.println("smooth2Value(200, 10)");
  Serial.println(DAC.smooth2Value(200, 10));
  Serial.print("Value:\t");
  Serial.println(DAC.getValue());
  Serial.println();

  Serial.println("writeDAC(100)");
  Serial.println(DAC.writeDAC(100));
  Serial.print("Value:\t");
  Serial.println(DAC.readDAC());
  Serial.println();

  Serial.println("writeDAC(200)");
  Serial.println(DAC.writeDAC(200));
  Serial.print("Value:\t");
  Serial.println(DAC.readDAC());
  Serial.println();

#endif



  //////////////////////////////////////////////////
  Serial.println("\n\nPERFORMANCE\n");

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
  for (int i=0; i< 100; i++)
  {
    DAC.smooth2Value(i*10, 10);
  }
  end = micros();
  Serial.print("100x  DAC.smooth2Value(i*10, 10):\t");
  Serial.println(end - start);

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

#endif
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




