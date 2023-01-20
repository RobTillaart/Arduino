//
//    FILE: I2C_bus_counter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: I2C bus counter
//    DATE: 2021-11-10
//     URL: https://github.com/RobTillaart/MultiSpeedI2CScanner
//     URL: http://forum.arduino.cc/index.php?topic=197360


#include <Arduino.h>
#include <Wire.h>

const char version[] = "0.1.0";

int wirePortCount = 1;


///////////////////////////////////////////////////
//
// MAIN CODE
//
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print(__FILE__);
  Serial.print("\t");
  Serial.println(version);
  delay(1000);

#if defined WIRE_IMPLEMENT_WIRE1 || WIRE_INTERFACES_COUNT > 1
  Wire1.begin();
  wirePortCount++;
#endif
#if defined WIRE_IMPLEMENT_WIRE2 || WIRE_INTERFACES_COUNT > 2
  Wire2.begin();
  wirePortCount++;
#endif
#if defined WIRE_IMPLEMENT_WIRE3 || WIRE_INTERFACES_COUNT > 3
  Wire3.begin();
  wirePortCount++;
#endif
#if defined WIRE_IMPLEMENT_WIRE4 || WIRE_INTERFACES_COUNT > 4
  Wire4.begin();
  wirePortCount++;
#endif
#if defined WIRE_IMPLEMENT_WIRE5 || WIRE_INTERFACES_COUNT > 5
  Wire5.begin();
  wirePortCount++;
#endif

  Serial.print("I2C bus count: ");
  Serial.println(wirePortCount);
}


void loop()
{
}


// -- END OF FILE --
