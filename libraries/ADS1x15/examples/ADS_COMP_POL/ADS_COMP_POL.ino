//
//    FILE: ADS_COMP_POL.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read analog input
//     URL: https://github.com/RobTillaart/ADS1X15/issues/76

#include "ADS1X15.h"

// choose your sensor
// ADS1013 ADS(0x48);
// ADS1014 ADS(0x48);
// ADS1015 ADS(0x48);
// ADS1113 ADS(0x48);
// ADS1114 ADS(0x48);

ADS1115 ADS(0x48);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();

  ADS.begin();
  ADS.setGain(0);      //  6.144 volt
  ADS.setDataRate(4);  //  0..7

  //  test polarity
  //  data rate 4 (default)
  //  MODE                COMP_POL    ALERT/RDY PIN
  //  0 = continuous      0 = LOW     LOW with 8 us HIGH PULSE
  //  0 = continuous      1 = HIGH    HIGH with 8 us LOW pulse
  //  1 = single          0 = LOW     HIGH with 8 ms LOW pulse
  //  1 = single          1 = HIGH    LOW with 8 ms HIGH pulse
  ADS.setMode(1);
  ADS.setComparatorPolarity(1);
  //  enable ALERT/RDY pin
  ADS.setComparatorThresholdHigh(0x8000);
  ADS.setComparatorThresholdLow(0x0000);
  ADS.setComparatorQueConvert(0);
  //  activate settings
  ADS.requestADC(0);

  Serial.println("Voltage");
  delay(1000);
}

void loop()
{
  //  comment all in loop() to get a single pulse
  int16_t raw = ADS.readADC(0);
  delay(1000);

  Serial.println(ADS.toVoltage(raw), 3);
  delay(1000);
}

//  -- END OF FILE --
