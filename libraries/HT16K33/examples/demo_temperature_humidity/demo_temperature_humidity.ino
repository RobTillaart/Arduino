//
//    FILE: demo_temperature_humidity.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//     URL: http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33

// This example uses th DHTNew library and a DHT22 sensor
//  https://github.com/RobTillaart/DHTNew


#include "HT16K33.h"
#include "dhtnew.h"


HT16K33 seg(0x70);
DHTNEW dht(10);
uint32_t lastTime = 0;
bool flag = true;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.setClock(100000);
  seg.begin();
  seg.displayOn();
}

void loop()
{

  uint32_t now = millis();
  if (now - lastTime > 4000)
  {
    lastTime = now;
    dht.read();

    if (flag)
    {
      seg.displayFixedPoint1(dht.getTemperature());
    }
    else
    {
      seg.displayFixedPoint1(dht.getHumidity());
    }
    flag = !flag;
  }
}

// -- END OF FILE --
