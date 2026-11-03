//
//    FILE: SLF3S_product_serial.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/SLF3S
//
//  To be used with Serial plotter.

#include "SLF3S.h"
#include "printHelpers.h"


SLF3S slf;
uint32_t lastTime = 0;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SLF3S_LIB_VERSION: ");
  Serial.println(SLF3S_LIB_VERSION);
  Serial.println();

  Wire.begin();

  //  SLF3S-0600F
  if (slf.begin(600) == false)
  {
    Serial.print("Error: ");
    Serial.println(slf.getLastError());
    while(1);
  }

  //  might check getLastError too
  uint32_t productID = slf.readProductID();
  uint64_t serialNR = slf.readSerialNR();
  Serial.print("ProductID:\t0x");
  Serial.println(hex(productID));    //  hex() from printHelpers library
  Serial.print("SerialNR:\t0x");
  Serial.println(hex(serialNR));     //  hex() from printHelpers library
  Serial.println("\ndone...");
}


void loop()
{

}


//  -- END OF FILE --
