//
//    FILE: AS5600_position_speed.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo compare performance with update flag
//     URL: https://github.com/RobTillaart/AS5600
//
//  Examples may use AS5600 or AS5600L devices.
//  Check if your sensor matches the one used in the example.
//  Optionally adjust the code.


#include "AS5600.h"

//  Uncomment the line according to your sensor type
AS5600L as5600;   //  use default Wire
// AS5600 as5600;   //  use default Wire

uint32_t start, stop;

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);
  Serial.println();

  Wire.begin();

  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  //  default, just be explicit.

  Serial.println(as5600.getAddress());

  //  as5600.setAddress(0x40);  //  AS5600L only

  int b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);

  for (uint32_t speed = 100000; speed <= 800000;  speed += 100000)
  {
    Wire.setClock(speed);
    Serial.println(speed);
    delay(100);

    start = micros();
    as5600.getCumulativePosition();
    as5600.getAngularSpeed();
    stop = micros();
    Serial.print("update true: \t");
    Serial.println(stop - start);
    delay(100);

    start = micros();
    as5600.readAngle();
    as5600.getCumulativePosition(false);
    as5600.getAngularSpeed(AS5600_MODE_DEGREES, false);
    stop = micros();
    Serial.print("update false: \t");
    Serial.println(stop - start);
    Serial.println();
    delay(100);
  }

  /*
     about ~1% slower on AVR @100K
    start = micros();
    as5600.getCumulativePosition(true);
    as5600.getAngularSpeed(AS5600_MODE_DEGREES, false);
    stop = micros();
    Serial.print("update false: \t");
    Serial.println(stop - start);
    Serial.println();
    delay(100);
  */

  delay(2000);
}


void loop()
{
  static uint32_t lastTime = 0;

  if (millis() - lastTime >= 100)
  {
    lastTime = millis();
    as5600.readAngle();
    Serial.print(as5600.getCumulativePosition(false));
    Serial.print("\t");
    Serial.println(as5600.getAngularSpeed(AS5600_MODE_DEGREES, false));
  }
}


//  -- END OF FILE --
