//
//    FILE: RS485.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 30-okt-2017
// VERSION: 0.2.5
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
  setRXmode();    //  receiver mode
}


//  0.3.0
// void RS485::begin(uint32_t baudRate)
// {
  // _stream->begin(baudRate);
  // setMicrosPerByte(baudRate);
// }


void RS485::setMicrosPerByte(uint32_t baudRate)
{
  //  count 11 bits time per byte
  _microsPerByte = (11 * 1000000) / baudRate ;
}


uint32_t RS485::getMicrosPerByte()
{
  return _microsPerByte;
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
  setTXmode();    //  transmit mode
  size_t n = _stream->write(c);
  delayMicroseconds(_microsPerByte);
  setRXmode();    //  receiver mode
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
  uint8_t n = 0;
  for (uint8_t i = 0; i < length; i++)
  {
    n += write(array[i]);
    yield();
  }
  return n;
}

#else

//  0.2.1 version
//  no yield() calls - might be blocking...
size_t RS485::write(uint8_t * array, uint8_t length)
{
  setTXmode();    //  transmit mode
  size_t n = _stream->write(array, length);
  delayMicroseconds(length * _microsPerByte);
  setRXmode();    //  receiver mode
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
//    SOH      0x01   start of header
//    STX      0x02   start of text
//    ETX      0x03   end of text
//    EOT      0x04   end of transmission
//
//  optional
//    ACK      0x06   ACKnowledge
//    NAK      0x15   Not Acknowledge
//    CAN      0x18   CANcel
//
///////////////////////////////////////////////////////
//
//  A message has the following layout
//
//     SOH          start of header
//     deviceID     to
//     deviceID     sender
//     length       length of message
//        STX          start of text
//        message      idem
//        CHECKSUM     idem, message only!
//        ETX          end of text
//     EOT          end of transmission
//

void RS485::send(uint8_t receiverID, uint8_t msg[], uint8_t len)
{
  uint8_t CHKSUM = 0;
  setTXmode();    //  transmit mode
  _stream->write(SOH);
  _stream->write(receiverID);  //  TO
  _stream->write(_deviceID);   //  FROM
  _stream->write(len);         //  LENGTH BODY
  _stream->write(STX);
  for (int i = 0; i < len; i++)
  {
    _stream->write(msg[i]);
    CHKSUM ^= msg[i];          //  Simple XOR checksum.
  }
  _stream->write(CHKSUM);
  _stream->write(ETX);
  _stream->write(EOT);
  delayMicroseconds((len + 8 + 2) * _microsPerByte);  // + 2 to be sure...
  setRXmode();
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
      if (v == SOH)
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

    //  expect STX
    case 4:
      if (v == STX) state = 5;
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

    //  expect ETX
    case 6:
      if (v == ETX) state = 7;
      else state = 99;
      break;

    //  expect EOT
    case 7:
      if (v == EOT)
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
    case 99:  //  wait for EOT in case of error
      if (v == EOT) state = 0;
      break;
  }

  return false;
}



//////////////////////////////////////////////////
//
//  PRIVATE
//


//  -- END OF FILE --

