//
//    FILE: MCP23S08_digitalRead.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-12-30
// PUPROSE: test MCP23017 library


#include "MCP23S08.h"
#include "SPI.h"


MCP23S08 MCP(10);
int rv = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("MCP23S08_test version: ");
  Serial.println(MCP23S08_LIB_VERSION);
  delay(100);

  SPI.begin();
  rv = MCP.begin();
  Serial.println(rv);

  rv = MCP.pinMode8(0xFF);   // CHECK
  Serial.println(rv);


  Serial.print("HWSPI: ");
  Serial.println(MCP.usesHWSPI());

  Serial.println("TEST digitalRead(pin)");
  for (int pin = 0; pin < 8; pin++)
  {
    int val = MCP.digitalRead(pin);
    Serial.print(val);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();
}


void loop()
{
  delay(1000);
  Serial.println("TEST digitalRead(pin)");
  for (int pin = 0; pin < 8; pin++)
  {
    int val = MCP.digitalRead(pin);
    Serial.print(val);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();

}


// -- END OF FILE --
