//
//    FILE: print_currency_TLA.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: display an int as currency test
//     URL: https://github.com/RobTillaart/currency
//
//  To be extended

#include "Arduino.h"
#include "currency.h"


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("CURRENCY_LIB_VERSION: ");
  Serial.println(CURRENCY_LIB_VERSION);
  Serial.println();
  delay(100);


  Serial.println( BTC(10000000) );
  Serial.println( USD(10000000) );
  Serial.println( EUR(10000000) );
  Serial.println( GBP(10000000) );
  Serial.println( RUB(10000000) );
  Serial.println( JPY(10000000) );
  Serial.println( CNY(10000000) );
  Serial.println();

  Serial.println( BTC(10000000) );
  Serial.println( BTC64(10000000) );
  Serial.println();
  Serial.println( USD(10000000) );
  Serial.println( USD64(10000000) );
  Serial.println();

  Serial.println("done");
}


void loop()
{
}


//  -- END OF FILE --
