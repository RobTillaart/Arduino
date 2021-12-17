//
//    FILE: DS1821_thermostat_config.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-08-07
// PURPOSE: Arduino library for DS1821 temperature sensor
//     URL: https://github.com/RobTillaart/DS1821


// THERMOSTAT CONFIG
// - be sure to  read datasheet first!


#include "DS1821.h"

// change configuration if needed
const int VDD       = 11;
const int DQ        = 10;
const int polarity  = 1;    // 1 = HIGH, 0 = LOW;
const int lowTemp   = 19;
const int highTemp  = 21;


OneWire ds(DQ);
DS1821 tt(&ds);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.println("Set DS1821 in oneWire Mode");
  tt.setOneWireMode(VDD, DQ);

  Serial.print("set Polarity:\t");
  Serial.println(polarity);
  tt.setPolarity(polarity);
  if (tt.getPolarity() != polarity)
  {
    Serial.println("error @ polarity");
  }

  Serial.print("set Low Temp:\t");
  Serial.println(lowTemp);
  tt.setLow(lowTemp);
  if (tt.getLow() != lowTemp)
  {
    Serial.println("error @ lowTemp");
  }
  tt.clrLowFlag();


  Serial.print("set highTemp:\t");
  Serial.println(highTemp);
  tt.setLow(highTemp);
  if (tt.getHigh() != highTemp)
  {
    Serial.println("error @ highTemp");
  }
  tt.clrHighFlag();

  Serial.println("Set DS1821 in Thermostat Mode");
  tt.setThermostatMode();

  Serial.println("\nConfiguration done...");
}


void loop()
{
  Serial.print("ThermoStat:\t");
  Serial.println(digitalRead(DQ));
  delay(100);
}


// -- END OF FILE --

