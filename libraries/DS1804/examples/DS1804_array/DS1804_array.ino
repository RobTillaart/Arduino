//    FILE: DS1804_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DS1804
//
//  not tested yet

#include "DS1804.h"


//  adjust pins if needed
const uint8_t CSPIN1 = 3;
const uint8_t CSPIN2 = 4;
const uint8_t CSPIN3 = 5;
const uint8_t INCPIN = 6;
const uint8_t UDPIN  = 7;


DS1804 ds[3] =
{
  DS1804(CSPIN1, INCPIN, UDPIN),
  DS1804(CSPIN2, INCPIN, UDPIN),
  DS1804(CSPIN3, INCPIN, UDPIN)
};

int idx = 0;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS1804_LIB_VERSION: ");
  Serial.println(DS1804_LIB_VERSION);
  Serial.println();

  //  all deselected by default
  for (int i = 0; i < 3; i++)
  {
    ds[i].begin();
  }
}


void loop()
{
  if (Serial.available())
  {
    int c = Serial.read();
    //  SELECT MODULE
    if (c == '0') {
      idx = 0;
      ds[0].select(true);
      ds[1].select(false);
      ds[2].select(false);
    };
    if (c == '1') {
      idx = 1;
      ds[0].select(false);
      ds[1].select(true);
      ds[2].select(false);
    };
    if (c == '2') {
      idx = 2;
      ds[0].select(false);
      ds[1].select(false);
      ds[2].select(true);
    };
    //  DESELECT ALL
    if (c == '3') {
      idx = 0;
      ds[0].select(false);
      ds[1].select(false);
      ds[2].select(false);
    };
    //  UP DOWN
    if (c == 'U') ds[idx].moveUp();
    if (c == 'D') ds[idx].moveDown();
  }
}


//  -- END OF FILE --
