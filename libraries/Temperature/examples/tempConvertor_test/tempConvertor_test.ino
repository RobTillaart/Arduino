//
//    FILE: temperatureConvertor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
//    DATE: 2022-01-08


#include "temperature.h"

temperatureConverter TC;

void setup()
{
  Serial.begin(115200);
  while(!Serial);
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

    if (celsius % 20 == 0)
    {
      Serial.println();
      Serial.print("\t C \t K \t F \t\t De \t Re \t Ra \t\t Ne \t Ro \n");
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
    Serial.print("\n");
  }


  /*
    for (int celsius = 0; celsius <= 100; celsius += 100)
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

      if (celsius % 20 == 0)
      {
        Serial.println();
        Serial.print("\t C \t K \t F \t\t De \t Re \t Ra \t\t Ne \t Ro \n");
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
      Serial.print("\n");
    }
  */

  Serial.print("Done...");
}


void loop()
{
}


//  -- END OF FILE --
