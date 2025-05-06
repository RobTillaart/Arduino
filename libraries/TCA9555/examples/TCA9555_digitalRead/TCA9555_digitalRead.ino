//
//    FILE: TCA9555_digitalRead.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test TCA9555 library
//     URL: https://github.com/RobTillaart/TCA9555


#include "TCA9555.h"

//  adjust address if needed
TCA9555 TCA(0x20);

int val = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9555_LIB_VERSION: ");
  Serial.println(TCA9555_LIB_VERSION);
  Serial.println();

  Wire.begin();
  TCA.begin();


  Serial.println("Set pinMode16 INPUT");
  TCA.pinMode16(0xFFFF);

  Serial.println("Normal polarity");
  TCA.setPolarity16(0x0000);


  Serial.println("TEST read1(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    val = TCA.read1(pin);
    Serial.print(val);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();


  Serial.println("TEST read8(port)");
  for (int port = 0; port < 2; port++)
  {
    val = TCA.read8(port);
    Serial.print(val, HEX);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();


  Serial.println("TEST read16()");
  val = TCA.read16();
  Serial.print(val, HEX);
  Serial.println();
  Serial.println();
  Serial.println();

//////////////////////////////////////////////

  Serial.println("Inverted polarity");
  TCA.setPolarity16(0xFFFF);


  Serial.println("TEST read1(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    val = TCA.read1(pin);
    Serial.print(val);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();


  Serial.println("TEST read8(port)");
  for (int port = 0; port < 2; port++)
  {
    val = TCA.read8(port);
    Serial.print(val, HEX);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();


  Serial.println("TEST read16()");
  val = TCA.read16();
  Serial.print(val, HEX);
  Serial.println();
  Serial.println("\ndone...");

}


void loop()
{
}


//  -- END OF FILE --
