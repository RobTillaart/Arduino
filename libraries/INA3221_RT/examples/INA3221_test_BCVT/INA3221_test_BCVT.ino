//
//    FILE: INA3221_test_BCVT.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test bus conversion time single channel
//     URL: https://github.com/RobTillaart/INA3221_RT


#include "INA3221.h"


INA3221 INA(0x40);
uint32_t start, stop;


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA3221_LIB_VERSION: ");
  Serial.println(INA3221_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
    while (1);
  }
  else
  {
    Serial.print("Found: \t");
    Serial.println(INA.getAddress());
  }

  Serial.print("CFG:\t");
  Serial.println(INA.getConfiguration(), HEX);  //  should be 0x7127

  //  overwrite default shunts.
  INA.setShuntR(0, 0.100);
  INA.enableChannel(0);
  delay(100);  // fllussssh IO


  //  should give roughly same timing
  //  see section 8.4.1 datasheet.
  for (int bcvt = 0; bcvt < 8; bcvt++)
  {
    Serial.println(INA.setBusVoltageConversionTime(bcvt));
    Serial.print("BVCT:\t");
    Serial.println(INA.getBusVoltageConversionTime());
    delay(100);

    start = micros();
    float busVoltage = INA.getBusVoltage(0);
    stop = micros();
    Serial.print("BUS V:\t");
    Serial.print(busVoltage, 3);
    Serial.print("\t");
    Serial.println(stop - start);
    delay(100);
  }
}


void loop()
{
}


//  -- END OF FILE --
