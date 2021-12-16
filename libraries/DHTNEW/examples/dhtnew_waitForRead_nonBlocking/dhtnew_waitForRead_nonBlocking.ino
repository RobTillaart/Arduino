//
//    FILE: dhtnew_waitForRead_nonBlocking.ino
//  AUTHOR: Budulinek
// PURPOSE: DHTNEW non-blocking wait for read example sketch for Arduino
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
  Serial.println("dhtnew_waitForRead_nonBlocking.ino");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();

  // MKR1010 needs this
  // mySensor.setDisableIRQ(false);

  Serial.println("This example shows how you can use the output of the read() function to implement non-blocking waiting for read.");
  Serial.println("In this example, Arduino continuously polls the read() function and returns fresh data (or an error) only when the read delay is over.");
  Serial.println("Infinite loop.");
  Serial.println();
  Serial.println("STAT\tHUMI\tTEMP\tTIME\tTYPE");
}


void loop()
{
  // READ DATA
  uint32_t start = micros();
  int chk = mySensor.read();
  uint32_t stop = micros();

  if (chk != DHTLIB_WAITING_FOR_READ) {
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

    // DISPLAY DATA
    Serial.print(mySensor.getHumidity(), 1);
    Serial.print(",\t");
    Serial.print(mySensor.getTemperature(), 1);
    Serial.print(",\t");
    uint32_t duration = stop - start;
    Serial.print(duration);
    Serial.print(",\t");
    Serial.println(mySensor.getType());
  }

  // do some other stuff
  delay(100);
}


// -- END OF FILE --

