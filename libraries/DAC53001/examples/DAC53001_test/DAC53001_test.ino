//
//    FILE: DAC53001_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test API
//     URL: https://github.com/RobTillaart/DAC53001
//
//  To be extended

#include "DAC53001.h"

//  adjust device type and address if needed.
DAC53001 dac(0x30);  //  default Wire

uint16_t value = 0;

void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DAC53001_LIB_VERSION: ");
  Serial.println(DAC53001_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = dac.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);

  Serial.println("\nDevice info");
  Serial.print("STATUS:\t");
  Serial.println(dac.getStatus(), HEX);
  Serial.print("DEVID:\t");
  Serial.println(dac.getDeviceID(), HEX);
  Serial.print("VERS:\t");
  Serial.println(dac.getVersionID(), HEX);
  Serial.print("BUSY0:\t");
  Serial.println(dac.isBusy(0), HEX);


  Serial.println("\nsetVoltageReference");
  for (int vr = 0; vr < 5; vr++)
  {
    dac.setReference((DACX300X_reference)vr);
    int nvr = dac.getReference();
    Serial.print("REF:\t");
    Serial.print(vr);
    Serial.print(" => ");
    Serial.println(nvr);
  }

  Serial.println("\nsetCurrentRange");
  for (int cr = 0; cr < 12; cr++)
  {
    dac.setCurrentRange(cr);
    int ncr = dac.getCurrentRange();
    Serial.print("RANGE:\t");
    Serial.print(cr);
    Serial.print(" => ");
    Serial.println(ncr);
  }

  Serial.println("\nsetOutputMode");
  for (int om = 0; om < 8; om++)
  {
    dac.setOutputMode(om);
    int nom = dac.getOutputMode();
    Serial.print("OUTPUT:\t");
    Serial.print(om);
    Serial.print(" => ");
    Serial.println(nom);
  }

  Serial.println("\nsetDAC");
  for (uint16_t value = 0; value <= dac.getMaxValue(); value++)
  {
    dac.setDAC(value);
    uint16_t nv = dac.getDAC();
    //  print only the errors.
    if (nv != value)
    {
      Serial.print("DAC:\t");
      Serial.print(value);
      Serial.print(" => ");
      Serial.println(nv);
    }
  }


  Serial.println("\nDone...");
}



void loop()
{
}


//  -- END OF FILE --
