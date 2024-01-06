//
//    FILE: TM1637_custom.ino
//  AUTHOR: Richard Jones
// PURPOSE: demo TM1637 library
//    DATE: 3 October 2022
//     URL: https://github.com/radionerd
//     URL: https://github.com/RobTillaart/TM1637_RT

//  Demonstration of how to display char *buff and override the TM1637 library asciiTo7Segment virtual function
//  to create a custom 7 segment character set.
//  The letter 'A' becomes swapped with @ in this trivial example
//  Status: Experimental. Tested on STM32F103C8T6 Blue Pill and Arduino Nano only


#include "TM1637.h"


const int DISPLAY_DIGITS_6 = 6;

// This example shows how to override the TM1637_RT library 7 segment patterns and copy the display output
// to the serial port overriding and adding to the library methods.
// myTM1637 inherits from library class TM1637 and overrides the library asciiTo7Segment() method.
// The derived class displayPChar() method also copies the display output to the serial port.

class myTM1637 : TM1637 {
  public:
  void setBrightness(uint8_t b) { TM1637::setBrightness(b);};

  void begin(uint8_t clockPin, uint8_t dataPin, uint8_t digits = 6) {TM1637::begin(clockPin,dataPin,digits);};

  void displayPChar( char * data ) {
    TM1637::displayPChar( &data[0] );  //  Call the base class
    Serial.println(data);              //  Copy display output to the serial port
  };

  uint8_t asciiTo7Segment ( char c ) {  //  Override library ascii to 7 segment conversion

    //        -01-
    //    20 |    | 02
    //        -40-
    //    10 |    | 04
    //        -08-    .80

    //7+1  Segment patterns for ASCII 0x30-0x5F
    const uint8_t asciiTo8Segment[] = {
      0x00,0x86,0x22,0x7f, 0x6d,0x52,0x7d,0x02,  //   !"# $%&'
      0x39,0x0f,0x7f,0x46, 0x80,0x40,0x80,0x52,  //  ()*+ ,-./
      0x3f,0x06,0x5b,0x4f, 0x66,0x6d,0x7d,0x07,  //  0123 4567
      0x7f,0x6f,0x09,0x89, 0x58,0x48,0x4c,0xD3,  //  89:; <=>?
      0x77,0x5f,0x7c,0x39, 0x5E,0x79,0x71,0x3d,  //  @aBC DEFG  NB: @ <-> A in this derived class
      0x74,0x06,0x0E,0x75, 0x38,0x37,0x54,0x5c,  //  HIJK LMNO
      0x73,0x67,0x50,0x6D, 0x78,0x3E,0x1C,0x9c,  //  PQRS TUVW
      0x76,0x6E,0x5B,0x39, 0x52,0x0F,0x23,0x08   //  XYZ[ /]^_
    };

    uint8_t  segments = c &0x80;
    c &= 0x7f;
    if ( c >= 0x60 ) c -= 0x20 ; // a-z -> A-Z
    if ( ( c >= 0x20 ) && ( c <= 0x5F ) ) {
      segments |= asciiTo8Segment[c-0x20];
    }
    return segments;
  }
};


myTM1637 myTM;


void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println(__FILE__);

  //  set clock pin, data pin to your own board pin names
  //  e.g.  myTM.begin(PB8, PB9 , DISPLAY_DIGITS_6 );
  myTM.begin( 14, 15 , DISPLAY_DIGITS_6 );  //  clock pin, data pin, and digits

  myTM.setBrightness(2);

}


void loop()
{
  char buff[20];
  static int seconds;
  //  Show A and @ swapped over on custom character set
  //  Compare the 7 segment display with the text shown on the serial monitor
  sprintf(buff,"@-A%3d", seconds++%100 );
  myTM.displayPChar(buff);  //  send buffer to display and serial port
  delay(1000);
}


//  -- END OF FILE --
