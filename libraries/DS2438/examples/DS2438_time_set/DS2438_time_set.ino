//
//    FILE: DS2438_time_convert.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DS2438 library time registers conversion
//     URL: https://github.com/RobTillaart/DS2438
//     URL: https://github.com/RobTillaart/dateTimeHelpers


#include "DS2438.h"
#include "dateTimeHelpers.h"

#define ONE_WIRE_BUS          2

OneWire   oneWire(ONE_WIRE_BUS);
DS2438    bm(&oneWire);

uint32_t lastPrint = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS2438_LIB_VERSION: ");
  Serial.println(DS2438_LIB_VERSION);
  Serial.println();


  bm.begin();
  Serial.print("Connect: ");
  Serial.println(bm.isConnected());

  dumpTimes();
  bm.writeElapsedTimeMeter(0);  //  reset to zero.
}


void loop()
{
  //  print the time parameters every 10 seconds.
  if (millis() - lastPrint >= 10000)
  {
    lastPrint = millis();
    dumpTimes();
  }

}


void dumpTimes()
{
  uint16_t days;
  uint8_t hours, minutes, sec;
  uint32_t ETM =  bm.readElapsedTimeMeter();

  secondsSplit(ETM, &days, &hours, &minutes, &sec);
  Serial.println("\nElapsedTimeMeter");
  Serial.print(ETM);
  Serial.print(" = ");
  Serial.print(days);
  Serial.print(" days ");
  Serial.print(hours);
  Serial.print(" hours ");
  Serial.print(minutes);
  Serial.print(" minutes ");
  Serial.print(sec);
  Serial.print(" seconds. ");
  Serial.println();

  uint32_t DTM =  bm.readDisconnectTime();
  secondsSplit(DTM, &days, &hours, &minutes, &sec);
  Serial.println("\nDisconnectTime");
  Serial.print(DTM);
  Serial.print(" = ");
  Serial.print(days);
  Serial.print(" days ");
  Serial.print(hours);
  Serial.print(" hours ");
  Serial.print(minutes);
  Serial.print(" minutes ");
  Serial.print(sec);
  Serial.print(" seconds. ");
  Serial.println();

  uint32_t EOC =  bm.readEndOfChargeTime();
  secondsSplit(EOC, &days, &hours, &minutes, &sec);
  Serial.println("\nEndOfChargeTime");
  Serial.print(EOC);
  Serial.print(" = ");
  Serial.print(days);
  Serial.print(" days ");
  Serial.print(hours);
  Serial.print(" hours ");
  Serial.print(minutes);
  Serial.print(" minutes ");
  Serial.print(sec);
  Serial.print(" seconds. ");
  Serial.println();
}



//  -- END OF FILE --
