//
//    FILE: SHT4x_advanced.ino
//  AUTHOR: Xorlent (https://github.com/Xorlent)
// PURPOSE: Advanced example showing automatic heating and equilibrium detection
//     URL: https://github.com/RobTillaart/SHT4x
//
//  This example demonstrates an advanced humidity measurement technique:
//  1. Takes an initial measurement to assess conditions
//  2. If high humidity is detected, applies heater to drive off condensation
//  3. Continuously samples temperature for equilibrium after heating
//  4. Returns settled temperature and humidity values
//
//  Note: The auto mode functions are in SHT4x_advancedFunctions.ino
//        This file is automatically included when compiling with the Arduino IDE


#include <Wire.h>
#include <SHT4x.h>

#define SHT4X_DEBUG                   false   //  true will display heat detection and equilibrium checking Serial debug output
#define SHT_DEFAULT_ADDRESS           0x44

//  Auto mode configuration
#define EQUILIBRIUM_WINDOW_SIZE       8       //  8 samples = 2 seconds @ 250ms intervals
#define DEFAULT_EQUILIBRIUM_TIMEOUT   60000   //  In milliseconds
#define DEFAULT_DT_THRESHOLD          0.023f  //  °C/s max change rate to determine equilibrium


SHT4x sht;

//  Forward declarations for functions in SHT4x_auto.ino
bool requestAuto(measType initialMeasurement = SHT4x_MEASUREMENT_SLOW, uint16_t timeout = DEFAULT_EQUILIBRIUM_TIMEOUT, float threshold = DEFAULT_DT_THRESHOLD);
bool autoReady();
float getAutoTemperature();
float getAutoHumidity();

//  External variables from SHT4x_auto.ino
extern bool needsHeating;
extern uint32_t autoStartTime;


void setup()
{
  Serial.begin(115200);
  while (!Serial) delay(500);

  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SHT4x_LIB_VERSION: \t");
  Serial.println(SHT4x_LIB_VERSION);
  Serial.println();

  //  Initialize I2C
  //  On supported microcontrollers, custom pins can be set using Wire.begin(SDA_PIN, SCL_PIN);
  Wire.begin();
  Wire.setClock(100000);

  //  Initialize sensor
  if (!sht.begin())
  {
    Serial.println("ERROR: Could not connect to SHT4x sensor");
    Serial.println("Check wiring or adjust Wire.begin pin assignments:");
    while (1) delay(1000);
  }

  Serial.println("SHT4x sensor initialized successfully");
  Serial.println("\n--- Ready to start measurements ---");
}


void loop()
{
  Serial.println("\nWaiting 10 seconds to start cycle...\n");
  delay(10000);
  //  Start auto measurement cycle
  if (!requestAuto())
  {
    Serial.println("Failed to start auto mode");
    delay(3000);
    return;
  }

  //  Wait for completion
  while (!autoReady())
  {
    // Perform work here while waiting for results to be ready from the SHT4X sensor
    delay(10);
  }

  //  Sample complete, display results
  if (sht.getError() == SHT4x_OK)
  {
    Serial.println("\n=== Final Results ===");
    Serial.print("Temperature: ");
    Serial.print(getAutoTemperature(), 2);
    Serial.println(" °C");
    Serial.print("Humidity:    ");
    Serial.print(getAutoHumidity(), 1);
    Serial.println(" %RH");
    Serial.print("Heating required: ");
    Serial.println(needsHeating ? "Yes" : "No");

    uint32_t elapsed = millis() - autoStartTime;
    Serial.print("Total time:  ");
    Serial.print(elapsed);
    Serial.println(" ms");
  }
  else
  {
    Serial.print("ERROR: ");
    Serial.println(sht.getError(), HEX);
  }
}
//  -- END OF FILE --
