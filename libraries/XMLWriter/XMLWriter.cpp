//
//    FILE: XMLWriter.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
//    DATE: 2013-11-06
// PURPOSE: Simple XML library
//
// HISTORY:
// 0.1.00 - 2011-01-21 initial version//
// Released to the public domain
//

#include <XMLWriter.h>

XMLWriter::XMLWriter(Print* stream)
{
    _stream = stream;
    _indent = 0;
    _idx = 0;
}

void XMLWriter::header()
{
    _stream->println("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
}

void XMLWriter::comment(char* text, bool oneLiner)
{
    _stream->println();
    if (oneLiner)
    {
        spaces();
        _stream->print("<!-- ");
        _stream->print(text);
        _stream->println(" -->");
    }
    else
    {
        _stream->println("<!-- ");
        _stream->println(text);
        _stream->println(" -->");
    }
}

void XMLWriter::tagOpen(char* tag, bool oneLiner)
{
    tagOpen(tag, "", oneLiner);
}

void XMLWriter::tagOpen(char* tag, char* name, bool oneLiner)
{
    strncpy(tagnames[_idx++], tag, 10);
    spaces();
    tagStart(tag);
    if (name[0] != 0) tagField("name", name);
    tagEnd();
    if (oneLiner) _stream->println();
    _indent += 2;
}

void XMLWriter::tagClose(bool indent)
{
    _indent -= 2;
    if (indent) spaces();
    _stream->print("</");
    _stream->print(tagnames[--_idx]);
    _stream->println(">");
}

void XMLWriter::writeNode(char* tag, char* value)
{
    tagOpen(tag, "", false);
    _stream->print(value);
    tagClose(false);
}

////////////////////////////////////////////////////////////////////

void XMLWriter::tagStart(char *tag)
{
    _stream->write('<');
    _stream->print(tag);
}

inline void XMLWriter::tagField(char *field, char* value)
{
    _stream->write(' ');
    _stream->print(field);
    _stream->print("=\"");
    _stream->print(value);
    _stream->print("\"");
}

inline void XMLWriter::tagEnd()
{
    _stream->write('>');
}

void XMLWriter::spaces()
{
    for (uint8_t i=0; i< _indent; i++) _stream->write(' ');
}

// END OF FILE