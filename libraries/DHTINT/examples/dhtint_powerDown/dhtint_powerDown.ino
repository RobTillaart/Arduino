//
//    FILE: dhtint_powerDown.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DHTINT library test sketch for Arduino
//     URL: https://github.com/RobTillaart/DHTINT

// DHT PIN layout from left to right
// =================================
// FRONT : DESCRIPTION
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : Not Connected
// pin 4 : GND

// to see the effect one must apply a voltmeter to the data pin of the sensor
// during the low power mode. Measuring during communication will disrupt the
// data transfer.


#include <dhtint.h>

DHTINT mySensor(16);


void setup()
{
  while(!Serial);        // MKR1010 needs this

  Serial.begin(115200);
  Serial.println("dhtint_powerDown.ino");
  Serial.print("DHTINT_LIB_VERSION: ");
  Serial.println(DHTINT_LIB_VERSION);

  // MKR1010 needs this
  // mySensor.setDisableIRQ(false);

  Serial.println("\nstartup");
  delay(2000);

  Serial.println("read sensor with 2 second interval");
  for (int i = 0; i < 3; i++)
  {
    int rv = mySensor.read();
    if (rv != DHTLIB_OK)
    {
      Serial.println(rv);  // will print -7 when measuring voltage
    }
    Serial.print(mySensor.getHumidity());
    Serial.print(",\t");
    Serial.println(mySensor.getTemperature());
    delay(2000);
  }

  Serial.println("switch to low power (~ 5 seconds )");
  Serial.println("measure voltage");
  mySensor.powerDown();
  delay(5000);

  Serial.println("switch sensor on (and wait 2 seconds)");
  mySensor.powerUp();
  // wait for 2 seconds.
  delay(2000);

  Serial.println("read sensor with 2 second interval");
  for (int i = 0; i < 3; i++)
  {
    mySensor.read();
    Serial.print(mySensor.getHumidity());
    Serial.print(",\t");
    Serial.println(mySensor.getTemperature());
    delay(2000);
  }

  Serial.println("\nDone...");
}


void loop()
{
}


// -- END OF FILE --

