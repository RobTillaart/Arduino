//
//    FILE: dht11_two.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DHT library test sketch for DHT11 && Arduino
//     URL: https://github.com/RobTillaart/DHTstable



#include "DHTStable.h"


DHTStable DHT_A;
DHTStable DHT_B;

#define DHT11_PIN_A       5
#define DHT11_PIN_B       6


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTSTABLE_LIB_VERSION);
  Serial.println();
}


void loop()
{
  Serial.print("DHT A:\t");
  DHT_A.read11(DHT11_PIN_A);
  Serial.print(DHT_A.getHumidity());
  Serial.print(",\t");
  Serial.println(DHT_A.getTemperature());


  Serial.print("DHT B:\t");
  DHT_B.read11(DHT11_PIN_B);
  Serial.print(DHT_B.getHumidity());
  Serial.print(",\t");
  Serial.println(DHT_B.getTemperature());

  delay(2000);
}


// -- END OF FILE --
