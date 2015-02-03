
//
//    FILE: dht21_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: DHT library test sketch for DHT21 && Arduino
//     URL:
//
// Released to the public domain
//

#include <dht.h>

dht DHT;

#define DHT21_PIN 5

void setup()
{
    Serial.begin(115200);
    Serial.println("DHT TEST PROGRAM ");
    Serial.print("LIBRARY VERSION: ");
    Serial.println(DHT_LIB_VERSION);
    Serial.println();
    Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

void loop()
{
    // READ DATA
    Serial.print("DHT21, \t");
    int chk = DHT.read21(DHT21_PIN);
    switch (chk)
    {
    case DHTLIB_OK:
        Serial.print("OK,\t");
        break;
    case DHTLIB_ERROR_CHECKSUM:
        Serial.print("Checksum error,\t");
        break;
    case DHTLIB_ERROR_TIMEOUT:
        Serial.print("Time out error,\t");
        break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    default:
        Serial.print("Unknown error,\t");
        break;
    }
    // DISPLAY DATA
    Serial.print(DHT.humidity, 1);
    Serial.print(",\t");
    Serial.println(DHT.temperature, 1);

    delay(2000);
}
//
// END OF FILE
//