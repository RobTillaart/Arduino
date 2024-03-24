//
//    FILE: dhtnew_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DHTNEW library test sketch for Arduino
//     URL: https://github.com/RobTillaart/DHTNew

// 
// DHT PIN layout from left to right
// =================================
// FRONT : DESCRIPTION
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : Not Connected
// pin 4 : GND


#include <dhtnew.h>

DHTNEW kitchen(4);
DHTNEW living(5);
DHTNEW outside(6);

DHTNEW ar[3] = { kitchen, living, outside };


void setup()
{
  while(!Serial);        // MKR1010 needs this

  Serial.begin(115200);
  Serial.println("dhtnew_array.ino");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();

  // MKR1010 needs this
  // mySensor.setDisableIRQ(false);

  for (int idx = 0; idx < 3; idx++)
  {
    test(idx);
  }
}


void loop()
{
  for (int idx = 0; idx < 3; idx++)
  {
    test(idx);
  }
  Serial.println();
}


void test(int idx)
{
  //  READ DATA
  uint32_t start = micros();
  int chk = ar[idx].read();
  uint32_t stop = micros();

  Serial.print(idx);
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
    case DHTLIB_WAITING_FOR_READ:
      Serial.print("Waiting for read,\t");
      break;
    default:
      Serial.print("Unknown: ");
      Serial.print(chk);
      Serial.print(",\t");
      break;
  }

  //  DISPLAY DATA
  Serial.print(ar[idx].getHumidity(), 1);
  Serial.print(",\t");
  Serial.print(ar[idx].getTemperature(), 1);
  Serial.print(",\t");
  uint32_t duration = stop - start;
  Serial.print(duration);
  Serial.print(",\t");
  Serial.println(ar[idx].getType());
  delay(500);
}


//  -- END OF FILE --

