//
//    FILE: dhtnew_waitForRead.ino
//  AUTHOR: Mr-HaleYa
// VERSION: 0.1.0
// PURPOSE: DHTNEW library waitForRead example sketch for Arduino
//     URL: https://github.com/RobTillaart/DHTNew
// HISTORY:
//
// 0.1.0    2020-05-03 initial version
//
// FRONT left 2 right
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : NC
// PIN 4 : GND

#include <dhtnew.h>

DHTNEW mySensor(6);

void setup()
{
  Serial.begin(115200);
  Serial.println("\n");
  Serial.println("dhtnew_waitForRead.ino");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();
  Serial.println("This sketch shows the use of the setWaitForReading() flag (default value is false).");
  Serial.println("Setting the flag to true will make the sketch wait until the sensor is ready to take another reading.");
  Serial.println("Otherwise, if the sensor was not ready to take a new reading the previous data will be returned.");
  Serial.println("Note: Sensor reading times vary with sensor type");

  Serial.println("\n1. Test with WaitForReading not set");
  Serial.println("AGE\tHUMI\tTEMP\tTIME\tTYPE\tSTAT");
  test();
  test();
  test();
  test();
  test();

  Serial.print("\n2. Test with WaitForReading set to ");
  mySensor.setWaitForReading(true);
  Serial.println(mySensor.getWaitForReading() ? "true" : "false");
  Serial.println("AGE\tHUMI\tTEMP\tTIME\tTYPE\tSTAT");
  test();
  test();
  test();
  test();
  test();

  Serial.println("\nDone...");
}

void loop()
{

}

void test()
{
  // READ DATA
  uint32_t start = micros();
  int chk = mySensor.read();
  uint32_t stop = micros();
  uint32_t duration = stop - start;

  // DISPLAY IF OLD OR NEW DATA
  if (duration > 50){Serial.print("NEW\t");}else{Serial.print("OLD\t");}
  
  // DISPLAY DATA
  Serial.print(mySensor.getHumidity(), 1);
  Serial.print(",\t");
  Serial.print(mySensor.getTemperature(), 1);
  Serial.print(",\t");
  Serial.print(duration);
  Serial.print(",\t");
  Serial.print(mySensor.getType());
  Serial.print(",\t");

  switch (chk)
  {
    case DHTLIB_OK:
      Serial.println("OK");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
    default:
      Serial.println("Unknown error");
      break;
  }
  delay(100);
}

// END OF FILE
