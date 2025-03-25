//
//    FILE: PCA9671_Wire1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PCA9671


#include "PCA9671.h"

//  adjust addresses if needed
PCA9671 PCA(0x20, &Wire1);  //  or Wire2 if supported


void doHigh()
{
  PCA.write(4, HIGH);
  int x = PCA.read16();
  Serial.print("Read ");
  Serial.println(x, HEX);
}


void doLow()
{
  PCA.write(4, LOW);
  int x = PCA.read16();
  Serial.print("Read ");
  Serial.println(x, HEX);
}


void doToggle()
{
  PCA.toggle(4);
  int x = PCA.read16();
  Serial.print("Read ");
  Serial.println(x, HEX);
}


void setup()
{
  //  while(!Serial);  //  uncomment when needed
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9671_LIB_VERSION:\t");
  Serial.println(PCA9671_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (!PCA.begin())
  {
    Serial.println("could not initialize...");
  }
  if (!PCA.isConnected())
  {
    Serial.println("=> not connected");
    while(1);
  }

  int x = PCA.read16();
  Serial.print("Read ");
  Serial.println(x, HEX);
  delay(1000);
}


void loop()
{
  Serial.println("HLT");
  while (Serial.available() == 0);
  switch (Serial.read())
  {
    case 'H': doHigh(); break;
    case 'L': doLow(); break;
    case 'T': doToggle(); break;
  }
}


//  -- END OF FILE --

