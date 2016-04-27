#ifndef XML_WRITER_H
#define XML_WRITER_H
//
//    FILE: XMLWriter.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.06
//    DATE: 2013-11-06
// PURPOSE: Simple XML writer library
//
// Released to the public domain
//

#include "Arduino.h"
// no pre 1.0 support!

#define XMLWRITER_VERSION "0.1.06"

// for comment()
#define NOMULTILINE false
#define MULTILINE   true

// for tagOpen(), tagEnd()
#define NEWLINE     true
#define NONEWLINE   false
#define NOINDENT    false    // for tagClose()

// for tagEnd()
#define SLASH       true
#define NOSLASH     false

// deepness of XML tree 5..10
// needed for stack of tagStack
#define XMLWRITER_MAXLEVEL 5      // adjust for deeper nested structures
#define XMLWRITER_MAXTAGSIZE 15   // adjust for longer fields - !! eats memory !!

// reduce footprint by commenting next line
#define XMLWRITER_ESCAPE_SUPPORT

class XMLWriter
{
public:
    XMLWriter(Print* stream);

    void reset();

    // standard XML header
    void header();

    // if multiline == true it does not indent to allow bigger text blocks
    // <!-- text -->
    void comment(char* text, bool multiLine=false);

    // <tag>
    void tagOpen(char* tag, bool newline=true);
    // <tag name="name">
    void tagOpen(char* tag, char* name, bool newline=true);
    // </tag>
    void tagClose(bool ind=true);

    // <tag
    void tagStart(char* tag);
    // field="value"
    void tagField(char* field, char* value);
    //  />
    void tagEnd(bool newline=true, bool addSlash=true);

    // <tag>value</tag>
    void writeNode(char* tag, char* value);

    // typically 0,2,4; default == 2;
    void setIndentSize(uint8_t size = 2);

    // for manual layout control
    void incrIndent()       { _indent += _indentStep; };
    void decrIndent()       { _indent -= _indentStep; };
    void indent();
    void raw(char * str)    { _stream->print(str); };       // TODO Q:other types?

    void tagField(char* field, uint8_t  value, uint8_t base=DEC);
    void tagField(char* field, uint16_t value, uint8_t base=DEC);
    void tagField(char* field, uint32_t value, uint8_t base=DEC);
    void tagField(char* field, int8_t   value, uint8_t base=DEC);
    void tagField(char* field, int16_t  value, uint8_t base=DEC);
    void tagField(char* field, int32_t  value, uint8_t base=DEC);
    void tagField(char *field, bool     value);
    void tagField(char* field, double   value, uint8_t decimals=2);

    void writeNode(char* tag, uint8_t   value, uint8_t base=DEC);
    void writeNode(char* tag, uint16_t  value, uint8_t base=DEC);
    void writeNode(char* tag, uint32_t  value, uint8_t base=DEC);
    void writeNode(char* tag, int8_t    value, uint8_t base=DEC);
    void writeNode(char* tag, int16_t   value, uint8_t base=DEC);
    void writeNode(char* tag, int32_t   value, uint8_t base=DEC);
    void writeNode(char* tag, bool      value);
    void writeNode(char* tag, double value, uint8_t decimals=2);

#ifdef XMLWRITER_ESCAPE_SUPPORT
    // expands the special xml chars
    void escape(char* str);
#endif

private:
    // outputstream
    Print* _stream;

    // for indentation
    uint8_t _indent;
    uint8_t _indentStep;

    // stack - used to remember the current tagname to create
    // automatic the right close tag.
    uint8_t _idx;
    char tagStack[XMLWRITER_MAXLEVEL][XMLWRITER_MAXTAGSIZE+1];
};

#endif
// END OF FILE