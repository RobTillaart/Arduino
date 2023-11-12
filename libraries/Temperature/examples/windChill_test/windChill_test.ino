//
//    FILE: windChill_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-01-09


#include "temperature.h"

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TEMPERATURE_LIB_VERSION: ");
  Serial.println(TEMPERATURE_LIB_VERSION);
  Serial.println();

  Serial.println(WindChill_F_mph (0, 10, true), 3);
  Serial.println(WindChill_C_kmph(0, 10, true), 3);
  Serial.println(WindChill_C_mps (0, 10, true), 3);
  Serial.println(WindChill_C_kmph(-20, 5, true), 3);


  Serial.println(WindChill_F_mph (0, 10, false), 3);
  Serial.println(WindChill_C_kmph(0, 10, false), 3);
  Serial.println(WindChill_C_mps (0, 10, false), 3);
 

  Serial.print("Done...");
}


void loop()
{
}


//  -- END OF FILE --
