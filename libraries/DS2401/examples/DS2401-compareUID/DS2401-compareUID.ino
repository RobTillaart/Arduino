//
//    FILE: DS2401_compareUID.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DS2401 lib demo
//     URL: https://github.com/RobTillaart/DS2401


#include <OneWire.h>
#include "DS2401.h"


#define ONE_WIRE_BUS          2

OneWire   oneWire(ONE_WIRE_BUS);
DS2401    ds24(&oneWire);

uint8_t   uid[8];


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DS2401_LIB_VERSION: ");
  Serial.println(DS2401_LIB_VERSION);


  ds24.begin();  //  read UID

  Serial.print("\ngetUID:\t ");
  ds24.getUID(uid);
  for (int i = 0; i < 8; i++)
  {
    if (uid[i] < 0x10) Serial.print(0);
    Serial.print(uid[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("compareUID:\t");
  Serial.println(ds24.compareUID(uid));
  Serial.println();


  Serial.print("\ngetUID6:\t ");
  ds24.getUID6(uid);
  for (int i = 0; i < 6; i++)
  {
    if (uid[i] < 0x10) Serial.print(0);
    Serial.print(uid[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("compareUID6:\t");
  Serial.println(ds24.compareUID6(uid));
  Serial.println();

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
