//
//    FILE: PrintCharArray.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Class that captures prints into a char array
//    DATE: 2017-12-07
//     URL:
// HISTORY: 0.1.0 2017-12-07 initial version
//
// Released to the public domain
//

#ifndef PrintCharArray_h
#define PrintCharArray_h

#include "Print.h"

#define PRINTCHARARRAY_VERSION "0.1.0"
#define BUFFERSIZE      256

class PrintCharArray: public Print
{
  public:
    PrintCharArray() {};

    size_t write(uint8_t c)
    {
      if (index < BUFFERSIZE-1)
      {
        buffer[index] = c;
        index++;
        buffer[index] = '\0';
        return 1;
      }
      return 0;
    }

    void clear()
    {
      index = 0;
      buffer[index] = '\0';
    }

    int free() { return (BUFFERSIZE - index); }

    int size() { return index; }

    char * getBuffer() { return buffer; }

  private:
    char buffer[BUFFERSIZE];
    int index = 0;
};
#endif
// -- END OF FILE --
