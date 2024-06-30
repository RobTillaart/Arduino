//
//    FILE: ADS_performance.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read analog input
//     URL: https://github.com/RobTillaart/ADS1X15

//  TODO verify output

//  test
//  connect 1 potmeter
//
//  GND ---[   x   ]------ 5V
//             |
//
//  measure at x (connect to AIN0).
//
//  https://github.com/RobTillaart/ADS1X15/issues/53


#include "ADS1X15.h"


//  choose your sensor
//  ADS1013 ADS(0x48);
//  ADS1014 ADS(0x48);
//  ADS1015 ADS(0x48);
//  ADS1113 ADS(0x48);
//  ADS1114 ADS(0x48);

ADS1115 ADS(0x48);

uint32_t start, d1, d2;
int x;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();
  Wire.setClock(600000);

  ADS.begin();
  ADS.setGain(0);  //  6.144 volt

  for (int dr = 0; dr < 8; dr++)
  {
    //  0 = slow   4 = medium   7 = fast
    ADS.setDataRate(dr);
    Serial.print("DR:\t");
    Serial.println(dr);

    test_single_shot();
    test_continuous();

    Serial.print("\t\tFACTOR:\t");
    Serial.println(1.0 * d1 / d2);
  }

  Serial.println("\nDone...");
}


void loop()
{
}


void test_single_shot()
{
  Serial.print(__FUNCTION__);

  ADS.setMode(1);
  start = micros();
  x = ADS.readADC(0);
  for (int i = 0; i < 100; i++)
  {
    x = ADS.readADC(0);
  }
  d1 = micros() - start;
  Serial.print("\t");
  Serial.print(d1);                  //  TIME (us)
  Serial.print("\t\t");
  Serial.println(100000000.0 / d1);  //  SPS
  delay(100);
}


void test_continuous()
{
  Serial.print(__FUNCTION__);

  ADS.setMode(0);
  start = micros();
  x = ADS.readADC(0);
  for (int i = 0; i < 100; i++)
  {
    x = ADS.getValue();
  }
  d2 = micros() - start;
  Serial.print("\t\t");
  Serial.print(d2);                  //  TIME (us)
  Serial.print("\t\t");
  Serial.println(100000000.0 / d2);  //  SPS
  delay(100);
}


//  -- END OF FILE --
