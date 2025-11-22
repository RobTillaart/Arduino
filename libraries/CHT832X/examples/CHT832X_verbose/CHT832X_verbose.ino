//
//    FILE: CHT832X_verbose.ino
//  AUTHOR: divadiow (from issue #2)
// PURPOSE: Demo for CHT832X I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/CHT832X

//  Always check datasheet for connections


#include "CHT832X.h"

CHT8320 CHT;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("CHT832X_LIB_VERSION: "));
  Serial.println(CHT832X_LIB_VERSION);
  Serial.println();


  Wire.begin();

  //  Call begin() and print its return value
  int beginStatus = CHT.begin();
  Serial.print("CHT.begin() return value: ");
  Serial.println(beginStatus);

  if (beginStatus == CHT832X_OK)
  {
    Serial.println("CHT832X initialized successfully.");
  }
  else
  {
    Serial.println("CHT832X initialization failed!");
  }

  // Test isConnected() and print the result
  if (CHT.isConnected())
  {
    Serial.println("CHT832X is connected.");
  }
  else
  {
    Serial.println("CHT832X is not connected!");
  }

  Serial.print("Error: ");
  Serial.println(CHT.getError());

  delay(1000);
}


void loop()
{
  //  Print the return value of the read() function
  int readValue = CHT.read();
  Serial.print("Read Value: ");
  Serial.println(readValue);

  if (readValue == CHT832X_OK)
  {
    Serial.print("Temperature: ");
    Serial.print(CHT.getTemperature());
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(CHT.getHumidity());
    Serial.println(" %");
  }
  else
  {
    Serial.print("Error reading sensor data: ");
    Serial.println(CHT.getError());
  }

  //  Add a delay to prevent spamming the serial monitor
  delay(1000);
}


//  -- END OF FILE --
