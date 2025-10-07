//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-08-28
// PURPOSE: unit tests for the AS7331 library
//     URL: https://github.com/RobTillaart/AS7331
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "AS7331.h"


unittest_setup()
{
  fprintf(stderr, "AS7331_LIB_VERSION: %s\n", (char *) AS7331_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants_address)
{
  assertEqual(0x74, AS7331_DEFAULT_ADDRESS);
}

unittest(test_constants_errors)
{
  assertEqual(0x00, AS7331_OK           );
  assertEqual(0x01, AS7331_CRC_ERROR    );
  assertEqual(0x10, AS7331_NOT_READY    );
  assertEqual(0x11, AS7331_REQUEST_ERROR);
}

unittest(test_constants_mode)
{
  assertEqual(0x00, AS7331_MODE_CONTINUOUS);
  assertEqual(0x01, AS7331_MODE_MANUAL    );
  assertEqual(0x02, AS7331_MODE_SYNS      );
  assertEqual(0x03, AS7331_MODE_SYND      );
}

unittest(test_constants_gain)
{
  assertEqual(0x0B, AS7331_GAIN_1x   );
  assertEqual(0x0A, AS7331_GAIN_2x   );
  assertEqual(0x09, AS7331_GAIN_4x   );
  assertEqual(0x08, AS7331_GAIN_8x   );
  assertEqual(0x07, AS7331_GAIN_16x  );
  assertEqual(0x06, AS7331_GAIN_32x  );
  assertEqual(0x05, AS7331_GAIN_64x  );
  assertEqual(0x04, AS7331_GAIN_128x );
  assertEqual(0x03, AS7331_GAIN_256x );
  assertEqual(0x02, AS7331_GAIN_512x );
  assertEqual(0x01, AS7331_GAIN_1024x);
  assertEqual(0x00, AS7331_GAIN_2048x);

}

unittest(test_constants_conversion)
{
  assertEqual(0x00, AS7331_CONV_001  );
  assertEqual(0x01, AS7331_CONV_002  );
  assertEqual(0x02, AS7331_CONV_004  );
  assertEqual(0x03, AS7331_CONV_008  );
  assertEqual(0x04, AS7331_CONV_016  );
  assertEqual(0x05, AS7331_CONV_032  );
  assertEqual(0x06, AS7331_CONV_064  );
  assertEqual(0x07, AS7331_CONV_128  );
  assertEqual(0x08, AS7331_CONV_256  );
  assertEqual(0x09, AS7331_CONV_512  );
  assertEqual(0x0A, AS7331_CONV_1024 );
  assertEqual(0x0B, AS7331_CONV_2048 );
  assertEqual(0x0C, AS7331_CONV_4096 );
  assertEqual(0x0D, AS7331_CONV_8192 );
  assertEqual(0x0E, AS7331_CONV_16384);
  assertEqual(0x0F, AS7331_CONV_001xx);
}

unittest(test_constants_clockFreq)
{
  assertEqual(0x00, AS7331_CCLK_1024);
  assertEqual(0x01, AS7331_CCLK_2048);
  assertEqual(0x02, AS7331_CCLK_4096);
  assertEqual(0x03, AS7331_CCLK_8192);
}

unittest(test_constants_status)
{
  assertEqual(0x8000, AS7331_STATUS_OUTCONVOF   );
  assertEqual(0x4000, AS7331_STATUS_MRESOF      );
  assertEqual(0x2000, AS7331_STATUS_ADCOF       );
  assertEqual(0x1000, AS7331_STATUS_LDATA       );
  assertEqual(0x0800, AS7331_STATUS_NDATA       );
  assertEqual(0x0400, AS7331_STATUS_NOTREADY    );
  assertEqual(0x0200, AS7331_STATUS_STANDBYSTATE);
  assertEqual(0x0100, AS7331_STATUS_POWERSTATE  );
}


unittest(test_constructor_ok)
{
  AS7331 UV(0x74);
  //  address OK
  assertEqual(0x74, UV.getAddress());
}

//  Need mock up to test.

unittest_main()


//  -- END OF FILE --

