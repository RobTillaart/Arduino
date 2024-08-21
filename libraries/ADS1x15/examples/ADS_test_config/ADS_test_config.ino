//
//    FILE: ADS_test_config.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: test config flags
//     URL: https://github.com/RobTillaart/ADS1X15
//          triggered by issue 80


#include "ADS1X15.h"

ADS1115 ADS(0x48);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();

  ADS.begin();

  Serial.println("\nTEST GAIN");
  int gain = 16;
  for (int i = 0; i < 6; i++)
  {
    Serial.print(gain);
    ADS.setGain(gain);
    if (ADS.getGain() == gain) Serial.println("\tOK");
    else Serial.println("\tFAIL");
  }

  Serial.println("\nTEST DATARATE");
  for (int i = 0; i < 7; i++)
  {
    Serial.print(i);
    ADS.setDataRate(i);
    if (ADS.getDataRate() == i) Serial.println("\tOK");
    else Serial.println("\tFAIL");
  }

  Serial.println("\nTEST MODE");
  for (int i = 0; i < 2; i++)
  {
    Serial.print(i);
    ADS.setMode(i);
    if (ADS.getMode() == i) Serial.println("\tOK");
    else Serial.println("\tFAIL");
  }

  Serial.println("\nTEST COMP MODE");
  for (int i = 0; i < 2; i++)
  {
    Serial.print(i);
    ADS.setComparatorMode(i);
    if (ADS.getComparatorMode() == i) Serial.println("\tOK");
    else Serial.println("\tFAIL");
  }

  Serial.println("\nTEST COMP POLARITY");
  for (int i = 0; i < 2; i++)
  {
    Serial.print(i);
    ADS.setComparatorPolarity(i);
    if (ADS.getComparatorPolarity() == i) Serial.println("\tOK");
    else Serial.println("\tFAIL");
  }

  Serial.println("\nTEST COMP LATCH");
  for (int i = 0; i < 2; i++)
  {
    Serial.print(i);
    ADS.setComparatorLatch(i);
    if (ADS.getComparatorLatch() == i) Serial.println("\tOK");
    else Serial.println("\tFAIL");
  }

  Serial.println("\nTEST COMP QUECONVERT");
  for (int i = 0; i < 2; i++)
  {
    Serial.print(i);
    ADS.setComparatorQueConvert(i);
    if (ADS.getComparatorQueConvert() == i) Serial.println("\tOK");
    else Serial.println("\tFAIL");
  }

  Serial.println("\ndone...");
}

void loop()
{
}

//  -- END OF FILE --
