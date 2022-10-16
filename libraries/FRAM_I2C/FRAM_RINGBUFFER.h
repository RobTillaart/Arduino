#pragma once
//
//    FILE: FRAM_RINGBUFFER.h
//  AUTHOR: Rob Tillaart
//    DATE: 2022-10-03
// PURPOSE: Arduino library for I2C FRAM based ring buffer
//     URL: https://github.com/RobTillaart/FRAM_I2C
//


#include "FRAM.h"   //   https://github.com/RobTillaart/FRAM_I2C


//  ERROR CODES
#define FRAM_RB_OK                     0
#define FRAM_RB_ERR_BUF_FULL          -1
#define FRAM_RB_ERR_BUF_EMPTY         -2
#define FRAM_RB_ERR_BUF_NO_ROOM       -21    //  (almost) full
#define FRAM_RB_ERR_BUF_NO_DATA       -22    //  (almost) empty


class FRAM_RINGBUFFER
{
public:


  //////////////////////////////////////////////////////////////////
  //
  //  CONSTRUCTOR + BEGIN
  //
  FRAM_RINGBUFFER();

  //  fram = pointer to FRAM object
  //  size in bytes
  //  memAddr in bytes where ring buffer starts
  //  returns uint32_t == first free (next) FRAM location.
  uint32_t begin(FRAM *fram, uint32_t size, uint32_t memAddr);


  //////////////////////////////////////////////////////////////////
  //
  //  ADMINISTRATIVE
  //
  void      flush();
  uint32_t  size();
  uint32_t  count();
  uint32_t  free();
  float     freePercent();

  bool      full();
  bool      empty();

  //  DEBUG
  //  uint32_t tail() { return _tail; };
  //  uint32_t front() { return _front; };


  //////////////////////////////////////////////////////////////////
  //
  //  BYTE INTERFACE
  //
  //  returns bytes written.
  //  - FRAM_RB_ERR_BUF_FULL indicates full buffer.
  int write(uint8_t value);
  //  returns value read
  //  - FRAM_RB_ERR_BUF_EMPTY indicates empty buffer.
  int read();
  //  returns value read
  //  - FRAM_RB_ERR_BUF_EMPTY indicates empty buffer.
  int peek();


  //////////////////////////////////////////////////////////////////
  //
  //  OBJECT INTERFACE
  //
  //  returns bytes written.
  //  - FRAM_RB_ERR_BUF_NO_ROOM indicates (almost) full buffer 
  //    ==>  object does not fit.
  template <class T> int write(T &obj)
  {
    uint8_t objectSize = sizeof(obj);
    if ((_size - _count) <  objectSize) return FRAM_RB_ERR_BUF_NO_ROOM;
    uint8_t * p = (uint8_t *)&obj;
    for (uint8_t i = 0; i < objectSize; i++)
    {
      write(*p++);
    }
    _saved = false;
    return objectSize;
  };

  //  returns bytes read.
  //  - FRAM_RB_ERR_BUF_NO_DATA indicates (almost) empty buffer 
  //    ==>  Too few bytes to read object.
  template <class T> int read(T &obj)
  {
    uint8_t objectSize = sizeof(obj);
    if (_count <  objectSize) return FRAM_RB_ERR_BUF_NO_DATA;
    uint8_t * p = (uint8_t *)&obj;
    for (uint8_t i = 0; i < objectSize; i++)
    {
      *p++ = read();
    }
    _saved = false;
    return objectSize;
  };

  //  returns bytes read.
  //  - FRAM_RB_ERR_BUF_NO_DATA indicates (almost) empty buffer 
  //    ==>  Too few bytes to read object.
  template <class T> int peek(T &obj)
  {
    uint8_t objectSize = sizeof(obj);
    if (_count <  objectSize) return FRAM_RB_ERR_BUF_NO_DATA;
    bool prevSaved = _saved;          //  remember saved state
    uint32_t previousTail = _tail;    //  remember _tail 'pointer'
    int n = read(obj);
    _tail = previousTail;             //  restore _tail 'pointer'
    _saved = prevSaved;               //  restore _saved
    _count += n;
    return n;
  };


  ///////////////////////////////////////////////////
  //
  //  MAKE RINGBUFFER PERSISTENT OVER REBOOTS
  //
  bool isSaved();
  //  stores the internal variables + checksum.
  //  if you need constant persistency, 
  //  call save() after every read() write() flush()
  void save();
  //  retrieves the internal variables + verify checksum.
  //  returns false if checksum fails ==> data inconsistent (no load)
  bool load();
  //  removes all data from ring buffer by overwriting the FRAM.
  void wipe();


private:
  uint32_t _count = 0;        //  optimization == front - tail (+ size)
  uint32_t _size  = 0;
  uint32_t _start = 0;
  uint32_t _front = _start;
  uint32_t _tail  = _start;
  FRAM *   _fram;
  bool     _saved = false;
};


// -- END OF FILE --

