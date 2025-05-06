//
//    FILE: TCA9555_digitalWrite.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test TCA9555 library
//     URL: https://github.com/RobTillaart/TCA9555


#include "TCA9555.h"

//  adjust address if needed
TCA9555 TCA(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9555_LIB_VERSION: ");
  Serial.println(TCA9555_LIB_VERSION);
  Serial.println();

  Wire.begin();
  TCA.begin();
  delay(1000);

  Wire.setClock(100000);


  Serial.println("Set pinMode1 OUTPUT");
  for (int i = 0; i < 16; i++)
  {
    TCA.pinMode1(i, OUTPUT);
    TCA.write1(i, HIGH);
    delay(100);
    TCA.write1(i, LOW);
  }


  Serial.println("TEST write1(0)");
  for (int i = 0; i < 16; i++)
  {
    TCA.write1(0, i % 2);  //  alternating HIGH/LOW
    Serial.print(i % 2);
    Serial.print('\t');
    delay(250);
  }
  delay(2000);
  Serial.println();
  Serial.println();


  Serial.println("TEST write1(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    TCA.write1(pin, (pin + 1) % 2); //  alternating HIGH/LOW
    Serial.print((pin + 1) % 2);
    Serial.print('\t');
    delay(250);
  }
  delay(2000);
  Serial.println();
  Serial.println();


  Serial.println("TEST write1(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    TCA.write1(pin, pin % 2);  //  alternating HIGH/LOW
    Serial.print(pin % 2);
    Serial.print('\t');
    delay(250);
  }
  delay(2000);
  Serial.println();
  Serial.println();


  Serial.println("TEST read back");
  for (int pin = 0; pin < 16; pin++)
  {
    int val = TCA.read1(pin);
    Serial.print(val);
    Serial.print('\t');
    delay(250);
  }
  Serial.println();
  Serial.println("\ndone...");

  TCA.write8(0, 0x00);
  TCA.write8(1, 0xFF);
  TCA.write1(8, LOW);
}


void loop()
{
}


//  -- END OF FILE --
