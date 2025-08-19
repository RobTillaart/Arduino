//
//    FILE: MAX14661_MUX_debug.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: use of lastError for diagnostics.
//     URL: https://github.com/RobTillaart/MAX14661


#include "Wire.h"
#include "MAX14661.h"

MAX14661 mux(0x4C);


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
  test3();
}


void test1()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  for (int ch = 0; ch < 16; ch++)
  {
    mux.MUXA(ch);
    Serial.print(ch);
    Serial.print("\t");
    Serial.print(mux.lastError());
    Serial.print("\t");
    Serial.print(mux.getMUXA(), HEX);
    Serial.print("\t");
    Serial.println(mux.lastError());
  }
  mux.MUXA(255);
  Serial.print(255);
  Serial.print("\t");
  Serial.print(mux.lastError());
  Serial.print("\t");
  Serial.print(mux.getMUXB(), HEX);
  Serial.print("\t");
  Serial.println(mux.lastError());
}


void test2()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  for (int ch = 0; ch < 16; ch++)
  {
    mux.MUXB(ch);
    Serial.print(ch);
    Serial.print("\t");
    Serial.print(mux.lastError());
    Serial.print("\t");
    Serial.print(mux.getMUXB(), HEX);
    Serial.print("\t");
    Serial.println(mux.lastError());
  }
  mux.MUXB(255);
  Serial.print(255);
  Serial.print("\t");
  Serial.print(mux.lastError());
  Serial.print("\t");
  Serial.print(mux.getMUXB(), HEX);
  Serial.print("\t");
  Serial.println(mux.lastError());
}


void test3()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  for (int ch = 0; ch < 16; ch++)
  {
    mux.MUXB(ch);
    Serial.print(ch);
    Serial.print("\t");
    Serial.print(mux.lastError());
    Serial.print("\t");
    Serial.print(mux.getMUXB(), HEX);
    Serial.print("\t");
    Serial.println(mux.lastError());
  }
  mux.MUXB(255);
  Serial.print(255);
  Serial.print("\t");
  Serial.print(mux.lastError());
  Serial.print("\t");
  Serial.print(mux.getMUXB(), HEX);
  Serial.print("\t");
  Serial.println(mux.lastError());
}


void loop()
{
}


//  -- END OF FILE --
