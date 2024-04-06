//
//    FILE: asyncAnalogTest2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo async is faster on AVR


#include "AsyncAnalog.h"


AsyncAnalog AA(A0);

volatile int x;

uint32_t start = 0;
uint32_t duration = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ASYNCANALOG_LIB_VERSION: ");
  Serial.println(ASYNCANALOG_LIB_VERSION);

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
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = analogRead(A0);
    Serial.print(x);
  }
  duration = micros() - start;
  Serial.println();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print(duration);
  Serial.println();
  delay(100);
}


void async_test()
{
  start = micros();
  AA.start();
  for (int i = 0; i < 1000; i++)
  {
    if (AA.ready())
    {
      x = AA.value();     //  read the value
      AA.start();         //  request next conversion
      Serial.print(x);    //  print value while conversion runs in the background
    }
  }
  duration = micros() - start;
  Serial.println();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print(duration);
  Serial.println();
  delay(100);
}


// -- END OF FILE --
