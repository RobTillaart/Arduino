//
//    FILE: rain_demo_count.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo experimental intensity formula
//     URL: https://github.com/RobTillaart/RAIN
//
//  EXPERIMENTAL
//  place the FC-37 under an angle (30° ?) so drop that hit, will roll off.
//  This sketch tries to count drops and convert it
//
//  should use an RTC, GPS or NTP for real 24hr clock
//  optional a nice LCD display.



#include "rain.h"

RAIN  RS(A0);
float threshold = 10.0;      //  adjust if needed.
float literPerDrop = 0.069;  //  adjust if needed

float mmDay = 0;
float mmHour = 0;
float mmMinute = 0;

uint32_t lastPrint  = 0;
uint32_t lastDay    = 0;
uint32_t lastHour   = 0;
uint32_t lastMinute = 0;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RAIN_LIB_VERSION: ");
  Serial.println(RAIN_LIB_VERSION);
  Serial.println();

  RS.begin(5.000, 1023);

  //  measured in an earlier run, adjust to your calibration.
  RS.setDryReference(5.0);

  RS.read();
  Serial.println(RS.percentage());

  for (int i = 0; i < 10000; i++)
    Serial.println(analogRead(A0));
}


void loop()
{
  //  should be a state machine to prevent blocking.
  //  count drops when going from DROP => IDLE or IDLE => DROP
  //  to investigate 
  
  //  wait for drop
  RS.read();
  if (RS.percentage() >= threshold)
  {
    mmDay    += literPerDrop;
    mmHour   += literPerDrop;
    mmMinute += literPerDrop;
    //  wait for drop to be gone
    //  adjust treshold if needed.
    while (RS.percentage() >= threshold) RS.read();
  }

  //  time to print?
  uint32_t now = millis();
  if (now - lastPrint >= 1000)   //  60 * 1000
  {
    Serial.print(mmDay);
    Serial.print("\t");
    Serial.print(mmHour);
    Serial.print("\t");
    Serial.print(mmMinute);
    Serial.print("\n");
    lastPrint = now;
  }

  //  time to reset?
  if (now - lastMinute >= 60000UL)
  {
    lastMinute = now;
    mmMinute = 0;
  }
  if (now - lastHour >= (60 * 60000UL))
  {
    lastHour = now;
    mmHour = 0;
  }
  if (now - lastDay >= (24 * 60 * 60000UL))
  {
    lastDay = now;
    mmMinute = 0;
  }

}


//  -- END OF FILE --
