//
//    FILE: oneWireSearch.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: scan for 1-Wire devices + code snippet generator
//    DATE: 2015-june-30
//     URL: http://forum.arduino.cc/index.php?topic=333923
//
// inspired by http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html
//
// Released to the public domain
//
// 0.1.00 initial version
// 0.1.01 first published version
// 0.1.02 small output changes

#include <OneWire.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("//\n// Start oneWireSearch.ino \n//");

  for (uint8_t pin = 2; pin < 13; pin++)
  {
    findDevices(pin);
  }
  Serial.println("\n//\n// End oneWireSearch.ino \n//");
}

void loop()
{
}

uint8_t findDevices(int pin)
{
  OneWire ow(pin);

  uint8_t address[8];
  uint8_t count = 0;


  if (ow.search(address))
  {
    Serial.print("\nuint8_t pin");
    Serial.print(pin, DEC);
    Serial.println("[][8] = {");
    do {
      count++;
      Serial.println("  {");
      for (uint8_t i = 0; i < 8; i++)
      {
        Serial.print("0x");
        if (address[i] < 0x10) Serial.print("0");
        Serial.print(address[i], HEX);
        if (i < 7) Serial.print(", ");
      }
      Serial.println("  },");
    } while (ow.search(address));

    Serial.println("};");
    Serial.print("// nr devices found: ");
    Serial.println(count);
  }

  return count;
}
