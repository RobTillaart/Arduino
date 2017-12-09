//
//    FILE: PrintSize.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Class that determines printSize
//    DATE: 2017-12-09
//     URL:
// HISTORY: 0.1.0   2017-12-09 initial version
//
// Released to the public domain
//

#ifndef PrintSize_h
#define PrintSize_h

#include "Print.h"

#define PRINTSIZE_VERSION "0.1.0"

class PrintSize: public Print
{
public:
  PrintSize() {};

  size_t write(uint8_t c) { return 1; }
};
#endif
// -- END OF FILE --
