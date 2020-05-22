//
//    FILE: dhtnew_adaptive_delay.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: DHTNEW library test sketch for Arduino
//     URL: https://github.com/RobTillaart/DHTNew
// HISTORY:
//
// 0.1.0    2018-08-06 initial version
// 0.1.1    2020-04-30 replaced humidity and temperature with functions
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

}

void test()
{
  static uint16_t dht_delay = 1000;
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
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error,\t");
      dht_delay += 10;
      break;
    default:
      Serial.print("Unknown error,\t");
      dht_delay += 10;
      break;
  }
  
  dht_delay = constrain(dht_delay, 100, 5000);
  // DISPLAY DATA
  Serial.print(mySensor.humidity, 1);
  Serial.print(",\t");
  Serial.print(mySensor.temperature, 1);
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