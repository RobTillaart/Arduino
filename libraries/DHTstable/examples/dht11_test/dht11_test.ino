//
//    FILE: dht11_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DHT library test sketch for DHT11 && Arduino
//     URL: https://github.com/RobTillaart/DHTstable



#include "DHTStable.h"

DHTStable DHT;

#define DHT11_PIN       5


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTSTABLE_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}


void loop()
{
  // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
      Serial.print("OK,\t"); 
      break;
    case DHTLIB_ERROR_CHECKSUM: 
      Serial.print("Checksum error,\t"); 
      break;
    case DHTLIB_ERROR_TIMEOUT: 
      Serial.print("Time out error,\t"); 
      break;
    default: 
      Serial.print("Unknown error,\t"); 
      break;
  }
  // DISPLAY DATA
  Serial.print(DHT.getHumidity(), 1);
  Serial.print(",\t");
  Serial.println(DHT.getTemperature(), 1);

  delay(2000);
}


// -- END OF FILE --
