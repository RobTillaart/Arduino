//
//    FILE: dhtnew_adaptive_delay.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: DHTNEW library test sketch for Arduino
//     URL: https://github.com/RobTillaart/DHTNew
//
// HISTORY:
// 0.1.0    2018-08-06 initial version
// 0.1.1    2020-04-30 replaced humidity and temperature with functions
// 0.1.2    2020-06-08 redid 0.1.1 testing and fix + improved error handling
// 0.1.3    2020-06-15 match 0.3.0 error handling
//
// DHT PIN layout from left to right
// =================================
// FRONT : DESCRIPTION  
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : Not Connected
// pin 4 : GND

// Note:
// Adaptive delay makes no sense anymore as the DHTNEW lib catches reads that
// are done faster than READ_DELAY apart (see dhtnew.cpp file).
// that said it is the goal to get this adaptibility into the library one day.
// A way to do this is to add a function auto_calibrate() that finds the timing
// where reading fails and use that value + safety margin (20%?)

#include <dhtnew.h>

DHTNEW mySensor(16);

void setup()
{
  Serial.begin(115200);
  Serial.println("dhtnew_adaptive_delay.ino");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();

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
  test();
}

void test()
{
  static uint16_t dht_delay = 600;
  // READ DATA
  uint32_t start = micros();
  int chk = mySensor.read();
  uint32_t stop = micros();

  switch (chk)
  {
    case DHTLIB_OK:
      Serial.print("OK,\t");
      dht_delay -= 10;
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      dht_delay += 10;
      break;
    case DHTLIB_ERROR_TIMEOUT_A:
      Serial.print("Time out A error,\t");
      dht_delay += 10;
      break;
    case DHTLIB_ERROR_TIMEOUT_B:
      Serial.print("Time out B error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT_C:
      Serial.print("Time out C error,\t");
      dht_delay += 10;
      break;
    case DHTLIB_ERROR_TIMEOUT_D:
      Serial.print("Time out D error,\t");
      dht_delay += 10;
      break;
    case DHTLIB_ERROR_SENSOR_NOT_READY:
      Serial.print("Sensor not ready,\t");
      dht_delay += 10;
      break;
    case DHTLIB_ERROR_BIT_SHIFT:
      Serial.print("Bit shift error,\t");
      dht_delay += 10;
      break;
    default:
      Serial.print("Unknown: ");
      Serial.print(chk);
      Serial.print(",\t");
      dht_delay += 100;
      break;
  }
  
  dht_delay = constrain(dht_delay, 100, 5000);
  // DISPLAY DATA
  Serial.print(mySensor.getHumidity(), 1);
  Serial.print(",\t");
  Serial.print(mySensor.getTemperature(), 1);
  Serial.print(",\t");
  uint32_t duration = stop - start;
  Serial.print(duration);
  Serial.print(",\t");
  Serial.print(mySensor.getType());
  Serial.print(",\t");
  Serial.println(dht_delay);
  delay(dht_delay);
}


// END OF FILE
