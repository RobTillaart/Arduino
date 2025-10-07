//
//    FILE: AS7331_continuous_IRQ.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AS7331

//  Connect the Ready Pin to an IRQ Pin e.g. 2
//  to detect the conversion is ready.
//
//  Sketch works well with plotter.


#include "AS7331.h"


AS7331 mySensor(0x74);

volatile bool AS7331_READY = false;
const uint8_t IRQ_PIN = 2;

void RDY_IRQ()
{
  AS7331_READY = true;
}


void setup()
{
  Serial.begin(115200);
  //  comment header for plotter
  //  Serial.println();
  //  Serial.println(__FILE__);
  //  Serial.print(F("AS7331_LIB_VERSION: "));
  //  Serial.println(AS7331_LIB_VERSION);
  //  Serial.println();

  //  READY Interrupt.
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(IRQ_PIN), RDY_IRQ, RISING);

  Wire.begin();

  if (mySensor.begin() == false)
  {
    Serial.print("invalid address: ");
    Serial.println(mySensor.getAddress(), HEX);
    while (1);
  }

  //  explicit reset and configuration
  mySensor.softwareReset();
  mySensor.setConfigurationMode();
  mySensor.powerUp();
  mySensor.setStandByOff();
  mySensor.setMode(AS7331_MODE_CONTINUOUS);
  mySensor.setGain(AS7331_GAIN_512x);
  mySensor.setConversionTime(AS7331_CONV_016);

  mySensor.startMeasurement();

  //  PLOTTER HEADER
  Serial.println("UVA\tUVB\tUVC\tTEMP\tERR");
}


void loop()
{
  if (AS7331_READY == true)
  {
    AS7331_READY = false;

    Serial.print(mySensor.getUVA_uW());
    Serial.print("\t");
    Serial.print(mySensor.getUVB_uW());
    Serial.print("\t");
    Serial.print(mySensor.getUVC_uW());
    Serial.print("\t");
    Serial.print(mySensor.getCelsius());
    Serial.print("\t");
    Serial.print(mySensor.getLastError());
    Serial.println();
  }

  //  other things.
}


//  -- END OF FILE --
