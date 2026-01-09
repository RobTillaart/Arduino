//
//    FILE: TLCBuffer_float.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour Time Length Compression
//     URL: https://github.com/RobTillaart/TLCBuffer
//
//  assumes voltage measurement, 5V ADC

#include "TLCBuffer.h"


TLCBuffer<float> measurements(50);  //  float as data element


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TLCBUFFER_LIB_VERSION: ");
  Serial.println(TLCBUFFER_LIB_VERSION);
  Serial.println();

  if (measurements.begin('m') == false)
  {
    Serial.println("TLCB failed allocating mem");
    while (1);
  }

  //  fill the buffer with "measurements" and generate different timestamps
  for (int i = 0; i < 20; i++)
  {
    //  5V - 10 bit.
    float voltage = analogRead(A0) * (5.0 / 1023);
    //  this voltage stays stable for some time.
    for (int i = 1 + random(100); i > 0; i--)
    {
      measurements.writeData(voltage);
      delay(1);
    }
  }

  Serial.print("SIZE:\t");  Serial.println(measurements.size());
  Serial.print("COUNT:\t");  Serial.println(measurements.count());
  Serial.println();

  for (int i = 0; i < measurements.count(); i++)
  {
    Serial.print(measurements.readDuration(i));
    Serial.print('\t');
    Serial.println(measurements.readData(i), 4);
  }
  Serial.println("\ndone...");

}


void loop()
{
}


//  -- END OF FILE --
