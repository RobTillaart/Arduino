//
//    FILE: SHT2x_resolution_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for SHT2x sensor resolution settings and performance
//     URL: https://github.com/RobTillaart/SHT2x
//
//  This example sketch demonstrates how to:
//  - Initialize the SHT2x sensor.
//  - Iterate through different measurement resolutions (0-3).
//  - Set the sensor's resolution using setResolution().
//  - Confirm the set resolution using getResolution().
//  - Measure the time taken for a synchronous read() operation at each resolution.
//  - Read and print temperature, humidity, raw temperature, and raw humidity values.
//  - Check for errors after sensor operations.
//

#include "SHT2x.h"
#include "Wire.h"

// Instantiate the sensor object.
// You can use a specific sensor type like SHT21, or the base SHT2x.
// SHT2x sensor;  // Generic base class
SHT21 sensor;     // Example using SHT21


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SHT2x_LIB_VERSION: \t");
  Serial.println(SHT2x_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!sensor.begin()) {
    Serial.println("SHT2x sensor not found or failed to initialize!");
    while (1); // Halt execution if sensor initialization fails
  }
  Serial.println("SHT2x sensor initialized.");
  Serial.println("Starting Resolution Test...");
  Serial.println("==========================");
}

void loop() {
  for (uint8_t res = 0; res < 4; res++) {
    Serial.println();
    Serial.print("Testing resolution: ");
    Serial.println(res);

    // Attempt to set the sensor resolution
    if (!sensor.setResolution(res)) {
      Serial.print("Error: Failed to set resolution to ");
      Serial.println(res);
      int error = sensor.getError();
      if (error != SHT2x_OK) {
        Serial.print("Sensor error code: 0x");
        Serial.println(error, HEX);
      }
      delay(2000); // Wait before trying next resolution
      continue;    // Skip to the next resolution setting
    }

    // Get and print the current resolution to confirm
    uint8_t currentRes = sensor.getResolution();
    Serial.print("Confirmed resolution set to: ");
    Serial.println(currentRes);
    if (currentRes != res) {
        Serial.println("Error: Resolution mismatch after setting!");
    }

    // Measure Temperature and Humidity Reading Time
    Serial.println("Performing synchronous read()...");
    uint32_t startTime = micros();
    bool readSuccess = sensor.read(); // Perform synchronous temperature and humidity reading
    uint32_t endTime = micros();
    uint32_t duration = endTime - startTime;

    Serial.print("read() duration: ");
    Serial.print(duration);
    Serial.println(" microseconds");

    // Check for errors after read()
    int error = sensor.getError(); // Clears the error flag
    if (!readSuccess || error != SHT2x_OK) {
      Serial.print("Error during read() operation. Success flag: ");
      Serial.print(readSuccess);
      Serial.print(", Error code: 0x");
      Serial.println(error, HEX);
    } else {
      // Print the readings
      Serial.print("Temperature:   ");
      Serial.print(sensor.getTemperature());
      Serial.println(" °C");

      Serial.print("Humidity:      ");
      Serial.print(sensor.getHumidity());
      Serial.println(" %");

      Serial.print("Raw Temp:      ");
      Serial.println(sensor.getRawTemperature());

      Serial.print("Raw Humidity:  ");
      Serial.println(sensor.getRawHumidity());
    }
    
    Serial.println("--------------------------");
    delay(2000); // Short delay before testing the next resolution
  }

  Serial.println();
  Serial.println("All resolutions tested. Repeating in 10 seconds...");
  Serial.println("==============================================");
  delay(10000); // Longer delay before repeating the entire test cycle
}
// -- END OF FILE --
