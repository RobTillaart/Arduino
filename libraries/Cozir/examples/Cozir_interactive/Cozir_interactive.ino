//
//    FILE: Cozir_interactive.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Cozir lib
//     URL: https://github.com/RobTillaart/Cozir


#include "Arduino.h"
#include "cozir.h"


COZIR czr(&Serial1);


void setup()
{
  Serial1.begin(9600);
  czr.init();

  Serial.begin(115200);
  Serial.print("COZIR_LIB_VERSION: ");
  Serial.println(COZIR_LIB_VERSION);
  Serial.println();

  //  set to polling.
  czr.setOperatingMode(CZR_POLLING);
  delay(1000);

  menu();
}


void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();
    switch (toupper(c))
    {
      case '0':
        czr.setOperatingMode(CZR_COMMAND);
        break;
      case '1':
        czr.setOperatingMode(CZR_STREAMING);
        break;
      case '2':
        czr.setOperatingMode(CZR_POLLING);
        menu();
        break;
      case 'Z':
        if (czr.getOperatingMode() != 0)
        {
          Serial.print("CO2:\t");
          Serial.println(czr.CO2());
        }
        break;
      case 'T':
        if (czr.getOperatingMode() != 0)
        {
          Serial.print("Temp:\t");
          Serial.println(czr.celsius(), 1);
        }
        break;
      case 'H':
        if (czr.getOperatingMode() != 0)
        {
          Serial.print("Humid:\t");
          Serial.println(czr.humidity(), 1);
        }
        break;
      case 'L':
        if (czr.getOperatingMode() != 0)
        {
          Serial.print("Light:\t");
          Serial.println(czr.light(), 1);
        }
        break;
      case 'P':
        if (czr.getOperatingMode() != 0)
        {
          Serial.print("PPM:\t");
          Serial.println(czr.getPPMFactor());
        }
        break;
      case 'G':
        if (czr.getOperatingMode() != 0)
        {
          //  use with care
          //  Serial.println(czr.calibrateFreshAir());
        }
        break;
      case 'N':
        if (czr.getOperatingMode() != 0)
        {
          //  use with care
          //  Serial.println(czr.calibrateNitrogen());
        }
        break;
      case 'V':
        czr.getVersionSerial();
        break;
      case 'C':
        czr.getConfiguration();
        break;
      case '?':
        menu();
        break;
    }
  }

  //  for echo in continuous mode.
  if (Serial1.available())
  {
    Serial.write(Serial1.read());
  }
}


void menu()
{
  Serial.println();
  Serial.println("-- COZIR GC0034 --");
  Serial.println();
  Serial.println("  0 Command mode (low power)");
  Serial.println("  1 Continuous mode");
  Serial.println("  2 Polling mode");
  Serial.println();
  Serial.println("  G calibrate fresh air = 400 ppm (use with care)");
  Serial.println("  N calibrate nitrogen (use with care)");
  Serial.println();
  Serial.println("  Z get CO2");
  Serial.println("  P get PPM factor");
  Serial.println();
  Serial.println("  T get Temperature");
  Serial.println("  H get Humidity");
  Serial.println("  L get Light");
  Serial.println();
  Serial.println("  V version info");
  Serial.println("  C Configuration info");
  Serial.println();
  Serial.println("  ? menu");
  Serial.println();
}


//  -- END OF FILE --
