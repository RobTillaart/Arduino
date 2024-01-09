//
//    FILE: FRAM_multilanguage_elements.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: multilanguage in FRAM.
//     URL: https://github.com/RobTillaart/FRAM_I2C
//
//
//  experimental code - NO OPERATIONAL CODE.


#include "FRAM.h"
#include "FRAM_MULTILANGUAGE.h"
#include "elements_name.h"


FRAM fram;
FRAM_ML FML;


uint32_t sizeInBytes = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FRAM_LIB_VERSION: ");
  Serial.println(FRAM_LIB_VERSION);

  Wire.begin();

  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.print("INIT ERROR: ");
    Serial.println(rv);
  }

  sizeInBytes = fram.getSizeBytes();
  Serial.print("FRAM SIZE:\t");
  Serial.println(sizeInBytes);
  Serial.println();

  //  configuration.
  uint32_t next = FML.begin(&fram, 0x2000, 1, 120, 15);
  //  uint32_t next = FML.begin(&fram, 0x2000);
  Serial.print("START:\t0x2000\n");
  Serial.print("NEXT:\t0x");
  Serial.println(next, HEX);
  Serial.print("SIZE:\t0x");
  Serial.println(next - 0x2000, HEX);
  Serial.print("LANG:\t");
  Serial.println(FML.getMaxLanguage());
  Serial.print("STRING:\t");
  Serial.println(FML.getMaxStrings());
  Serial.print("LENGTH:\t");
  Serial.println(FML.getMaxLength());
  Serial.println();

  //  fill in the names of the elements
  FML.setLanguageName(0, "EN");
  FML.setLanguage(0);
  for (int e = 0; e < 73; e++)
  {
    FML.setText(3, elements_name[e]);
  }

  //  print the table.
  Serial.println();
  for (int e = 0;  e < 73; e++)
  {
    char buffer[20];
    Serial.print(e + 1);
    Serial.print("\t");
    FML.getText(e, buffer);
    Serial.print(buffer);
    Serial.println();
  }

  Serial.println();
  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
