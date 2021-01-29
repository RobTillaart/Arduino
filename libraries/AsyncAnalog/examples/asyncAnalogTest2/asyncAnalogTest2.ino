//
//    FILE: asyncAnalogTest2.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2020-03-27

#include "AsyncAnalog.h"

AsyncAnalog AA(A0);

uint32_t start = 0;
uint32_t duration = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println("start: ");
  Serial.println(analogRead(0));
}


void loop()
{
  normal_test();
  delay(1000);

  async_test();
  delay(1000);
}


void normal_test()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    int x = analogRead(A0);
    Serial.println(x);
  }
  duration = micros() - start;
  Serial.print(duration);
  Serial.print("\n\n");
}


void async_test()
{
  int  x = 0;

  Serial.println();
  Serial.println(__FUNCTION__);

  start = micros();
  AA.start();
  for (int i = 0; i < 1000; i++)
  {
    if (AA.ready())
    {
      x = AA.value();     // read the value
      AA.start();         // request next conversion
      Serial.println(x);  // print value while conversion runs in the background
    }
  }
  duration = micros() - start;
  Serial.print(duration);
  Serial.print("\n\n");
}

// END OF FILE