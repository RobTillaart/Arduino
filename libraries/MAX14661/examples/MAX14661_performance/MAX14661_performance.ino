//
//    FILE: MAX14661_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance measurements
//     URL: https://github.com/RobTillaart/MAX14661


#include "Wire.h"
#include "MAX14661.h"

MAX14661 mux(0x4C);  //  0x4C..0x4F

uint32_t start, stop;

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

  //  delay to flush all IO.
  delay(100);

  for (uint32_t speed = 100000; speed <= 600000; speed += 100000)
  {
    Wire.setClock(speed);
    Serial.println(speed);
    delay(10);
    test_pair();
    test_mux();
    test_shadow();
    test_full_control();
  }

  Wire.setClock(100000);
  Serial.println("\ndone...");
}


void test_pair()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  mux.connectPair(3);
  stop = micros();
  Serial.print("connectPair:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.disconnectPair(3);
  stop = micros();
  Serial.print("disconnectPair:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.isConnectedPair(3);
  stop = micros();
  Serial.print("isCconnectedPair:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.disconnectAllPairs();
  stop = micros();
  Serial.print("disconnectAllPairs:\t");
  Serial.println(stop - start);
  delay(10);
}


void test_mux()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  mux.MUXA(3);
  stop = micros();
  Serial.print("MUXA:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.getMUXA();
  stop = micros();
  Serial.print("getMUXA:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.MUXB(5);
  stop = micros();
  Serial.print("MUXB:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.getMUXB();
  stop = micros();
  Serial.print("getMUXB:\t");
  Serial.println(stop - start);
  delay(10);
}


void test_shadow()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  mux.shadowClear();
  stop = micros();
  Serial.print("shadowClear:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.activateShadow();
  stop = micros();
  Serial.print("activateShadow:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.setShadowChannelMaskA(0xAAAA);
  stop = micros();
  Serial.print("setShadowChannelMaskA:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.getShadowChannelMaskA();
  stop = micros();
  Serial.print("getShadowChannelMaskA:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.isOpenShadowChannelA(5);
  stop = micros();
  Serial.print("isOpenShadowChannelA:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.openShadowChannelA(5);
  stop = micros();
  Serial.print("openShadowChannelA:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.closeShadowChannelA(5);
  stop = micros();
  Serial.print("closeShadowChannelA:\t");
  Serial.println(stop - start);
  delay(10);
}


void test_full_control()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  mux.connectA(3);
  stop = micros();
  Serial.print("connectA:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.connectB(5);
  stop = micros();
  Serial.print("connectB:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.disconnectA(5);
  stop = micros();
  Serial.print("disconnectA:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.disconnectB(3);
  stop = micros();
  Serial.print("disconnectB:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mux.disconnectAll();
  stop = micros();
  Serial.print("disconnectAll:\t");
  Serial.println(stop - start);
  delay(10);
}


void loop()
{
}


//  -- END OF FILE --
