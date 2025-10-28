//
//    FILE: RLCBuffer_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/RLCBuffer


#include "RLCBuffer.h"


RLCBuffer RLCB(20);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RLCBUFFER_LIB_VERSION: ");
  Serial.println(RLCBUFFER_LIB_VERSION);
  Serial.println();

  if (RLCB.begin() == false)
  {
    Serial.println("RLCB failed allocating mem");
    while (1);
  }

  Serial.print("SIZE:\t");  Serial.println(RLCB.size());
  Serial.print("COUNT:\t");  Serial.println(RLCB.count());
  Serial.println();

  //  fill the buffer with random numbers and generate different timestamps
  for (int i = 0; i < 20; i++)
  {
    uint32_t val = random(10);
    for (int i = 1 + random(500); i > 0; i--)
    {
      RLCB.writeData(val);
    }
  }

  Serial.print("SIZE:\t");  Serial.println(RLCB.size());
  Serial.print("COUNT:\t");  Serial.println(RLCB.count());
  Serial.println();

  for (int i = 0; i < 20; i++)
  {
    Serial.print(RLCB.readCount(i));
    Serial.print('\t');
    Serial.println(RLCB.readData(i));
  }
  Serial.println("\ndone...");

}


void loop()
{
}


//  -- END OF FILE --
