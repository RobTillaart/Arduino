//
//    FILE: TCA9548_search_device.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TCA9548 I2C multiplexer
//     URL: https://github.com/RobTillaart/TCA9548
//
//    NOTE: since 0.3.0 a find function is added.


#include "TCA9548.h"

TCA9548 MP(0x70);

//  0x38 is a dummy (in fact a PCF8574), adjust to your needs.
uint8_t searchAddress = 0x38;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9548_LIB_VERSION: ");
  Serial.println(TCA9548_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (MP.begin() == false)
  {
    Serial.println("Could not connect to TCA9548 multiplexer.");
  }

  Serial.println("\nScan the channels of the multiplexer for searchAddress.\n");
  for (int chan = 0; chan < MP.channelCount(); chan++)
  {
    MP.selectChannel(chan);
    bool b = MP.isConnected(searchAddress);
    Serial.print("CHAN: ");
    Serial.print(chan);
    Serial.print("\t");
    Serial.print( b ? "found!" : "x");
  }
  Serial.println();

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

