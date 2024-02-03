//
//    FILE: RS485.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 30-okt-2017
// VERSION: 0.5.0
// PURPOSE: Arduino library for RS485 modules (MAX485)
//     URL: https://github.com/RobTillaart/RS485


#include "RS485.h"


//  - a stream - SWserial of HW serial (preferred)
//  - a pin for TX- enable line
//  - slave ID, or 0 as master (or don't care)
RS485::RS485(Stream * stream, uint8_t sendPin, uint8_t deviceID)
{
  _stream   = stream;
  _sendPin  = sendPin;
  _deviceID = deviceID;

  pinMode(_sendPin, OUTPUT);
  //  default receiver mode ==>  _sendPin == LOW
  setRXmode();
}


uint8_t RS485::getDeviceID()
{
  return _deviceID;
}


///////////////////////////////////////////////////////
//
//  STREAM INTERFACE
//
int RS485::available()
{
  return _stream->available();
}


int RS485::read()
{
  return _stream->read();
}


int RS485::peek()
{
  return _stream->peek();
}


void RS485::flush()
{
  _stream->flush();
}


size_t RS485::write(uint8_t c)
{
  setTXmode();       //  transmit mode
  size_t n = _stream->write(c);
  _stream->flush();  //  wait for all data transmitted
  setRXmode();       //  receiver mode
  return n;
}


size_t RS485::write(char * array, uint8_t length)
{
  return write((uint8_t *)array, length);
}


///////////////////////////////////////////////////////
//
//  discussion about write and yield see
//  - https://github.com/RobTillaart/RS485/issues/2
//

//  #define RS485_YIELD_ENABLE  1

#ifdef RS485_YIELD_ENABLE

//  smallest and slightly fastest.
size_t RS485::write(uint8_t * array, uint8_t length)
{
  setTXmode();       //  transmit mode
  size_t n = 0;
  for (uint8_t i = 0; i < length; i++)
  {
    n += _stream->write(array[i]);
    yield();
  }
  setRXmode();       //  receiver mode
  return n;
}

#else

//  0.2.1 version
//  no yield() calls - might be blocking...
size_t RS485::write(uint8_t * array, uint8_t length)
{
  setTXmode();       //  transmit mode
  size_t n = _stream->write(array, length);
  _stream->flush();  //  wait for all data transmitted
  setRXmode();       //  receiver mode
  return n;
}

#endif



///////////////////////////////////////////////////////
//
//  EXPERIMENTAL - use at own risk.
//
///////////////////////////////////////////////////////
//
//  commando   value  meaning
//
//    ASCII_SOH      0x01   start of header
//    ASCII_STX      0x02   start of text
//    ASCII_ETX      0x03   end of text
//    ASCII_EOT      0x04   end of transmission
//
//  optional
//    ASCII_ACK      0x06   ACKnowledge
//    ASCII_NAK      0x15   Not Acknowledge
//    ASCII_CAN      0x18   CANcel
//
///////////////////////////////////////////////////////
//
//  A message has the following layout
//
//     ASCII_SOH          start of header
//     deviceID           to
//     deviceID           sender
//     length             length of message
//        ASCII_STX          start of text
//        message            idem
//        CHECKSUM           idem, message only!
//        ASCII_ETX          end of text
//     ASCII_EOT          end of transmission
//

size_t RS485::send(uint8_t receiverID, uint8_t msg[], uint8_t len)
{
  size_t n = 0;
  uint8_t CHKSUM = 0;

  setTXmode();                 //  transmit mode
  _stream->write(ASCII_SOH);
  n += _stream->write(receiverID);  //  TO
  n += _stream->write(_deviceID);   //  FROM
  n += _stream->write(len);         //  LENGTH BODY
  n += _stream->write(ASCII_STX);
  for (int i = 0; i < len; i++)
  {
    n += _stream->write(msg[i]);
    CHKSUM ^= msg[i];          //  Simple XOR checksum.
  }
  n += _stream->write(CHKSUM);
  n += _stream->write(ASCII_ETX);
  n += _stream->write(ASCII_EOT);
  _stream->flush();
  setRXmode();                 //  receive mode

  return n;
}


//  returns true if complete message is captured.
//  multiple calls needed as it should be non-blocking.
bool RS485::receive(uint8_t &senderID, uint8_t msg[], uint8_t &msglen)
{
  static uint8_t state  = 0;
  static uint8_t length = 0;
  static bool    forMe  = false;
  static uint8_t CHKSUM = 0;

  if (_stream->available() == 0) return false;

  uint8_t v = _stream->read();
  //  if (debug) Serial.print(v, HEX);
  // Serial.print(state, HEX);
  // Serial.print('\t');
  // Serial.println(v, HEX);

  switch(state)
  {
    //  waiting for new packet
    case 0:
      if (v == ASCII_SOH)
      {
        _bidx = 0;        //  start new packet
        CHKSUM = 0;
        state = 1;
      }
      break;

    //  extract receiver
    case 1:
      forMe = ((v == _deviceID) || (v == 255));  //  PM or broadcast?
      if (not forMe) state = 99;
      else state = 2;
      break;

    //  extract sender
    case 2:
      senderID = v;
      state = 3;
      break;

    //  extract length
    case 3:
      msglen = v;
      length = v;
      state = 4;
      break;

    //  expect ASCII_STX
    case 4:
      if (v == ASCII_STX) state = 5;
      else state = 99;
      break;

    //  extract message
    case 5:
      if (length == 0)
      {
        //  expect checksum
        if (CHKSUM == v) state = 6;
        else
        {
          //  debug failing checksum
          //  Serial.print(CHKSUM, HEX);
          //  Serial.print('\t');
          //  Serial.println(v, HEX);
          state = 99;  //  for debug change to state = 6;
        }
        break;
      }
      //  error handling  if v not ASCII ?
      _buffer[_bidx++] = v;
      CHKSUM ^= v;
      length--;
      break;

    //  expect ASCII_ETX
    case 6:
      if (v == ASCII_ETX) state = 7;
      else state = 99;
      break;

    //  expect ASCII_EOT
    case 7:
      if (v == ASCII_EOT)
      {
        msglen = _bidx;
        for (int i = 0; i < msglen; i++)
        {
          msg[i] = _buffer[i];
        }
        state = 0;
        return true;
      }
      state = 99;
      break;

    //  SKIP until next packet
    case 99:  //  wait for ASCII_EOT in case of error
      if (v == ASCII_EOT) state = 0;
      break;
  }

  return false;
}


size_t RS485::send(uint8_t receiverID, char msg[], uint8_t len)
{
  return send(receiverID, (uint8_t *)msg, len);
}


bool RS485::receive(uint8_t &senderID, char msg[], uint8_t &len)
{
  return receive(senderID, (uint8_t*) msg, len);
}


//////////////////////////////////////////////////
//
//  PRIVATE
//


//  -- END OF FILE --

