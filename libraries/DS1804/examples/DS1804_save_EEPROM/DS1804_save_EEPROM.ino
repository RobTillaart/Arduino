//    FILE: DS1804_save_EEPROM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: helper to set start up value
//     URL: https://github.com/RobTillaart/DS1804

#include "DS1804.h"

//  adjust pins if needed
const uint8_t CSPIN = 5;
const uint8_t INCPIN = 6;
const uint8_t UDPIN = 7;

DS1804 ds(CSPIN, INCPIN, UDPIN);

int value = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS1804_LIB_VERSION: ");
  Serial.println(DS1804_LIB_VERSION);
  Serial.println();

  ds.begin();
  delay(1000);
  ds.select(true);
  //  be sure to set it to zero
  ds.moveDown(100);

  Serial.println("COMMANDS");
  Serial.println("========");
  Serial.println("Z = ZERO");
  Serial.println("U = UP");
  Serial.println("D = DOWN");
  Serial.println("S = SAVE");
}


void loop()
{
  if (Serial.available())
  {
    int c = Serial.read();
    if (c == 'Z')
    {
      ds.moveDown(100);
      value = 0;
      Serial.println(value);
    }
    if (c == 'D')
    {
      ds.moveDown();
      value--;
      if (value < 0) value = 0;
      Serial.println(value);
    }
    if (c == 'U')
    {
      ds.moveUp();
      value++;
      if (value > 100) value = 100;
      Serial.println(value);
    }
    if (c == 'S')
    {
      ds.saveEEPROM();
      Serial.println("SAVED");
    }

  }
}


//  -- END OF FILE --
