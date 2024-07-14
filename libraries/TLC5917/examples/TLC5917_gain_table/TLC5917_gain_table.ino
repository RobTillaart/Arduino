//
//    FILE: TLC5917_gain_table.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo getCOnfiguration and getXXXGain()
//          creates a table e.g. for Excel or plotter.
//     URL: https://github.com/RobTillaart/TLC5917


#include "TLC5917.h"


const int DEVICES = 1;
const int CLOCK   = 13;
const int DATA    = 12;
const int LATCH   = 11;
const int ENABLE  = 10;

TLC5917 tlc(DEVICES, CLOCK, DATA, LATCH, ENABLE);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5917_LIB_VERSION: \t");
  Serial.println(TLC5917_LIB_VERSION);
  Serial.println();

  if (tlc.begin() == false)
  {
    Serial.println("error");
    while (1);
  }

  tlc.setSpecialMode();

  Serial.println("\tCONF\tVGAIN\tCGAIN");
  for (int conf = 0; conf <= 255; conf++)
  {
    if (conf % 16 == 0) Serial.println();

    tlc.writeConfiguration(conf);
    Serial.print("\t");
    //  comment next line for nice plotter view
    Serial.print(tlc.getConfiguration());
    Serial.print("\t");
    Serial.print(tlc.getVoltageGain(), 3);
    Serial.print("\t");
    Serial.println(tlc.getCurrentGain(), 3);
  }
  Serial.println();

  tlc.setNormalMode();
  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
