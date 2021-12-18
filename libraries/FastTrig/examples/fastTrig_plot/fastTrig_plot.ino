//
//    FILE: fastTrig_plot.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: testing the fastTrigonio functions
//    DATE: 2020-09-07

// sketch to visualy compare tan(x) and itan(x)
// use IDE.plotter to view.


#include "FastTrig.h"


volatile float x;
int i;


void setup()
{
  Serial.begin(115200);

  // clean plotter buffer
  for (int i = 0; i < 500; i++)
  {
    Serial.print(0);
    Serial.print("\t");
    Serial.print(0);
    Serial.print("\t");
    Serial.print(0);
    Serial.print("\t");
    Serial.print(0);
    Serial.print("\t");
    Serial.print(0);
    Serial.print("\t");
    Serial.print(0);
    Serial.print("\t");
    Serial.println();
  }

  for (int i = -9100; i < -8900; i++)
  {
    Serial.print(tan(0.01 * i * PI / 180.0), 6);
    Serial.print("\t");
    Serial.print(itan(0.01 * i), 6);
    Serial.println();
  }
  for (int i = -100; i < 100; i++)
  {
    Serial.print(tan(0.1 * i * PI / 180.0), 6);
    Serial.print("\t");
    Serial.print(itan(0.1 * i), 6);
    Serial.println();
  }
  for (int i = 850; i < 950; i++)
  {
    Serial.print(tan(0.1 * i * PI / 180.0), 6);
    Serial.print("\t");
    Serial.print(itan(0.1 * i), 6);
    Serial.println();
  }

  Serial.println("done...\n");
}


void loop()
{
}


// -- END OF FILE --

