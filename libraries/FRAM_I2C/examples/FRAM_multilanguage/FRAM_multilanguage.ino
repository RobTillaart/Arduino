//
//    FILE: FRAM_multilanguage.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: multilanguage in FRAM.
//     URL: https://github.com/RobTillaart/FRAM_I2C
//
//
//  experimental code - NO OPERATIONAL CODE.


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
  //  uint32_t next = FML.begin(&fram, 0x1000, 4, 12, 20);
  uint32_t next = FML.begin(&fram, 0x1000);
  Serial.print("START:\t1000\n");
  Serial.print("NEXT:\t");
  Serial.println(next, HEX);
  Serial.print("LANG:\t");
  Serial.println(FML.getMaxLanguage());
  Serial.print("STRING:\t");
  Serial.println(FML.getMaxStrings());
  Serial.print("LENGTH:\t");
  Serial.println(FML.getMaxLength());
  Serial.println();


  //  user must fill all of them!
  /*
  FML.setLanguageName(0, "EN");   //  English
  FML.setLanguageName(1, "FR");   //  French
  FML.setLanguageName(2, "IRL");  //  Irish
  FML.setLanguageName(3, "P");    //  Portuguese
  */
  
  Serial.println("Languages:");
  for (int i = 0; i < FML.getMaxLanguage(); i++)
  {
    char language[4];
    FML.getLanguageName(i, language);
    Serial.println(language);
  }

  /*
  FML.setLanguage(0);
  FML.setText(0, "January");
  FML.setText(1, "February");
  FML.setText(2, "March");
  FML.setText(3, "April");
  FML.setText(4, "May");
  FML.setText(5, "June");
  FML.setText(6, "July");
  FML.setText(7, "August");
  FML.setText(8, "September");
  FML.setText(9, "October");
  FML.setText(10, "November");
  FML.setText(11, "December");

  FML.setLanguage(1);
  FML.setText(0, "janvier");
  FML.setText(1, "février");
  FML.setText(2, "mars");
  FML.setText(3, "avril");
  FML.setText(4, "mai");
  FML.setText(5, "juin");
  FML.setText(6, "juillet");
  FML.setText(7, "août");
  FML.setText(8, "septembre");
  FML.setText(9, "octobre");
  FML.setText(10, "novembre");
  FML.setText(11, "décembre");

  FML.setLanguage(2);
  FML.setText(0, "January");
  FML.setText(1, "February");
  FML.setText(2, "March");
  FML.setText(3, "April");
  FML.setText(4, "May");
  FML.setText(5, "June");
  FML.setText(6, "July");
  FML.setText(7, "August");
  FML.setText(8, "September");
  FML.setText(9, "October");
  FML.setText(10, "November");
  FML.setText(11, "December");

  FML.setLanguage(3);
  FML.setText(0, "janeiro");
  FML.setText(1, "fevereiro");
  FML.setText(2, "março");
  FML.setText(3, "abril");
  FML.setText(4, "maio");
  FML.setText(5, "junho");
  FML.setText(6, "julho");
  FML.setText(7, "agosto");
  FML.setText(8, "setembro");
  FML.setText(9, "outubro");
  FML.setText(10, "novembro");
  FML.setText(11, "dezembro");
  */

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
