//
//    FILE: PrintString.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Class that captures prints into a String 
//    DATE: 2017-12-09
//     URL: 
// HISTORY: 0.1.0 2017-12-09 initial version
//
// Released to the public domain
//

#ifndef PrintString_h
#define PrintString_h

#include "Arduino.h"
#include "Print.h"

#define PRINTSTRING_VERSION "0.1.0"

class PrintString: public Print
{
public:
  PrintString() {};
  
  size_t write(uint8_t c)
  {
    buffer += (char)c;
    return 1;
  }
  
  void clear()
  {
    buffer = "";
  }
 
  String getString() { return buffer; }

private:
  String buffer;
};
#endif
// -- END OF FILE --
