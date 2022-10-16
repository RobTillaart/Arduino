//
//    FILE: FRAM_RINGBUFFER.h
//  AUTHOR: Rob Tillaart
//    DATE: 2022-10-03
// PURPOSE: Arduino library for I2C FRAM based RING BUFFER
//     URL: https://github.com/RobTillaart/FRAM_I2C
//


#include "FRAM_RINGBUFFER.h"


FRAM_RINGBUFFER::FRAM_RINGBUFFER()
{
}


uint32_t FRAM_RINGBUFFER::begin(FRAM *fram, uint32_t size, uint32_t start)
{
  _fram  = fram;
  _size  = size;
  _start = start + 20;    //  allocate 5 uint32_t for storage.
  flush();
  _saved = false;
  return _start + _size;  //  first free FRAM location.
}


//////////////////////////////////////////////////////////////////
//
//  ADMINISTRATIVE
//
void FRAM_RINGBUFFER::flush()
{
  _front = _tail = _start;
  _count = 0;
  _saved = false;
}


uint32_t FRAM_RINGBUFFER::size()
{
  return _size;
}


uint32_t FRAM_RINGBUFFER::count()
{
  return _count;
}


bool FRAM_RINGBUFFER::full()
{
  return _count == _size;
}


bool FRAM_RINGBUFFER::empty()
{
  return _count == 0;
}


uint32_t FRAM_RINGBUFFER::free()
{
  return _size - _count;
}


float FRAM_RINGBUFFER::freePercent()
{
  return (100.0 * _count) / _size;
}

//  DEBUG
//  uint32_t FRAM_RINGBUFFER::tail() { return _tail; };
//  uint32_t FRAM_RINGBUFFER::front() { return _front; };


//////////////////////////////////////////////////////////////////
//
//  BYTE INTERFACE
//
int FRAM_RINGBUFFER::write(uint8_t value)
{
  if (full()) return FRAM_RB_ERR_BUF_FULL;
  _fram->write8(_front, value);
  _saved = false;
  _front++;
  _count++;
  if (_front >= _start + _size) _front = _start;
  return 1;
}


int FRAM_RINGBUFFER::read()
{
  if (empty()) return FRAM_RB_ERR_BUF_EMPTY;
  int value = _fram->read8(_tail);
  _saved = false;
  _tail++;
  _count--;
  if (_tail >= _start + _size) _tail = _start;
  return value;
}


int FRAM_RINGBUFFER::peek()
{
  if (empty()) return FRAM_RB_ERR_BUF_EMPTY;
  int value = _fram->read8(_tail);
  return value;
}


///////////////////////////////////////////////////
//
//  MAKE RINGBUFFER PERSISTENT OVER REBOOTS
//
bool FRAM_RINGBUFFER::isSaved()
{
  return _saved;
}


void FRAM_RINGBUFFER::save() 
{
  uint32_t pos = _start - 20;
  if (not _saved)
  {
    uint32_t checksum = _size + _front + _tail + _count;
    _fram->write32(pos +  0, _size );
    _fram->write32(pos +  4, _front);
    _fram->write32(pos +  8, _tail );
    _fram->write32(pos + 12, _count);
    _fram->write32(pos + 16, checksum);
    _saved = true;
  }
}


bool FRAM_RINGBUFFER::load()  
{
  uint32_t pos = _start - 20;
  uint32_t size     = _fram->read32(pos +  0);
  uint32_t front    = _fram->read32(pos +  4);
  uint32_t tail     = _fram->read32(pos +  8);
  uint32_t count    = _fram->read32(pos + 12);
  uint32_t checksum = _fram->read32(pos + 16);
  //  checksum test should be enough.
  //  optional these are possible
  //    (_start <= _front) && (_front < _start + _size);
  //    (_start <= _tail)  && (_tail < _start + _size);
  _saved = (checksum == size + front + tail + count);
  if (_saved)
  {
    _size = size;
    _front = front;
    _tail = tail;
    _count = count;
  }
  return _saved;
}


void FRAM_RINGBUFFER::wipe()
{
  uint32_t pos = _start - 20;       //  also overwrite metadata
  while (pos < _start + _size - 4)  //  prevent writing adjacent FRAM
  {
    _fram->write32(pos, 0xFFFFFFFF);
    pos += 4;
  }
  while (pos < _start + _size)      //  if _size not a multiple of 4.
  {
    _fram->write8(pos, 0xFF);
    pos++;
  }
  flush();  //  reset internal variables too.
}



// -- END OF FILE --

