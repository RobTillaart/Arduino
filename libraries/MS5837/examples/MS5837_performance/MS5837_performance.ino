//    FILE: MS5837_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MS5837 library
//     URL: https://github.com/RobTillaart/MS5837

/*  AVR I2C codes
  |     0  |  success
  |     1  |  length to long for buffer
  |     2  |  address send, NACK received
  |     3  |  data send, NACK received
  |     4  |  other twi error
  |     5  |  timeout
*/


#include "Arduino.h"
#include "Wire.h"

#include "MS5837.h"

MS5837 MS(&Wire);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MS5837_LIB_VERSION: ");
  Serial.println(MS5837_LIB_VERSION);
  Serial.println();

  Wire.begin();

  //  MS5837_30 = 0
  //  MS5837_02 = 1
  if (MS.begin(1) == true)
  {
    Serial.println("MS5837 found.");
  }
  else
  {
    Serial.println("MS5837 not found. halt.");
    // while (1);
  }
  Serial.println();

  test(8);
  test(9);
  test(10);
  test(11);
  test(12);
  test(13);
}


void loop()
{
}


void test(uint8_t bits)
{
  start = micros();
  int ret = MS.read(bits);
  stop = micros();
  if (ret != 0)
  {
    Serial.print("Read Error!!\t");
  }
  Serial.print("B: ");
  Serial.print(bits);
  Serial.print("\tT: ");
  Serial.print(MS.getTemperature(), 2);
  Serial.print("\tP: ");
  Serial.print(MS.getPressure(), 2);
  Serial.print("\tA: ");
  Serial.print(MS.getAltitude(1023.45), 2);
  Serial.print("\tD: ");
  Serial.print(MS.getDepth(1023.45), 2);
  Serial.print("\tE: ");
  Serial.print(MS.getLastError());
  Serial.print("\tM: ");
  Serial.print(stop - start);
  Serial.println();
  delay(100);
}


//  -- END OF FILE --
