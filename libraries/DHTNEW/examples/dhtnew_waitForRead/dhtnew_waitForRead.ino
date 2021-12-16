//
//    FILE: dhtnew_waitForRead.ino
//  AUTHOR: Mr-HaleYa
// PURPOSE: DHTNEW library waitForRead example sketch for Arduino
//     URL: https://github.com/RobTillaart/DHTNew

// DHT PIN layout from left to right
// =================================
// FRONT : DESCRIPTION  
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : Not Connected
// pin 4 : GND


#include <dhtnew.h>

DHTNEW mySensor(5);   // ESP 16    UNO 5    MKR1010 5


void setup()
{
  while(!Serial);        // MKR1010 needs this

  Serial.begin(115200);
  Serial.println("\n");
  Serial.println("dhtnew_waitForRead.ino");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();

  // MKR1010 needs this
  // mySensor.setDisableIRQ(false);

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
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT_A:
      Serial.print("Time out A error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT_B:
      Serial.print("Time out B error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT_C:
      Serial.print("Time out C error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT_D:
      Serial.print("Time out D error,\t");
      break;
    case DHTLIB_ERROR_SENSOR_NOT_READY:
      Serial.print("Sensor not ready,\t");
      break;
    case DHTLIB_ERROR_BIT_SHIFT:
      Serial.print("Bit shift error,\t");
      break;
    default:
      Serial.print("Unknown: ");
      Serial.print(chk);
      Serial.print(",\t");
      break;
  }
  Serial.println();
  delay(100);
}


// -- END OF FILE --

