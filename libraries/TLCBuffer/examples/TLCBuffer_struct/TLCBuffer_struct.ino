//
//    FILE: TLCBuffer_struct.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour Time Length Compression
//     URL: https://github.com/RobTillaart/TLCBuffer
//
//  needs memcmp in lib for lastData
//  needs memset in lib for lastData


#include "TLCBuffer.h"

struct WEATHER
{
  uint16_t temp;
  uint8_t hum;
} w;

TLCBuffer<WEATHER, uint32_t> measurements(13);


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
    w.temp = 20 + random(5);
    w.hum = 50 + random(5);
    for (int i = 1 + random(100); i > 0; i--)
    {
      measurements.writeData(w);
      delay(1);
    }
  }

  Serial.print("SIZE:\t");  Serial.println(measurements.size());
  Serial.print("COUNT:\t");  Serial.println(measurements.count());
  Serial.print("INDEX:\t");  Serial.println(measurements.index());
  Serial.println();

  for (uint16_t i = 0; i < measurements.count(); i++)
  {
    Serial.print(measurements.readDuration(i));
    Serial.print('\t');
    w = measurements.readData(i);
    Serial.print(w.temp);
    Serial.print('\t');
    Serial.print(w.hum);
    Serial.print('\t');
    if (i == measurements.index())
    {
      Serial.print("(last)");  //  indicate last added value.
    }
    Serial.println();
  }
  Serial.println("\ndone...");

}


void loop()
{
}


//  -- END OF FILE --
