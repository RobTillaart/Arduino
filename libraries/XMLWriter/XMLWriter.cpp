//
//    FILE: XMLWriter.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.5
//    DATE: 2013-11-06
// PURPOSE: Arduino library for creating XML


#include "XMLWriter.h"


XMLWriter::XMLWriter(Print* stream, uint8_t bufferSize)
{
  _bufferSize = constrain(bufferSize, 2, 250);
  _buffer = (char *) malloc(_bufferSize);
  _stream = stream;
  reset();
}


XMLWriter::~XMLWriter()
{
  if (_buffer != NULL) free(_buffer);
}


void XMLWriter::reset()
{
  _indent      = 0;
  _indentStep  = 2;
  _tagIndex    = 0;
  _bufferIndex = 0;
  _config      = XMLWRITER_COMMENT | XMLWRITER_INDENT | XMLWRITER_NEWLINE;
  _bytesOut    = 0;
}


void XMLWriter::setConfig(uint8_t config)
{
  _config = config;
};


void XMLWriter::header()
{
  print(F("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"));
}


void XMLWriter::version()
{
  print(F("<!-- "));
  print(F(" XMLWRITER_VERSION: "));
  print(XMLWRITER_VERSION);
  print(F(" -->\n"));
}


void XMLWriter::debug()
{
  print(F("<!-- "));
  print('\n');
  print(F(" VERSION: "));
  println(XMLWRITER_VERSION);
  print(F("MAXLEVEL: "));
  println(XMLWRITER_MAXLEVEL);
  print(F(" TAGSIZE: "));
  println(XMLWRITER_MAXTAGSIZE);
  print(F("  CONFIG: "));
  println(_config, HEX);
  print(F("  INDENT: "));
  println(_indent);
  print(F(" BUFSIZE: "));
  println(_bufferSize);
  print(F(" -->\n"));
}


void XMLWriter::comment(const char* text, const bool multiLine)
{
  if (_config & XMLWRITER_COMMENT)
  {
    print('\n');
    if (!multiLine) indent();
    print(F("<!-- "));
    if (multiLine) print('\n');
    print(text);
    if (multiLine) print('\n');
    print(F(" -->\n"));
  }
}


void XMLWriter::newLine(uint8_t n)
{
  if (_config & XMLWRITER_NEWLINE)
  {
    while(n--) print('\n');
  }
}


void XMLWriter::tagOpen(const char* tag, const bool newline)
{
  tagOpen(tag, "", newline);
}


void XMLWriter::tagOpen(const char* tag, const char* name, const bool newline)
{
  if (_tagIndex > XMLWRITER_MAXLEVEL)
  {
    comment("MAXLEVEL exceeded.");
    comment(tag);
    comment(name);
    flush();
    return;
  }
  if (strlen(tag) > XMLWRITER_MAXTAGSIZE)
  {
     comment("MAXTAGSIZE exceeded.");
     comment(tag);
     flush();
     return;
  }
  strcpy(_tagStack[_tagIndex++], tag);
  tagStart(tag);
  if (name[0] != 0) tagField("name", name);
  tagEnd(newline, NOSLASH);
  _indent += _indentStep;
}


void XMLWriter::tagClose(const bool ind)
{
  _indent -= _indentStep;
  if (ind) indent();
  print("</");
  print(_tagStack[--_tagIndex]);
  print(">\n");
}


void XMLWriter::tagStart(const char *tag)
{
  indent();
  print('<');
  print(tag);
}


void XMLWriter::tagField(const char *field, const char* str)
{
  print(' ');
  print(field);
  print("=\"");
#ifdef XMLWRITER_ESCAPE_SUPPORT
  escape(str);
#else
  print(str);
#endif
  print('"');
}


void XMLWriter::tagEnd(const bool newline, const bool addSlash)
{
  if (addSlash) print("/>");
  else print('>');
  if (newline) print('\n');
}


void XMLWriter::writeNode(const char* tag, const char* str)
{
  tagOpen(tag, "", NONEWLINE);
#ifdef XMLWRITER_ESCAPE_SUPPORT
  escape(str);
#else
  print(str);
#endif
  tagClose(NOINDENT);
}


///////////////////////////////////////////////////////////////
//
//  TAGFIELD
//
void XMLWriter::tagField(const char *field, const uint8_t value, const uint8_t base)
{
  tagField(field, (uint32_t) value, base);
}


void XMLWriter::tagField(const char *field, const uint16_t value, const uint8_t base)
{
  tagField(field, (uint32_t) value, base);
}


void XMLWriter::tagField(const char *field, const uint32_t value, const uint8_t base)
{
  print(' ');
  print(field);
  print("=\"");
  print(value, base);
  print('"');
}


void XMLWriter::tagField(const char *field, const int8_t value, const uint8_t base)
{
  tagField(field, (int32_t) value, base);
}


