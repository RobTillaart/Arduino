//
//    FILE: MAX14661_PAIR.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PAIR interface
//     URL: https://github.com/RobTillaart/MAX14661


#include "Wire.h"
#include "MAX14661.h"

MAX14661 mux(0x4C);  //  0x4C..0x4F


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MAX14661_LIB_VERSION: ");
  Serial.println(MAX14661_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (mux.begin() == false)
  {
    Serial.print(mux.lastError());
    Serial.println("\t Could not find MAX14661");
    while (1);
  }

  test1();
  test2();

  Serial.println("\ndone...");
}


void test1()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  for (int pair = 0; pair < 8; pair++)
  {
    mux.disconnectPair(pair);
    Serial.print(pair);
    Serial.print("\t");
    Serial.print(mux.isConnectedPair(pair));
    Serial.print("\t");
    mux.connectPair(pair);
    Serial.print(mux.isConnectedPair(pair));
    Serial.println();
  }
  mux.disconnectAllPairs();
  for (int pair = 0; pair < 8; pair++)
  {
    Serial.print("\t");
    Serial.print(mux.isConnectedPair(pair));
  }
  Serial.println();
}


void test2()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  mux.disconnectAllPairs();
  for (int i = 0; i < 10; i++)
  {
    uint8_t pair = random(8);
    mux.connectPair(pair);
    for (int pair = 0; pair < 8; pair++)
    {
      Serial.print("\t");
      Serial.print(mux.isConnectedPair(pair));
    }
    Serial.println();
  }
  mux.disconnectAllPairs();
  for (int pair = 0; pair < 8; pair++)
  {
    Serial.print("\t");
    Serial.print(mux.isConnectedPair(pair));
  }
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --
