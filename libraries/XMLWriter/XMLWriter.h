#ifndef XML_WRITER_H
#define XML_WRITER_H
//
//    FILE: XMLWriter.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
//    DATE: 2013-11-06
// PURPOSE: Simple XML writer library
//
// Released to the public domain
//

#define XMLWRITER_VERSION "0.1.01"

// deepness of XML tree 5..10
// needed for stack of tagnames
#define XMLWRITER_MAXLEVEL 5

#define XMLWRITER_EXTENDED

#include "Arduino.h"

class XMLWriter
{
public:
    XMLWriter(Print* stream);

    void reset();
    void header();
    void comment(char* text, bool multiLine=false);

    void tagOpen(char* tag, bool newline=true);
    void tagOpen(char* tag, char* name, bool newline=true);
    void tagClose(bool indent=true);

    void tagStart(char* tag);
    void tagField(char* field, char* value);
    void tagEnd(bool newline=true, bool addSlash=true);

    void writeNode(char* tag, char* value);

#ifdef XMLWRITER_EXTENDED
    void tagField(char* field, int value);
    void tagField(char* field, long value);
    void tagField(char* field, double value, uint8_t decimals=2);

    void writeNode(char* tag, int value);
    void writeNode(char* tag, long value);
    void writeNode(char* tag, double value, uint8_t decimals=2);
#endif

private:
    void spaces();

    Print* _stream;
    uint8_t _indent;

    uint8_t _idx;
    char tagnames[XMLWRITER_MAXLEVEL][11];
};

#endif
// END OF FILE