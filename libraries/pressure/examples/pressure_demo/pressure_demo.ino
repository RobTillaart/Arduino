//
//    FILE: pressure_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-11-25
//     URL: https://github.com/RobTillaart/pressure


#include "pressure.h"


pressure P;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRESSURE_LIB_VERSION: ");
  Serial.println(PRESSURE_LIB_VERSION);

  // convert one pressure to 12 output units.
  P.setMilliBar(1019.1);

  Serial.print("mBar: \t");    Serial.println(P.getMilliBar(),3);
  Serial.print("Bar: \t");     Serial.println(P.getBar(),3);
  Serial.print("PSI: \t");     Serial.println(P.getPSI(),3);
  Serial.print("ATM: \t");     Serial.println(P.getATM(),3);
  Serial.print("DYN: \t");     Serial.println(P.getDynes(),3);
  Serial.print("InchHg: \t");  Serial.println(P.getInchHg(),3);
  Serial.print("InchH20: \t"); Serial.println(P.getInchH2O(),3);
  Serial.print("Pascal: \t");  Serial.println(P.getPascal(),3);
  Serial.print("TORR: \t");    Serial.println(P.getTORR(),3);
  Serial.print("CmHg: \t");    Serial.println(P.getCmHg(),3);
  Serial.print("CMH20: \t");   Serial.println(P.getCmH2O(),3);
  Serial.print("MSW: \t");     Serial.println(P.getMSW(),3);
}

void loop()
{
}


// -- END OF FILE --
