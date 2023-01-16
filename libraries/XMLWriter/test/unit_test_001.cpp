//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-09
// PURPOSE: unit tests for the XMLWriter library
//          https://github.com/RobTillaart/XMLWriter
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)

#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "XMLWriter.h"


unittest_setup()
{
  fprintf(stderr, "XMLWRITER_VERSION: %s\n", (char *) XMLWRITER_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertFalse(NOMULTILINE);
  assertTrue(MULTILINE);

  assertTrue(NEWLINE);
  assertFalse(NONEWLINE);
  assertFalse(NOINDENT);
  
  assertTrue(SLASH);
  assertFalse(NOSLASH);

  assertEqual( 5, XMLWRITER_MAXLEVEL);
  assertEqual(15, XMLWRITER_MAXTAGSIZE);

  assertEqual(0x00, XMLWRITER_NONE   );
  assertEqual(0x01, XMLWRITER_COMMENT);
  assertEqual(0x02, XMLWRITER_INDENT );
  assertEqual(0x04, XMLWRITER_NEWLINE);
}


unittest(test_constructor)
{
  XMLWriter XML(&Serial);
  assertEqual(0, XML.bytesWritten());
  assertEqual(2, XML.getIndentSize());

  //  OK it is a debug function but should work
  assertEqual(0, XML.bufferIndex());
}


unittest(test_header_flush)
{
  XMLWriter XML(&Serial);

  XML.header();
  assertEqual(36, XML.bytesWritten());
  assertEqual(3, XML.bufferIndex());
  
  XML.flush();
  assertEqual(39, XML.bytesWritten());
  assertEqual(0, XML.bufferIndex());
  
  XML.reset();
  assertEqual(0, XML.bytesWritten());
  assertEqual(0, XML.bufferIndex());
}


unittest(test_indent)
{
  XMLWriter XML(&Serial);
  assertEqual(0, XML.bytesWritten());
  
  for (uint8_t indent = 0; indent < 10; indent += 2)
  {
    XML.setIndentSize(indent);
    assertEqual(indent, XML.getIndentSize());
  }
  assertEqual(0, XML.bytesWritten());
  
  XML.reset();
  XML.setIndentSize(2);
  XML.indent();
  assertEqual(0, XML.bytesWritten());
  fprintf(stderr, "%d\n", XML.bufferIndex());
  assertEqual(0, XML.bufferIndex());
  
  XML.reset();
  XML.setIndentSize(2);
  XML.incrIndent();
  XML.indent();
  assertEqual(0, XML.bytesWritten());
  fprintf(stderr, "%d\n", XML.bufferIndex());
  assertEqual(2, XML.bufferIndex());
  
  XML.reset();
  XML.setIndentSize(2);
  XML.incrIndent();
  XML.decrIndent();
  XML.indent();
  assertEqual(0, XML.bytesWritten());
  fprintf(stderr, "%d\n", XML.bufferIndex());
  assertEqual(0, XML.bufferIndex());
}


unittest(test_header_comment_version_debug)
{
  XMLWriter XML(&Serial);
  assertEqual(0, XML.bytesWritten());

  XML.header();
  assertEqual(36, XML.bytesWritten());
  XML.comment("This is a demo of\na simple XML lib for Arduino!", true);
  assertEqual(99, XML.bytesWritten());
  XML.version();
  assertEqual(126, XML.bytesWritten());
  XML.debug();
  assertEqual(225, XML.bytesWritten());

  XML.flush();
  assertEqual(229, XML.bytesWritten());
  assertEqual(0, XML.bufferIndex());      //  nothing to flush
}


unittest_main()

//  -- END OF FILE --
