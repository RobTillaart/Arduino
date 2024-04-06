//
//    FILE: asyncAnalogTest.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


#include "AsyncAnalog.h"


AsyncAnalog AA(A0);

uint32_t start = 0;
uint32_t duration = 0;
uint16_t count = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ASYNCANALOG_LIB_VERSION: ");
  Serial.println(ASYNCANALOG_LIB_VERSION);

  Serial.print("\nstart: ");
  Serial.println(analogRead(0));

  //  request initial measurement
  AA.start();
  start = micros();
}


void loop()
{

  //  if measurement ready
  if (AA.ready())
  {
    // get data
    duration = micros() - start;
    uint16_t val = AA.value();

    //  process measurement
    Serial.print(duration);
    Serial.print('\t');
    Serial.print(val);
    Serial.print('\t');
    Serial.println(count);

    //  request a new measurement
    AA.start();
    start = micros();


    count = 0;
  }

  //  do other stuff here
  count++;
}


//  -- END OF FILE --
