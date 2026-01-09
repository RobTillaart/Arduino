//
//    FILE: TLCBuffer_int.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour Time Length Compression
//     URL: https://github.com/RobTillaart/TLCBuffer


#include "TLCBuffer.h"

//  T_DATA (= signed), T_TIME (= unsigned)
TLCBuffer<int16_t, uint16_t> TLCB(20);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TLCBUFFER_LIB_VERSION: ");
  Serial.println(TLCBUFFER_LIB_VERSION);
  Serial.println();

  if (TLCB.begin('m') == false)
  {
    Serial.println("TLCB failed allocating mem");
    while (1);
  }

  Serial.print("SIZE:\t");  Serial.println(TLCB.size());
  Serial.print("COUNT:\t");  Serial.println(TLCB.count());
  Serial.println();

  //  fill the buffer with random numbers and generate different timestamps
  for (int i = 0; i < 20; i++)
  {
    int val = -50 + random(100);
    for (int i = 1 + random(99); i > 0; i--)
    {
      TLCB.writeData(val);
      delay(1);
    }
  }

  Serial.print("SIZE:\t");  Serial.println(TLCB.size());
  Serial.print("COUNT:\t");  Serial.println(TLCB.count());
  Serial.println();

  for (int i = 0; i < TLCB.count(); i++)
  {
    Serial.print(i);
    Serial.print('\t');
    Serial.print(TLCB.readDuration(i));
    Serial.print('\t');
    Serial.println(TLCB.readData(i));
  }
  Serial.println("\ndone...");

}


void loop()
{
}


//  -- END OF FILE --
