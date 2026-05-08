//
//    FILE: A02YYUW_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/A02YYUW


#include "A02YYUW.h"

//  adjust your board.
//  MEGA    - Serial1 = (19,18), Serial2 = (17,16), Serial3 = (15,14)
//  ESP32   - UART1 = (9,10), UART2 = (17,16)
//  RPIPICO - Serial1 = (0,1), Serial2 = (8,9), SerialPIO = (x,y)


A02YYUW mySensor(&Serial1, 19);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("A02YYUW_LIB_VERSION: ");
  Serial.println(A02YYUW_LIB_VERSION);
  Serial.println();

  Serial1.begin(9600);
  mySensor.begin();
  mySensor.setProcessingMode(true);
}


void loop()
{
  if (mySensor.newDistance())
  {
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(mySensor.getDistanceMM());
    Serial.print("\t");
    Serial.print(mySensor.getDistanceCM());
    Serial.print("\t");
    Serial.print(mySensor.getDistanceINCH());
    Serial.print("\n");
  }

  //  other code here.
}


//  -- END OF FILE --
