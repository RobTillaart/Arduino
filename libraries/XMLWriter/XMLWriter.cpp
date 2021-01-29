//
//    FILE: XMLWriter.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2013-11-06
// PURPOSE: Arduino library for creating XML 
//
//  HISTORY:
//  0.1.00 2013-11-06  initial version
//  0.1.01 2013-11-07  rework interfaces
//  0.1.02 2013-11-07  +setIndentSize(), corrected history, +escape support
//  0.1.03 2015-03-07  refactored - footprint + interface
//  0.1.04 2015-05-21  refactored - reduce RAM -> used F() macro etc.
//  0.1.05 2015-05-23  added XMLWRITER_MAXTAGSIZE 15 (to support KML coordinates tag)
//  0.1.6  2016-03-16  added incrIndent(), decrIndent(), indent(), raw();
//  0.1.7  2017-07-26  added const where possible
//  0.1.8  2017-12-09  fix casting issue #83 (long -> int32_t);
//  0.1.9  2017-12-09  add PROGMEM support for escape() strings
//  0.2.0  2020-04-24  refactor, added examples, #pragma, print as base class
//  0.2.1  2020-04-26  performance optimized, setconfig() + newLine() added
//  0.2.2  2020-04-29  dynamic buffer size in constructor
//  0.2.3  2020-06-19  fix library.json
//  0.2.4  2020-07-07  fix #6 Print interface made public
//  0.3.0  2021-01-09  arduino-ci + unit tests
//                     add getIndentSize(); version(); debug();


#include "XMLWriter.h"


XMLWriter::XMLWriter(Print* stream, uint8_t bufsize)
{
  _bufsize = constrain(bufsize, 2, 250);
  _buffer = (char *) malloc(_bufsize);
  _stream = stream;
  reset();
}


XMLWriter::~XMLWriter()
{
  if (_buffer != NULL) free(_buffer);
}


void XMLWriter::reset()
{
  _indent     = 0;
  _indentStep = 2;
  _tidx       = 0;
  _bidx       = 0;
  _config     = XMLWRITER_COMMENT | XMLWRITER_INDENT | XMLWRITER_NEWLINE;
  _bytesOut   = 0;
}


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
  println(_bufsize);
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
  if (_tidx > XMLWRITER_MAXLEVEL)
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
  strcpy(_tagStack[_tidx++], tag);
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
  print(_tagStack[--_tidx]);
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
// TAGFIELD
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
  // F() is slower & uses less RAM but 15 bytes saved
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
// WRITENODE
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
  // F() is slower & uses less RAM but saves 9 bytes
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
    // as indentation is a multiple of 2 
    // this is nice balance between speed and RAM.
    for (uint8_t i = _indent; i > 0; i-= 2) print("  ");
  }
}

size_t XMLWriter::write(uint8_t c)
{
  _buffer[_bidx++] = c;
  if (_bidx == (_bufsize - 1)) flush();
  return 1;
};

void XMLWriter::flush()
{
  _bytesOut += _bidx;
  if (_bidx > 0)
  {
    _buffer[_bidx] = 0;
    _stream->print(_buffer);
    _bidx = 0;
  }
};


////////////////////////////////////////////////////////////////////
//
// ESCAPE
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
// NOTE: & and ; are handled in code.     // 25 bytes RAM
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
        print(expanded[q - c]); // uint8_t idx = q-c;
        print(';');
    }
#endif
    p++;
  }
}
#endif


// -- END OF FILE --
