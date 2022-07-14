//
//    FILE: sparse_matrix_2D_histogram.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo 2D
//     URL: https://github.com/RobTillaart/SparseMatrix
//
// TOPVIEW SHT85  (check datasheet)
//            +-------+
// +-----\    | SDA 4 -----
// | +-+  ----+ GND 3 -----
// | +-+  ----+ +5V 2 -----
// +-----/    | SCL 1 -----
//            +-------+


#include  "SparseMatrix.h"
#include "SHT85.h"

#define SHT85_ADDRESS         0x44

SHT85 sht;

SparseMatrix sm(40);
uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);

  Serial.print("SHT_LIB_VERSION: \t");
  Serial.println(SHT_LIB_VERSION);
  Serial.print("SPARSEMATRIX_LIB_VERSION: \t");
  Serial.println(SPARSEMATRIX_LIB_VERSION);

  sm.clear();

  Wire.begin();
  sht.begin(SHT85_ADDRESS);
  Wire.setClock(100000);
}


void loop()
{
  if (millis() - lastTime > 10000)
  {
    lastTime = millis();
    dump(20, 10, 0);
  }
  sht.read();
  uint8_t x = round(sht.getHumidity()) - 45;     // adjust if needed 
  uint8_t y = round(sht.getTemperature()) - 20;  // adjust if needed
//  Serial.print(x);
//  Serial.print(" ");
//  Serial.print(y);
//  Serial.print("\n");
  sm.add(x, y, 1);
  delay(1000);
}


void dump(uint8_t sx, uint8_t sy, uint8_t dm)
{
  Serial.println();
  Serial.print("DUMP\t");

  Serial.print(sm.size());
  Serial.print("\t");
  Serial.print(sm.count());
  Serial.print("\t");

  Serial.print(sx);
  Serial.print("x");
  Serial.print(sy);
  Serial.print("\t");
  Serial.println(sm.sum());
  for (int y = 0; y < sy; y++)
  {
    for (int x = 0; x < sx; x++)
    {
      Serial.print(sm.get(x, y), dm);
      Serial.print('\t');
    }
    Serial.println();
  }
  Serial.println();
}


//  -- END OF FILE --