void XMLWriter::tagField(const char *field, const int16_t value, const uint8_t base)
{
  tagField(field, (int32_t) value, base);
}


void XMLWriter::tagField(const char *field, const int value, const int base)
{
  tagField(field, (int32_t) value, (uint8_t) base);
}


void XMLWriter::tagField(const char *field, const int32_t value, const uint8_t base)
{
  print(' ');
  print(field);
  print("=\"");
  print(value, base);
  print('"');
}


void XMLWriter::tagField(const char *field, const bool value)
{
  print(' ');
  print(field);
  //  F() is slower & uses less RAM but 15 bytes saved
  print(value ? F("=\"true\"") : F("=\"false\""));
}


void XMLWriter::tagField(const char *field, const double value, const uint8_t decimals)
{
  print(' ');
  print(field);
  print(F("=\""));
  print(value, decimals);
  print('"');
}


///////////////////////////////////////////////////////////////
//
//  WRITENODE
//
void XMLWriter::writeNode(const char* tag, const uint8_t value, const uint8_t base)
{
  writeNode(tag, (uint32_t) value, base);
}


void XMLWriter::writeNode(const char* tag, const uint16_t value, const uint8_t base)
{
  writeNode(tag, (uint32_t) value, base);
}


void XMLWriter::writeNode(const char* tag, const uint32_t value, const uint8_t base)
{
  tagOpen(tag, "", NONEWLINE);
  print(value, base);
  tagClose(NOINDENT);
}


void XMLWriter::writeNode(const char* tag, const int8_t value, const uint8_t base)
{
  writeNode(tag, (int32_t) value, base);
}


void XMLWriter::writeNode(const char* tag, const int16_t value, const uint8_t base)
{
  writeNode(tag, (int32_t) value, base);
}


void XMLWriter::writeNode(const char* tag, const int value, const int base)
{
  writeNode(tag, (int32_t) value, (uint8_t) base);
}


void XMLWriter::writeNode(const char* tag, const int32_t value, const uint8_t base)
{
  tagOpen(tag, "", NONEWLINE);
  print(value, base);
  tagClose(NOINDENT);
}


void XMLWriter::writeNode(const char* tag, const bool value)
{
  tagOpen(tag, "", NONEWLINE);
  //  F() is slower & uses less RAM but saves 9 bytes
  print(value ? F("true") : F("false"));
  tagClose(NOINDENT);
}


void XMLWriter::writeNode(const char* tag, const double value, const uint8_t decimals)
{
  tagOpen(tag, "", NONEWLINE);
  print(value, decimals);
  tagClose(NOINDENT);
}


void XMLWriter::indent()
{
  if (_config & XMLWRITER_INDENT)
  {
    //  as indentation is a multiple of 2
    //  this is nice balance between speed and RAM.
    for (uint8_t i = _indent; i > 0; i-= 2) print("  ");
  }
}


size_t XMLWriter::write(uint8_t c)
{
  _buffer[_bufferIndex++] = c;
  if (_bufferIndex == (_bufferSize - 1)) flush();
  return 1;
};


void XMLWriter::flush()
{
  _bytesOut += _bufferIndex;
  if (_bufferIndex > 0)
  {
    _buffer[_bufferIndex] = 0;
    _stream->write(_buffer, _bufferIndex);  //  saves ~40 bytes on UNO.
    //  _stream->print(_buffer);
    _bufferIndex = 0;
  }
};


////////////////////////////////////////////////////////////////////
//
//  ESCAPE
//

#ifdef XMLWRITER_ESCAPE_SUPPORT
static char c[6] = "\"\'<>&";

#ifdef __PROGMEM__
PROGMEM const char quote[] = "&quot;";
PROGMEM const char apostrophe[] = "&apos;";
PROGMEM const char lessthen[] = "&lt;";
PROGMEM const char greaterthen[] = "&gt;";
PROGMEM const char ampersand[] = "&amp;";

PROGMEM const char* const expanded[] =
{
  quote, apostrophe, lessthen, greaterthen, ampersand
};

#else
//  NOTE: & and ; are handled in code.     //  25 bytes RAM
static char expanded[][5] = { "quot", "apos","lt","gt","amp"};

#endif

void XMLWriter::escape(const char* str)
{
  char* p = (char *)str;
  while (*p != 0)
  {
    char* q = strchr(c, *p);
    if (q == NULL) print(*p);
#ifdef __PROGMEM__
    else
    {
      char buf[8];
      strcpy_P(buf, (char*)pgm_read_word(&(expanded[q - c])));
      print(buf);
    }
#else
    else
    {
        print('&');
        print(expanded[q - c]);  //  uint8_t idx = q-c;
        print(';');
    }
#endif
    p++;
  }
}
#endif


//  -- END OF FILE --

