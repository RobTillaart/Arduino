//
//    FILE: AS7331_interactive.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour (verbose)
//     URL: https://github.com/RobTillaart/AS7331
//
//  Not fully tested yet,
//  maybe need an I2C LCD display to show parameters + mode
//  or a VT100 terminal... if time permits...

#include "AS7331.h"


AS7331 mySensor(0x74);


int convTime = 10;  //  AS7331_CONV_1024 (~1 sec)
int gain = 5;       //  AS7331_GAIN_64x
int clockFreq = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("AS7331_LIB_VERSION: "));
  Serial.println(AS7331_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (mySensor.begin() == false)
  {
    Serial.print("invalid address: ");
    Serial.println(mySensor.getAddress(), HEX);
    while (1);
  }

  mySensor.powerUp();
  mySensor.startMeasurement();
}


void loop()
{
  if (Serial.available() > 0) processSerial();

  if (mySensor.conversionReady())
  {
    Serial.print("UVA:\t");
    Serial.println(mySensor.getUVA_uW());
    Serial.print("UVB:\t");
    Serial.println(mySensor.getUVB_uW());
    Serial.print("UVC:\t");
    Serial.println(mySensor.getUVC_uW());
    Serial.print("TEMP:\t");
    Serial.println(mySensor.getCelsius());
    Serial.print("ERR:\t");
    Serial.println(mySensor.getLastError());
    Serial.println();
  }

  //  other things.
}


void processSerial()
{
  int c = Serial.read();
  switch (c)
  {
    case 'R' :
      mySensor.softwareReset();
      break;
    case 'T' :
      if (convTime < 14) convTime++;
      mySensor.setConfigurationMode();
      mySensor.setConversionTime(convTime);
      mySensor.setMeasurementMode();
      break;
    case 't' :
      if (convTime > 0) convTime--;
      mySensor.setConfigurationMode();
      mySensor.setConversionTime(convTime);
      mySensor.setMeasurementMode();
      break;
    case 'G' :
      if (gain < 11) gain++;
      mySensor.setConfigurationMode();
      mySensor.setGain(gain);
      mySensor.setMeasurementMode();
      break;
    case 'g' :
      if (gain > 0) gain--;
      mySensor.setConfigurationMode();
      mySensor.setGain(gain);
      mySensor.setMeasurementMode();
      break;
    case 'S' :
      mySensor.setStandByOn();
      break;
    case 's' :
      mySensor.setStandByOff();
      break;
    case 'P' :
      mySensor.powerUp();
      break;
    case 'p' :
      mySensor.powerDown();
      break;
    case 'C' :
      if (clockFreq < 3) clockFreq++;
      mySensor.setConfigurationMode();
      mySensor.setClockFrequency(clockFreq);
      mySensor.setMeasurementMode();
      break;
    case 'c' :
      if (clockFreq > 0) clockFreq--;
      mySensor.setConfigurationMode();
      mySensor.setClockFrequency(clockFreq);
      mySensor.setMeasurementMode();
      break;
    case 'M' :
      mySensor.startMeasurement();
      break;
    case 'I' :
      Serial.print(gain);
      Serial.print('\t');
      Serial.print(convTime);
      Serial.print('\t');
      Serial.print(clockFreq);
      Serial.print('\n');
      break;
    case 'H' :
      help();
      break;
    default:
      break;
  }
}


void help()
{
  Serial.println("COMMANDS\n--------");
  Serial.println("R = Reset");
  Serial.println("T = Time incr");
  Serial.println("t = Time decr");
  Serial.println("G = Gain incr");
  Serial.println("g = Gain decr");
  Serial.println("S = Standby on");
  Serial.println("s = Standby off");
  Serial.println("P = Power on");
  Serial.println("p = Power down");
  Serial.println("C = Clock incr");
  Serial.println("c = Clock decr");
  Serial.println("M = Measure");
  Serial.println("H = Help");
  Serial.println();
}


//  -- END OF FILE --
