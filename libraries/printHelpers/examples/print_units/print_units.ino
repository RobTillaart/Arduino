//
//    FILE: print_units.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"

uint32_t start, stop, duration;


//  original reference implementation.
/*
char * units(float value, uint8_t decimals, const char * units)
{
  static char buf[25];
  strcpy(buf, eng(value, decimals, true));

  uint8_t len = strlen(buf);  //  optimize spot to replace
  if (strstr(buf, "E+"))
  {
    //  add prefix = "TGMK munpa";
    if (strstr(buf, "E+12")) strcpy(&buf[len - 4], " T");
    else if (strstr(buf, "E+09")) strcpy(&buf[len - 4], " G");
    else if (strstr(buf, "E+06")) strcpy(&buf[len - 4], " M");
    else if (strstr(buf, "E+03")) strcpy(&buf[len - 4], " K");
    else if (strstr(buf, "E+00")) strcpy(&buf[len - 4], "  ");
  }
  else if (strstr(buf, "E-"))
  {
    if (strstr(buf, "E-03")) strcpy(&buf[len - 4], " m");
    else if (strstr(buf, "E-06")) strcpy(&buf[len - 4], " u");
    else if (strstr(buf, "E-09")) strcpy(&buf[len - 4], " n");
    else if (strstr(buf, "E-12")) strcpy(&buf[len - 4], " p");
    else if (strstr(buf, "E-15")) strcpy(&buf[len - 4], " a");
  }
  strcat(buf, units);
  return buf;
}
*/


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_LIB_VERSION: ");
  Serial.println(PRINTHELPERS_LIB_VERSION);
  Serial.println();


  Serial.println("Engineering rightAlign = true");
  for (float f = 3.14e-6; f < 1e7; f *= 6.6)
  {
    Serial.println(eng(f, 1, true));
  }
  Serial.println();


  Serial.println("Volts");
  for (float f = 3.14e-6; f < 1e7; f *= 6.6)
  {
    Serial.println(units(f, 1, "Volts"));
  }
  Serial.println();


  Serial.println("Capacity");
  for (float f = 1e-12; f <= 1; f *= 10)
  {
    Serial.println(units(f, 0, "F"));
  }
  Serial.println();


  Serial.println("Current");
  for (float f = 123e-6; f < 10; f *= PI)
  {
    Serial.println(units(f, 2, "A"));
  }
  Serial.println();


  Serial.println("Resistance");
  for (float f = 12; f < 1e7; f *= EULER)
  {
    Serial.println(units(f, 1, "Ohm"));
  }
  Serial.println();


  Serial.println("Pressure");
  for (float f = 123e-3; f < 1e12; f *= 23.9)
  {
    Serial.println(units(f, 2, "P"));
  }
  Serial.println();


  Serial.println("scalar I");
  for (float f = 357e-6; f < 1e12; f *= 23.9)
  {
    Serial.println(units(f, 2, ""));
  }
  Serial.println();


  Serial.println("scalar II");
  for (float f = 357e-6; f < 1e12; f *= 23.9)
  {
    Serial.println(units(f, 2, " units"));
  }
  Serial.println();


  Serial.println("Temperature");
  for (float f = 259e-6; f < 1e12; f *= 21.9)
  {
    Serial.println(units(f, 1, "K"));
  }
  Serial.println();


  Serial.println("Distance");
  for (float f = 1e-6; f < 1e13; f *= 11.1)
  {
    Serial.println(units(f, 1, "Meter"));
  }
  Serial.println();


  Serial.println("Frequency");
  for (float f = 1e-3; f < 1e13; f *= 12.3)
  {
    Serial.println(units(f, 1, "Hz"));
  }
  Serial.println();


  Serial.println("when out of range, just add units.");
  Serial.println(units(246e23, 2, "K"));

  Serial.println("\ndone...");
}


void loop()
{
}



//  -- END OF FILE --
