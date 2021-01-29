//
//    FILE: MS5611_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo application
//    DATE: 2020-06-21
//     URL: https://github.com/RobTillaart/MS5611


#include "MS5611.h"


MS5611 MS5611(0x77);   // 0x76 = CSB to VCC; 0x77 = CSB to GND


uint32_t start, stop, count;


void setup()
{
  Serial.begin(115200);
  Serial.print(__FILE__);
  Serial.print("MS5611 lib version: ");
  Serial.println(MS5611_LIB_VERSION);

  bool b = MS5611.begin();
  Serial.println(b ? "found" : "not found");

  count = 0;
  Serial.println("CNT\tDUR\tRES\tTEMP\tPRES");
  delay(1000);
}

void loop()
{
  start = micros();
  int result = MS5611.read();
  stop = micros();

  Serial.print(count);
  count++;
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(result);
  Serial.print("\t");
  Serial.print(MS5611.getTemperature(), 2);
  Serial.print("\t");
  Serial.print(MS5611.getPressure(), 2);
  Serial.println();

  delay(1000);
}

// -- END OF FILE --

