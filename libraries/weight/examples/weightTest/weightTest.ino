//
//    FILE: weightTest.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-06-17


#include "weight.h"

const float accuracy = 0.0001;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
}


void loop()
{
  float stone, lbs, ounce, kilo, val, kg;

  stone = random(20) * 0.12345;
  lbs = random(20) * 3.46281;
  ounce = random(20) * 6.3723;
  kilo = random(100) * 1.3579;

  Serial.print(millis());

  val = kilo2lbs(lbs2kilo(lbs));
  if (abs(val - lbs) > accuracy)
  {
    Serial.print("\tPOUND: ");
    Serial.print(lbs);
  }

  val = gram2ounce(ounce2gram(ounce));
  if (abs(val - ounce) > accuracy)
  {
    Serial.print("\tOUNCE: ");
    Serial.print(ounce);
  }

  val = kilo2stone(stone2kilo(stone));
  if (abs(val - stone) > accuracy)
  {
    Serial.print("\tSTONE: ");
    Serial.print(stone);
  }

  metric2US(kilo, stone, lbs, ounce);
  kg = US2metric(stone, lbs, ounce);
  if (abs(kilo - kg) > accuracy)
  {
    Serial.print("\tUS2ME: ");
    Serial.print(kilo);
  }
  Serial.println("\t.");
}


//  -- END OF FILE --

