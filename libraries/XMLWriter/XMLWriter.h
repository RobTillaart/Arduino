#pragma once
//
//    FILE: XMLWriter.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.5
//    DATE: 2013-11-06
// PURPOSE: Arduino library for creating XML


#include "Arduino.h"


#define XMLWRITER_VERSION         (F("0.3.5"))


//  for comment()
#define NOMULTILINE               false
#define MULTILINE                 true

//  for tagOpen(), tagEnd()
#define NEWLINE                   true
#define NONEWLINE                 false
#define NOINDENT                  false    //  for tagClose()

//  for tagEnd()
#define SLASH                     true
#define NOSLASH                   false

//  deepness of XML tree 5..10
//  needed for stack of tagStack
#ifndef XMLWRITER_MAXLEVEL
#define XMLWRITER_MAXLEVEL        5      //  adjust for deeper nested structures
#endif

#ifndef XMLWRITER_MAXTAGSIZE
#define XMLWRITER_MAXTAGSIZE      15     //  adjust for longer fields - !! eats memory !!
#endif

//  reduce footprint by commenting next line
#define XMLWRITER_ESCAPE_SUPPORT

//  configuration - setConfig
#define XMLWRITER_NONE            0x00
#define XMLWRITER_COMMENT         0x01
#define XMLWRITER_INDENT          0x02
#define XMLWRITER_NEWLINE         0x04

//  uncomment next line to reduce ~30bytes RAM in escape()  (AVR only)
//  #define __PROGMEM__


class XMLWriter : public Print
{
public:
  //  default = Serial
  XMLWriter(Print* stream = &Serial, uint8_t bufferSize = 10);
  ~XMLWriter();

  void reset();

  //  to show/strip comment, indent, newLine
  //  to minimize the output setConfig(0);
  void setConfig(uint8_t config);

  //  standard XML header
  void header();

  //  prints XMLWRITER_VERSION as comment
  void version();

  //  prints debug information into the XML as comment
  void debug();


  //  if multiline == true it does not indent to allow bigger text blocks
  //  <!-- text -->
  void comment(const char* text, const bool multiLine = false);

  //  add a number of newlines to the output, default = 1.
  void newLine(uint8_t n = 1);

  //  TAG
  //
  //  <tag>
  void tagOpen(const char* tag, const bool newline = true);
  //  <tag name="name">
  void tagOpen(const char* tag, const char* name, const bool newline = true);
  //  </tag>
  void tagClose(const bool ind = true);

  //  <tag
  void tagStart(const char* tag);
  //  field="value"
  void tagField(const char* field, const char* value);
  //   />
  void tagEnd(const bool newline = true, const bool addSlash = true);

  //  <tag>value</tag>
  void writeNode(const char* tag, const char* value);


  //  INDENT
  //
  //  typically 0,2,4; default == 2;
  //  multiple of 2;
  void    setIndentSize(const uint8_t size = 2) { _indentStep = size; };
  uint8_t getIndentSize() { return _indentStep; };
  //  for manual layout control
  void incrIndent()       { _indent += _indentStep; };
  void decrIndent()       { _indent -= _indentStep; };
  void indent();
  void raw(const char * str) { print(str); };


  void tagField(const char* field, const uint8_t  value, const uint8_t base = DEC);
  void tagField(const char* field, const uint16_t value, const uint8_t base = DEC);
  void tagField(const char* field, const uint32_t value, const uint8_t base = DEC);
  void tagField(const char* field, const int8_t   value, const uint8_t base = DEC);
  void tagField(const char* field, const int16_t  value, const uint8_t base = DEC);
  void tagField(const char* field, const int32_t  value, const uint8_t base = DEC);
  void tagField(const char* field, const int      value, const int base = DEC);
  void tagField(const char* field, const bool     value);
  void tagField(const char* field, const float    value, const uint8_t decimals = 2);
  void tagField(const char* field, const double   value, const uint8_t decimals = 2);



  void writeNode(const char* tag, const uint8_t   value, const uint8_t base = DEC);
  void writeNode(const char* tag, const uint16_t  value, const uint8_t base = DEC);
  void writeNode(const char* tag, const uint32_t  value, const uint8_t base = DEC);
  void writeNode(const char* tag, const int8_t    value, const uint8_t base = DEC);
  void writeNode(const char* tag, const int16_t   value, const uint8_t base = DEC);
  void writeNode(const char* tag, const int32_t   value, const uint8_t base = DEC);
  void writeNode(const char* tag, const int       value, const int base = DEC);
  void writeNode(const char* tag, const bool      value);
  void writeNode(const char* tag, const float     value, const uint8_t decimals = 2);
  void writeNode(const char* tag, const double    value, const uint8_t decimals = 2);



#ifdef XMLWRITER_ESCAPE_SUPPORT
  //  expands the special XML chars
  void escape(const char* str);
#endif


  //  One need to call flush() at the end of writing to empty the internal buffer.
  //  Note: this is overridden of the Print interface
  void  flush();


  //  metrics
  uint8_t  bufferIndex()  { return _bufferIndex; };
  uint32_t bytesWritten() { return _bytesOut; };


private:
  //  output stream, Print Class
  Print*   _stream;
  size_t   write(uint8_t c);

  //  for indentation
  uint8_t  _indent;
  uint8_t  _indentStep;

  //  configuration
  uint8_t  _config;

  //  stack - used to remember the current tagname to create
  //  automatic the right close tag.
  uint8_t  _tagIndex;
  char     _tagStack[XMLWRITER_MAXLEVEL][XMLWRITER_MAXTAGSIZE + 1];

  //  output admin
  char *   _buffer;
  uint8_t  _bufferSize;
  uint8_t  _bufferIndex;
  uint32_t _bytesOut;
};


//  -- END OF FILE --

