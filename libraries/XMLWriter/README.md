# XMLWriter

Arduino Library to create simple XML (messages, files, print, ...)

## Description

The XMLWriter class supports generating XML files and send these over a stream
like Ethernet SD.File or Serial.

When instantiating an XMLWriter one can define the internal buffer size.
This buffering makes the output faster, especially for Ethernet and SD.File.
The buffer size should be at least 2 bytes.
A bigger buffer is often faster but it also depends on the properties of the
stream to see real performance gains.
E.g. the baudrate and internal buffer of Serial, packet behaviour of Ethernet,
or paging of SD cards.
So if performance is an issue one should do some testruns with different sizes
for the buffer and choose one that is appropriate.

Indicative sizes based upon the examples.
Run your tests to find your application optimum.

| STREAM   |    SIZE    |
|:------------|:----------|
| Ethernet | 20-30 |
| Serial   |  5 |
| SD File  |  10-16 |

Important to know when usinig buffering is that your code should always include
a call to **XML.flush()** at the end of the XML generation to flush the buffer.

## Operation

See examples

