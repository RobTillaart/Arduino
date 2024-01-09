//
//    FILE: FRAM_multilanguage_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: multi language text tablein FRAM. READER
//     URL: https://github.com/RobTillaart/FRAM_I2C


#include "FRAM.h"
#include "FRAM_MULTILANGUAGE.h"


FRAM fram;
FRAM_ML FML;

uint32_t sizeInBytes = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FRAM_LIB_VERSION: ");
  Serial.println(FRAM_LIB_VERSION);
  Serial.println();
  Serial.println("Assumes FRAM written with FRAM_multilanguage_write.ino" );

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
  uint32_t next = FML.begin(&fram, 0x1000);
  Serial.print("START:\t1000\n");
  Serial.print("NEXT:\t");
  Serial.println(next, HEX);
  Serial.print("SIZE:\t");
  Serial.println(next - 0x1000);
  Serial.print("LANG:\t");
  Serial.println(FML.getMaxLanguage());
  Serial.print("STRING:\t");
  Serial.println(FML.getMaxStrings());
  Serial.print("LENGTH:\t");
  Serial.println(FML.getMaxLength());
  Serial.println();

  
  Serial.println("Languages:");
  for (int i = 0; i < FML.getMaxLanguage(); i++)
  {
    char language[4];
    FML.getLanguageName(i, language);
    Serial.println(language);
  }

  Serial.println();
  for (int m = 0; m < 12; m++)
  {
    char buffer[20];
    Serial.print(m + 1);
    Serial.print("\t");

    for (int lang = 0; lang < FML.getMaxLanguage(); lang++)
    {
      FML.setLanguage(lang);
      FML.getText(m, buffer);
      Serial.print(buffer);
      Serial.print("\t");
    }
    Serial.println();
  }

  Serial.println();
  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
