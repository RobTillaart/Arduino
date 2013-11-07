//
//    FILE: XMLWriter.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
//    DATE: 2013-11-06
// PURPOSE: Simple XML library
//
// HISTORY:
// 0.1.00 - 2011-11-06 initial version
// 0.1.01 - 2011-11-07 rework interfaces
//
// Released to the public domain
//

#include <XMLWriter.h>

#define XMLWRITER_INDENT_STEP 2

XMLWriter::XMLWriter(Print* stream)
{
    _stream = stream;
    reset();
}

void XMLWriter::reset()
{
    _indent = 0;
    _idx = 0;
}

void XMLWriter::header()
{
    _stream->println("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
}

void XMLWriter::comment(char* text, bool multiLine)
{
    _stream->println();
    if (multiLine)
    {
        _stream->println("<!-- ");
        _stream->println(text);
        _stream->println(" -->");
    }
    else
    {
        spaces();
        _stream->print("<!-- ");
        _stream->print(text);
        _stream->println(" -->");
    }
}

void XMLWriter::tagOpen(char* tag, bool newline)
{
    tagOpen(tag, "", newline);
}

void XMLWriter::tagOpen(char* tag, char* name, bool newline)
{
    strncpy(tagnames[_idx++], tag, 10);
    tagStart(tag);
    if (name[0] != 0) tagField("name", name);
    tagEnd(newline, false);
    _indent += XMLWRITER_INDENT_STEP;
}

void XMLWriter::tagClose(bool indent)
{
    _indent -= XMLWRITER_INDENT_STEP;
    if (indent) spaces();
    _stream->print("</");
    _stream->print(tagnames[--_idx]);
    _stream->println(">");
}

void XMLWriter::tagStart(char *tag)
{
    spaces();
    _stream->write('<');
    _stream->print(tag);
}

void XMLWriter::tagField(char *field, char* value)
{
    _stream->write(' ');
    _stream->print(field);
    _stream->print("=\"");
    _stream->print(value);
    _stream->print("\"");
}

void XMLWriter::tagEnd(bool newline, bool addSlash)
{
    if (addSlash) _stream->write('/');
    _stream->print('>');
    if (newline) _stream->println();
}

void XMLWriter::writeNode(char* tag, char* value)
{
    tagOpen(tag, "", false);
    _stream->print(value);
    tagClose(false);
}

#ifdef XMLWRITER_EXTENDED
void XMLWriter::tagField(char *field, int value)
{
    _stream->write(' ');
    _stream->print(field);
    _stream->print("=\"");
    _stream->print(value);
    _stream->print("\"");
}

void XMLWriter::tagField(char *field, long value)
{
    _stream->write(' ');
    _stream->print(field);
    _stream->print("=\"");
    _stream->print(value);
    _stream->print("\"");
}

void XMLWriter::tagField(char *field, double value, uint8_t decimals)
{
    _stream->write(' ');
    _stream->print(field);
    _stream->print("=\"");
    _stream->print(value);
    _stream->print("\"");
}

void XMLWriter::writeNode(char* tag, int value)
{
    tagOpen(tag, "", false);  // one line
    _stream->print(value);
    tagClose(false);
}

void XMLWriter::writeNode(char* tag, long value)
{
    tagOpen(tag, "", false);
    _stream->print(value);
    tagClose(false);
}

void XMLWriter::writeNode(char* tag, double value, uint8_t decimals)
{
    tagOpen(tag, "", false);
    _stream->print(value, decimals);
    tagClose(false);
}
#endif

////////////////////////////////////////////////////////////////////

void XMLWriter::spaces()
{
    for (uint8_t i=0; i< _indent; i++) _stream->write(' ');
}

// END OF FILE