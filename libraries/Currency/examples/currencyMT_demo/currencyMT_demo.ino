//
//    FILE: currencyMT_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test currency class implementation
//     URL: https://github.com/RobTillaart/currency


#include "Arduino.h"
#include "currencyMT.h"


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("CURRENCY_LIB_VERSION: ");
  Serial.println(CURRENCY_LIB_VERSION);
  Serial.println();
  delay(100);

  Serial.println( currency(10000000, 0, '.', ',', "USD") );
  Serial.println( currency(10000000, 1, '.', ',', "EUR") );
  Serial.println( currency(0, 2, '.', ',', "JPY") );
  Serial.println( currency(-100, 3, '.', ',', "IRP") );
  Serial.println( currency(12345678, 4, '.', ',', "BTC") );
  Serial.println();


  Serial.println( currency(10000000, 0, '.', ',', NULL) );
  Serial.println( currency(10000000, 1, '.', ',', NULL) );
  Serial.println( currency(10000000, 2, '.', ',', NULL) );
  Serial.println( currency(10000000, 3, '.', ',', NULL) );
  Serial.println( currency(10000000, 4, '.', ',', NULL) );
  Serial.println();

  Serial.println( EUR(0) );
  Serial.println( EUR(9) );
  Serial.println( EUR(10) );
  Serial.println( EUR(99) );
  Serial.println( EUR(100) );
  Serial.println( EUR(999) );
  Serial.println( EUR(1000) );
  Serial.println( EUR(9999) );
  Serial.println( EUR(10000) );
  Serial.println( EUR(99999) );
  Serial.println( EUR(100000) );
  Serial.println( EUR(999999) );
  Serial.println( EUR(1000000) );
  Serial.println( EUR(9999999) );
  Serial.println( EUR(10000000) );
  Serial.println( EUR(99999999) );
  Serial.println( EUR(100000000) );
  Serial.println( EUR(999999999) );
  Serial.println( EUR(1000000000) );
  Serial.println();

  Serial.println( EUR(-0, 2, '.', ',') );
  Serial.println( EUR(-9, 2, '.', ',') );
  Serial.println( EUR(-10, 2, '.', ',') );
  Serial.println( EUR(-99, 2, '.', ',') );
  Serial.println( EUR(-100, 2, '.', ',') );
  Serial.println( EUR(-999, 2, '.', ',') );
  Serial.println( EUR(-1000, 2, '.', ',') );
  Serial.println( EUR(-9999, 2, '.', ',') );
  Serial.println( EUR(-10000, 2, '.', ',') );
  Serial.println( EUR(-99999, 2, '.', ',') );
  Serial.println( EUR(-100000, 2, '.', ',') );
  Serial.println( EUR(-999999, 2, '.', ',') );
  Serial.println( EUR(-1000000, 2, '.', ',') );
  Serial.println( EUR(-9999999, 2, '.', ',') );
  Serial.println( EUR(-10000000, 2, '.', ',') );
  Serial.println( EUR(-99999999, 2, '.', ',') );
  Serial.println( EUR(-100000000, 2, '.', ',') );
  Serial.println( EUR(-999999999, 2, '.', ',') );
  Serial.println( EUR(-1000000000, 2, '.', ',') );
  Serial.println();

  Serial.println( currency64(-999999999999999, 2, '.', ',', "EUR") );
  Serial.println( currency64(-1000000000000000, 2, '.', ',', "EUR") );
  Serial.println();

  Serial.println("done");
}


void loop()
{
}


//  -- END OF FILE --
