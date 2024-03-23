//
//    FILE: DS2401_getUID4.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DS2401 lib getUID
//     URL: https://github.com/RobTillaart/DS2401

#include <OneWire.h>
#include "DS2401.h"


#define ONE_WIRE_BUS          2

OneWire   oneWire(ONE_WIRE_BUS);
DS2401    ds24(&oneWire);

uint32_t  uid;  //  4 bytes


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DS2401_LIB_VERSION: ");
  Serial.println(DS2401_LIB_VERSION);

  ds24.begin();  //  read UID
  Serial.print("\ngetUID4:\t ");
  ds24.getUID4(&uid);
  Serial.println(uid, HEX);
  Serial.print("compareUID4:\t ");
  Serial.println(ds24.compareUID4(&uid));

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
