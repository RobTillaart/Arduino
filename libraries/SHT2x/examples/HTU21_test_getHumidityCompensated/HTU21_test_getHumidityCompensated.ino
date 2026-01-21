//
//    FILE: HTU21_test_getHumidityCompensated.ino
//  AUTHOR: morfeus02, Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SHT2x


#include "Wire.h"
#include "SHT2x.h"

HTU21 sht;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SHT2x_LIB_VERSION: \t");
  Serial.println(SHT2x_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!sht.begin())
  {
    Serial.println("ERROR: Could not connect to HTU21 sensor!");
    while (1);
  }

  Serial.println("HTU21 connected.");
  Serial.println();
  Serial.println("Test getHumidityCompensated()");
  Serial.println("================================================");
  Serial.println();
}


void loop()
{
  sht.read();

  float temperature = sht.getTemperature();
  float humidity = sht.getHumidity();
  float compensated = sht.getHumidityCompensated();
  float factor = sht.getHumidityCompensationFactor();

  //  manually calculate expected value using the formula
  float expected = humidity + (25.0f - temperature) * factor;

  //  check if library result matches manual calculation
  float diff = compensated - expected;
  bool pass = (abs(diff) < 0.001);  //  tolerance for float comparison

  //  print results
  Serial.println("--- Reading ---");
  Serial.print("Temperature:        ");
  Serial.print(temperature, 2);
  Serial.println(" C");

  Serial.print("Humidity (raw):     ");
  Serial.print(humidity, 2);
  Serial.println(" %");

  Serial.print("Compensation factor: ");
  Serial.println(factor, 4);

  Serial.print("Compensation delta:  ");
  Serial.print((25.0f - temperature) * factor, 2);
  Serial.println(" %");

  Serial.print("Humidity (comp):    ");
  Serial.print(compensated, 2);
  Serial.println(" %");

  Serial.print("Expected (manual):  ");
  Serial.print(expected, 2);
  Serial.println(" %");

  Serial.print("Validation:         ");
  Serial.println(pass ? "PASS" : "FAIL");

  Serial.println();

  delay(2000);
}


//  -- END OF FILE --
