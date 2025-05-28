//
//    FILE: SHT2x_battery_check.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for SHT2x sensor battery check functionality
//     URL: https://github.com/RobTillaart/SHT2x
//
//  This example sketch demonstrates how to:
//  - Initialize the SHT2x sensor.
//  - Periodically check the sensor's battery status using batteryOK().
//  - Handle potential errors during the status check.
//  - Print the battery status to the Serial Monitor.
//
//  Note: The battery status feature relies on a bit in the user register.
//  Not all SHT2x compatible sensors may implement or reliably report this.
//  It typically indicates if VDD is below a certain threshold (e.g., ~2.25V).
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
    Serial.println("Please check wiring and sensor type.");
    while (1); // Halt execution if sensor initialization fails
  }
  Serial.println("SHT2x sensor initialized.");
  Serial.println("Starting Battery Status Check...");
  Serial.println("==============================");
}

void loop() {
  Serial.print("Checking battery status... ");

  // Call batteryOK() to check the battery status bit in the user register.
  bool isBatteryOK = sensor.batteryOK();

  // It's important to check for errors after calling batteryOK(),
  // as this function involves reading the user register via I2C.
  int error = sensor.getError(); // Clears the error flag

  if (error != SHT2x_OK) {
    Serial.print("Error while checking battery status. Error code: 0x");
    Serial.println(error, HEX);
  } else {
    // Print the battery status
    if (isBatteryOK) {
      Serial.println("Battery status: OK (VDD >= ~2.25V)");
    } else {
      Serial.println("Battery status: LOW (VDD < ~2.25V)");
    }
  }
  
  Serial.println("------------------------------");
  delay(5000); // Wait 5 seconds before checking again
}
// -- END OF FILE --
