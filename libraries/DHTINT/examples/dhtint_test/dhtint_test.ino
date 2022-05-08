//
//    FILE: dhtint_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DHTINT library test sketch for Arduino
//     URL: https://github.com/RobTillaart/DHTINT

// DHT PIN layout from left to right
// =================================
// FRONT : DESCRIPTION
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : Not Connected
// pin 4 : GND


#include <dhtint.h>

DHTINT mySensor(5);   // ESP 16    UNO 5    MKR1010 5


void setup()
{
  while(!Serial);        // MKR1010 needs this

  Serial.begin(115200);
  Serial.println("dhtint_test.ino");
  Serial.print("DHTINT_LIB_VERSION: ");
  Serial.println(DHTINT_LIB_VERSION);
  Serial.println();

  // MKR1010
  // mySensor.setDisableIRQ(false);

  Serial.println("\n1. Type detection test, first run might take longer to determine type");
  Serial.println("STAT\tHUMI\tTEMP\tTIME\tTYPE");
  test();
  test();
  test();
  test();

  Serial.println("\n2. Humidity offset test");
  Serial.println("STAT\tHUMI\tTEMP\tTIME\tTYPE");
  mySensor.setHumOffset(2.5);
  test();
  mySensor.setHumOffset(5.5);
  test();
  mySensor.setHumOffset(-5.5);
  test();
  mySensor.setHumOffset(0);
  test();

  Serial.println("\n3. Temperature offset test");
  Serial.println("STAT\tHUMI\tTEMP\tTIME\tTYPE");
  mySensor.setTempOffset(2.5);
  test();
  mySensor.setTempOffset(5.5);
  test();
  mySensor.setTempOffset(-5.5);
  test();
  mySensor.setTempOffset(0);
  test();

  Serial.println("\n4. LastRead test");
  mySensor.read();
  for (int i = 0; i < 20; i++)
  {
    if (millis() - mySensor.lastRead() > 1000)
    {
      mySensor.read();
      Serial.println("actual read");
    }
    Serial.print(mySensor.getHumidity(), 1);
    Serial.print(",\t");
    Serial.println(mySensor.getTemperature(), 1);
    delay(250);
  }

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
    case DHTLIB_WAITING_FOR_READ:
      Serial.print("Waiting for read,\t");
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
  delay(500);
}


// -- END OF FILE --

