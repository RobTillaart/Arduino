//
//    FILE: print_currency.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: display an int as currency test
//     URL: https://github.com/RobTillaart/currency


#include "Arduino.h"
#include "currency.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  Serial.println( currency(10000000, 0, '.', ',', '$') );
  Serial.println( currency(10000000, 1, '.', ',', 'E') );
  Serial.println( currency(10000000, 2, '.', ',', 'Y') );
  Serial.println( currency(10000000, 3, '.', ',', '$') );
  Serial.println( currency(10000000, 4, '.', ',', '$') );
  Serial.println();

  Serial.println( currency(0, 2, '.', ',', '$') );
  Serial.println( currency(9, 2, '.', ',', '$') );
  Serial.println( currency(10, 2, '.', ',', '$') );
  Serial.println( currency(99, 2, '.', ',', '$') );
  Serial.println( currency(100, 2, '.', ',', '$') );
  Serial.println( currency(999, 2, '.', ',', '$') );
  Serial.println( currency(1000, 2, '.', ',', '$') );
  Serial.println( currency(9999, 2, '.', ',', '$') );
  Serial.println( currency(10000, 2, '.', ',', '$') );
  Serial.println( currency(99999, 2, '.', ',', '$') );
  Serial.println( currency(100000, 2, '.', ',', '$') );
  Serial.println( currency(999999, 2, '.', ',', '$') );
  Serial.println( currency(1000000, 2, '.', ',', '$') );
  Serial.println( currency(9999999, 2, '.', ',', '$') );
  Serial.println( currency(10000000, 2, '.', ',', '$') );
  Serial.println( currency(99999999, 2, '.', ',', '$') );
  Serial.println( currency(100000000, 2, '.', ',', '$') );
  Serial.println( currency(999999999, 2, '.', ',', '$') );
  Serial.println( currency(1000000000, 2, '.', ',', '$') );
  Serial.println();

  Serial.println( currency(-0, 2, '.', ',', '$') );
  Serial.println( currency(-9, 2, '.', ',', '$') );
  Serial.println( currency(-10, 2, '.', ',', '$') );
  Serial.println( currency(-99, 2, '.', ',', '$') );
  Serial.println( currency(-100, 2, '.', ',', '$') );
  Serial.println( currency(-999, 2, '.', ',', '$') );
  Serial.println( currency(-1000, 2, '.', ',', '$') );
  Serial.println( currency(-9999, 2, '.', ',', '$') );
  Serial.println( currency(-10000, 2, '.', ',', '$') );
  Serial.println( currency(-99999, 2, '.', ',', '$') );
  Serial.println( currency(-100000, 2, '.', ',', '$') );
  Serial.println( currency(-999999, 2, '.', ',', '$') );
  Serial.println( currency(-1000000, 2, '.', ',', '$') );
  Serial.println( currency(-9999999, 2, '.', ',', '$') );
  Serial.println( currency(-10000000, 2, '.', ',', '$') );
  Serial.println( currency(-99999999, 2, '.', ',', '$') );
  Serial.println( currency(-100000000, 2, '.', ',', '$') );
  Serial.println( currency(-999999999, 2, '.', ',', '$') );
  Serial.println( currency(-1000000000, 2, '.', ',', '$') );
  Serial.println();

  Serial.println( currency64(-999999999999999, 2, '.', ',', '$') );
  Serial.println( currency64(-1000000000000000, 2, '.', ',', '$') );

  Serial.println( bitcoin64(-123456789123456789) );
  Serial.println( yuan64(-1000000000000000) );

  Serial.println("done");
}


void loop()
{
}


//  -- END OF FILE --

