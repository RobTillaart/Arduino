//    FILE: MS5837_plotter_median_avg.ino
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
#include "RunningMedian.h"

MS5837 MS(&Wire);

RunningMedian samples = RunningMedian(17);

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MS5837_LIB_VERSION: ");
  Serial.println(MS5837_LIB_VERSION);
  Serial.print(F("RUNNING_MEDIAN_VERSION: "));
  Serial.println(RUNNING_MEDIAN_VERSION);
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
  Serial.println("Low\tMedian\tAvg\tHigh");

  while(MS.read(8) != 0);
}


void loop()
{
  if (MS.read(8) != 0)
  {
    Serial.print("Read Error!!\t");
    return;
  }
  float val = MS.getAltitude(1024);
  samples.add(val);
  
  Serial.print(samples.getLowest(), 2);
  Serial.print("\t");
  Serial.print(samples.getMedian(), 2);
  Serial.print("\t");
  Serial.print(samples.getAverage(), 2);
  Serial.print("\t");
  Serial.print(samples.getHighest(), 2);
  Serial.println();
  delay(20);
}


//  -- END OF FILE --
