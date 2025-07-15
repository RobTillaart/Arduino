//
//    FILE: AS5600_detect_type.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AS5600
//
//  Examples may use AS5600 or AS5600L devices.

#include <Wire.h>
#include "AS5600.h"

//  if address of the AS5600L has been changed it can be anything
//  AS5600 == 0, AS5600L == 1;  undefined == 2
int as5600Type = 2;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);
  Serial.println();

  Wire.begin();

  Serial.println("check address AS5600 0x36: ");
  Wire.beginTransmission(0x36);
  int error = Wire.endTransmission();
  if (error != 0)
  {
    Serial.print("not found.");
  }
  else
  {
    Serial.println("found.");
    as5600Type = 0;
  }

  Serial.println("check address AS5600L 0x40: ");
  Wire.beginTransmission(0x40);
  error = Wire.endTransmission();
  if (error != 0)
  {
    Serial.print("not found.");
  }
  else
  {
    Serial.println("found.");
    as5600Type = 1;
  }
  if (as5600Type == 2)
  {
    Serial.println("Could not determine type, so set it to AS5600L");
    as5600Type = 1;
  }
}


void loop()
{
  if (as5600Type == 0)
  {
    AS5600 device;
    device.begin();

    Serial.print(device.readAngle());
    Serial.print("\t");
    Serial.println(device.rawAngle());
    Serial.print("STATUS:\t ");
    Serial.println(device.readStatus(), HEX);
    Serial.print("CONFIG:\t ");
    Serial.println(device.getConfigure(), HEX);
    Serial.print("  GAIN:\t ");
    Serial.println(device.readAGC(), HEX);
    Serial.print("MAGNET:\t ");
    Serial.println(device.readMagnitude(), HEX);
    Serial.print("DETECT:\t ");
    Serial.println(device.detectMagnet(), HEX);
    Serial.print("M HIGH:\t ");
    Serial.println(device.magnetTooStrong(), HEX);
    Serial.print("M  LOW:\t ");
    Serial.println(device.magnetTooWeak(), HEX);
    Serial.println();
  }
  else  //  default AS5600L
  {
    AS5600L device;
    device.begin();

    Serial.print(device.readAngle());
    Serial.print("\t");
    Serial.println(device.rawAngle());
    Serial.print("STATUS:\t ");
    Serial.println(device.readStatus(), HEX);
    Serial.print("CONFIG:\t ");
    Serial.println(device.getConfigure(), HEX);
    Serial.print("  GAIN:\t ");
    Serial.println(device.readAGC(), HEX);
    Serial.print("MAGNET:\t ");
    Serial.println(device.readMagnitude(), HEX);
    Serial.print("DETECT:\t ");
    Serial.println(device.detectMagnet(), HEX);
    Serial.print("M HIGH:\t ");
    Serial.println(device.magnetTooStrong(), HEX);
    Serial.print("M  LOW:\t ");
    Serial.println(device.magnetTooWeak(), HEX);
    Serial.println();
    delay(3000);
  }
}
