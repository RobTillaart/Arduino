//
//    FILE: dht_tuning.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: DHT test sketch for DHT22 && Arduino => find minimum time between reads
//     URL:
//
// Released to the public domain
//

#include <dht.h>

dht DHT;

#define DHT22_PIN 2

void setup()
{
  Serial.begin(115200);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\t\tHumidity (%),\tTemperatur (C),\tT_Read (us)\tT_Cycle (us)\tT_Delay (us)");
}

int del = 500;
uint32_t startRead = 0;
uint32_t stopRead = 0;
uint32_t startCycle = 0;
uint32_t stopCycle = 0;
uint32_t tempCycle = 0;

void loop()
{
  while(del > 0){
    // READ DATA
    Serial.print("DHT22, \t");
    
    startRead = micros();
    int chk = DHT.read22(DHT22_PIN);
    stopRead = micros();

    switch (chk)
    {
    case DHTLIB_OK:
      Serial.print("OK,\t\t");
      del -= 10;
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out,\t");
      del += 10;
      break;
    case DHTLIB_ERROR_CONNECT:
      Serial.print("Connect,\t");
      break;
    case DHTLIB_ERROR_ACK_L:
      Serial.print("Ack Low,\t");
      break;
    case DHTLIB_ERROR_ACK_H:
      Serial.print("Ack High,\t");
      break;
    default:
      Serial.print("Unknown,\t");
      break;
    }
    // DISPLAY DATA
    Serial.print(DHT.humidity, 1);
    Serial.print(",\t\t");
    Serial.print(DHT.temperature, 1);
    Serial.print(",\t\t");
    Serial.print(stopRead - startRead);
    Serial.print(",\t\t");
    stopCycle = micros();
    tempCycle = micros();
    Serial.print(stopCycle - startCycle);
    startCycle = tempCycle;
    Serial.print(",\t\t");
    Serial.print(del);
    Serial.print("000");
    Serial.println();

    delay(del);
  }
  while(1);
}
//
// END OF FILE
//

