//
//    FILE: temperatureConvertor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
//     URL: https://github.com/RobTillaart/Temperature


#include "temperature.h"

temperatureConverter TC;

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TEMPERATURE_LIB_VERSION: ");
  Serial.println(TEMPERATURE_LIB_VERSION);
  Serial.println();

  for (int celsius = -20; celsius <= 125; celsius++)
  {
    TC.setCelsius(celsius);
    float C = TC.getCelsius();
    float K = TC.getKelvin();
    float F  = TC.getFahrenheit();
    float De = TC.getDelisle();
    float Re = TC.getReamur();
    float Ra = TC.getRankine();
    float Ne = TC.getNewton();
    float Ro = TC.getRomer();
    float Le = TC.getLeiden();
    float We = TC.getWedgwood();

    if (celsius % 20 == 0)
    {
      Serial.println();
      Serial.print("\t C \t K \t F \t\t De \t Re \t Ra \t\t Ne \t Ro \t Le \t We \n");
    }

    Serial.print("\t");
    Serial.print(C);
    Serial.print("\t");
    Serial.print(K);
    Serial.print("\t");
    Serial.print(F);
    Serial.print("\t\t");
    Serial.print(De);
    Serial.print("\t");
    Serial.print(Re);
    Serial.print("\t");
    Serial.print(Ra);
    Serial.print("\t\t");
    Serial.print(Ne);
    Serial.print("\t");
    Serial.print(Ro);
    Serial.print("\t");
    Serial.print(Le);
    Serial.print("\t");
    Serial.print(We);
    Serial.print("\n");
  }


  /*
    for (int Celsius = 0; Celsius <= 100; Celsius += 100)
    {
      TC.setCelsius(Celsius);
      float C = TC.getCelsius();
      float K = TC.getKelvin();
      float F  = TC.getFahrenheit();
      float De = TC.getDelisle();
      float Re = TC.getReamur();
      float Ra = TC.getRankine();
      float Ne = TC.getNewton();
      float Ro = TC.getRomer();
      float Le = TC.getLeiden();
      float We = TC.getWedgwood();

      if (Celsius % 20 == 0)
      {
        Serial.println();
        Serial.print("\t C \t K \t F \t\t De \t Re \t Ra \t\t Ne \t Ro \t Le \t We \n");
      }

      Serial.print("\t");
      Serial.print(C);
      Serial.print("\t");
      Serial.print(K);
      Serial.print("\t");
      Serial.print(F);
      Serial.print("\t\t");
      Serial.print(De);
      Serial.print("\t");
      Serial.print(Re);
      Serial.print("\t");
      Serial.print(Ra);
      Serial.print("\t\t");
      Serial.print(Ne);
      Serial.print("\t");
      Serial.print(Ro);
      Serial.print("\t");
      Serial.print(Le);
      Serial.print("\t");
      Serial.print(We);
      Serial.print("\n");
    }
  */

  Serial.print("Done...");
}


void loop()
{
}


//  -- END OF FILE --
