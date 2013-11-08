//
//    FILE: XMLWriter.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
//    DATE: 2013-11-06
// PURPOSE: Simple XML library
//
// HISTORY:
// 0.1.00 - 2013-11-06 initial version
// 0.1.01 - 2013-11-07 rework interfaces
// 0.1.02 - 2013-11-07 +setIndentSize(), corrected history, +escape support
//
// Released to the public domain
//

#include <XMLWriter.h>

XMLWriter::XMLWriter(Print* stream)
{
    _stream = stream;
    reset();
}

void XMLWriter::reset()
{
    _indent = 0;
    _indentStep = 2;
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
    strncpy(tagNames[_idx++], tag, 10);
    tagStart(tag);
    if (name[0] != 0) tagField("name", name);
    tagEnd(newline, NOSLASH);
    _indent += _indentStep;
}

void XMLWriter::tagClose(bool indent)
{
    _indent -= _indentStep;
    if (indent) spaces();
    _stream->print("</");
    _stream->print(tagNames[--_idx]);
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
#ifdef XMLWRITER_ESCAPE_SUPPORT
    escape(value);
#else
    _stream->print(value);
#endif
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
    tagOpen(tag, "", NONEWLINE);
#ifdef XMLWRITER_ESCAPE_SUPPORT
    escape(value);
#else
    _stream->print(value);
#endif
    tagClose(NOINDENT);
}

void XMLWriter::setIndentSize(uint8_t size)
{
    _indentStep = size;
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
    tagOpen(tag, "", NONEWLINE);  // one line
    _stream->print(value);
    tagClose(NOINDENT);
}

void XMLWriter::writeNode(char* tag, long value)
{
    tagOpen(tag, "", NONEWLINE);
    _stream->print(value);
    tagClose(NOINDENT);
}

void XMLWriter::writeNode(char* tag, double value, uint8_t decimals)
{
    tagOpen(tag, "", NONEWLINE);
    _stream->print(value, decimals);
    tagClose(NOINDENT);
}
#endif

////////////////////////////////////////////////////////////////////

void XMLWriter::spaces()
{
    for (uint8_t i=_indent; i>0; i--) _stream->write(' ');
}

#ifdef XMLWRITER_ESCAPE_SUPPORT
char c[6] = "\"\'<>&"; 
char expanded[][7] = { "&quot;", "&apos;","&lt;","&gt;","&amp;"}; // todo in flash

void XMLWriter::escape(char* str)
{
    char* p = str;
    while(*p != 0)
    {
        char* q = strchr(c, *p);
        if (q == NULL) _stream->write(*p);
        else _stream->print(expanded[q - c]); // uint8_t idx = q-c;
        p++;
    }
}
#endif

// END OF FILE