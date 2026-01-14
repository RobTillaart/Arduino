//
//    FILE: PCA9671_blink.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9671 library
//     URL: https://github.com/RobTillaart/PCA9671


#include "PCA9671.h"

PCA9671 PCA(0x20);


void doHigh()
{
  PCA.write(4, HIGH);
  int x = PCA.read16();
  Serial.print("Read ");
  printHex(x);
}


void doLow()
{
  PCA.write(4, LOW);
  int x = PCA.read16();
  Serial.print("Read ");
  printHex(x);
}


void doToggle()
{
  PCA.toggle(4);
  int x = PCA.read16();
  Serial.print("Read ");
  printHex(x);
}


void printHex(uint16_t x)
{
  if (x < 0x1000) Serial.print('0');
  if (x < 0x100)  Serial.print('0');
  if (x < 0x10)   Serial.print('0');
  Serial.println(x, HEX);
}



void setup()
{
  //  while(!Serial);  //  uncomment when needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PCA9671_LIB_VERSION:\t");
  Serial.println(PCA9671_LIB_VERSION);
  Serial.println();

  Wire.begin();
  delay(1000);
  PCA.begin();
}


void loop()
{
  PCA.write16(0xFFFF);
  Serial.println("HIGH");
  delay(1000);

  PCA.write16(0x0000);
  Serial.println("LOW");
  delay(1000);
}


//  -- END OF FILE --
