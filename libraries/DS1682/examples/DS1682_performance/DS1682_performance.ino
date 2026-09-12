//
//    FILE: DS1682_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/DS1682


#include "DS1682.h"


DS1682 upTimer;  //  0x6A default address
uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS1682_LIB_VERSION: ");
  Serial.println(DS1682_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  bool b = upTimer.begin();

  Serial.print("BEGIN:\t");
  Serial.println(b);
  Serial.print("ADDR:\t");
  Serial.println(upTimer.getAddress());
  delay(100);

  for (uint32_t cl = 100000; cl < 500000; cl += 100000)
  {
    Wire.setClock(cl);
    Serial.println();
    Serial.println(cl);
    delay(100);

    start = micros();
    uint32_t etc = upTimer.getElapsedSeconds();
    stop = micros();
    Serial.print("ETC:\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.println(etc);

    delay(100);

    start = micros();
    uint32_t ec = upTimer.getEventCounter();
    stop = micros();
    Serial.print("EC:\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.println(ec);
    delay(100);


  }

  Serial.println("done...");
}


void loop()
{

}


//  -- END OF FILE --
