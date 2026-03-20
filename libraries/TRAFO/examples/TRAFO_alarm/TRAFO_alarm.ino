//
//    FILE: TRAFO_alarm.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple RMS alarm
//     URL: https://github.com/RobTillaart/TRAFO
//
//  This sketch defines two level, a low and high treshold
//  The measured voltage should be between these levels.
//  If not a message is printed with a (simple) timestamp.
//  Alternatively one could sound a buzzer or use a RGB LED 
//  and the map2color library to map the voltage to a color of choice.


#include "TRAFO.h"


TRAFO myTrafo;

//  to configure
float lowTreshold  = 210;
float highTreshold = 250;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TRAFO_LIB_VERSION: ");
  Serial.println(TRAFO_LIB_VERSION);
  Serial.println();

  myTrafo.begin(readADC, 1023, 5.0, 708);
}


void loop()
{
  float voltage = myTrafo.getRMS();
  if (voltage < lowTreshold) 
  {
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("LOW ALARM");
  }
  if (voltage > highTreshold) 
  {
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("HIGH ALARM");
  }
 
  Serial.println(myTrafo.getRMS());
  
  delay(1000);  //  just to simulate 
}


int32_t readADC()
{
  return (int32_t)analogRead(A0);
}


//  -- END OF FILE --
