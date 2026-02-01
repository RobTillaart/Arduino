//    FILE: SHT2x_AH_issue42.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test for issue 42 - effect of Wifi on RH and T
//     URL: https://github.com/RobTillaart/SHT2x/issues/42
//     URL: https://github.com/RobTillaart/Temperature
//
//


#include "Arduino.h"


//  from Temperature Library
float absoluteHumidity(float Celsius, float relHumidity)
{
  float TC = Celsius;
  float AH = (2.1674 * 6.112) * relHumidity;
  AH *= exp((17.67 * TC) / (243.5 + TC));
  AH /=  (273.15 + TC);
  return AH;
}


void test(float Celsius, float relHumidity)
{
  Serial.print(Celsius);
  Serial.print("\t");
  Serial.print(relHumidity);
  Serial.print("\t");
  Serial.println(absoluteHumidity(Celsius, relHumidity));
}


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);

  //  Test 1-2
  Serial.println("03 cm, Temp = 23.6, Hum = 34.4");
  Serial.println(absoluteHumidity(23.6, 34.4));
  Serial.println("15 cm, Temp = 23.4, Hum = 32.2");
  Serial.println(absoluteHumidity(23.4, 32.2));
  Serial.println();

  //  Test 3-4
  Serial.println("03 cm, Temp = 25.6, Hum = 24.0");
  Serial.println(absoluteHumidity(25.6, 24.0));
  Serial.println("15 cm, Temp = 22.6, Hum = 28.3");
  Serial.println(absoluteHumidity(22.6, 28.3));
  Serial.println();

  Serial.println("\n\nStart");
  test(23.3, 30.3);
  test(23.3, 30.3);
  test(23.3, 30.2);
  test(23.3, 30.0);
  test(23.3, 29.8);
  Serial.println("10 min");
  test(26.4, 21.9);
  Serial.println("20 min");
  test(28.4, 18.6);
  Serial.println("30 min");
  test(29.1, 17.4);
}

void loop()
{
}


//  -- END OF FILE --
