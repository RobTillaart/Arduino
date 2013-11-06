#ifndef XML_WRITER_H
#define XML_WRITER_H
//
//    FILE: XMLWriter.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
//    DATE: 2013-11-06
// PURPOSE: Simple XML writer library
//
// Released to the public domain
//

#define XMLWRITER_VERSION "0.1.00"

// deepness of XML tree 5..10 
// needed for stack of tagnames
#define XMLWRITER_MAXLEVEL 5

#include "Arduino.h"

class XMLWriter
{
public:
    XMLWriter(Print* stream);

    void header();
    void comment(char* text, bool oneLiner=true);
    void tagOpen(char* tag, bool oneLiner=true);
    void tagOpen(char* tag, char* name, bool oneLiner=true);
    void tagClose(bool indent=true);
    void writeNode(char* tag, char* value);
    
private:
    void tagStart(char *tag);
    void tagField(char *field, char* value);
    void tagEnd();

    void spaces();

    Print* _stream;
    uint8_t _indent;
    
    uint8_t _idx;
    char tagnames[XMLWRITER_MAXLEVEL][11];
};

#endif
// END OF FILE