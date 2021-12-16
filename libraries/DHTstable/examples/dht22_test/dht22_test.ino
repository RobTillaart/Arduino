//
//    FILE: dht22_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DHT library test sketch for DHT22 && Arduino
//     URL: https://github.com/RobTillaart/DHTstable


#include "DHTStable.h"

DHTStable DHT;

#define DHT22_PIN       5


struct
{
    uint32_t total;
    uint32_t ok;
    uint32_t crc_error;
    uint32_t time_out;
    uint32_t connect;
    uint32_t ack_l;
    uint32_t ack_h;
    uint32_t unknown;
} counter = { 0,0,0,0,0,0,0,0};


void setup()
{
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.print("LIBRARY VERSION: ");
    Serial.println(DHTSTABLE_LIB_VERSION);
    Serial.println();
    Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)\tTime (us)");
}


void loop()
{
    // READ DATA
    Serial.print("DHT22, \t");

    uint32_t start = micros();
    int chk = DHT.read22(DHT22_PIN);
    uint32_t stop = micros();

    counter.total++;
    switch (chk)
    {
    case DHTLIB_OK:
        counter.ok++;
        Serial.print("OK,\t");
        break;
    case DHTLIB_ERROR_CHECKSUM:
        counter.crc_error++;
        Serial.print("Checksum error,\t");
        break;
    case DHTLIB_ERROR_TIMEOUT:
        counter.time_out++;
        Serial.print("Time out error,\t");
        break;
    default:
        counter.unknown++;
        Serial.print("Unknown error,\t");
        break;
    }

    // DISPLAY DATA
    Serial.print(DHT.getHumidity(), 1);
    Serial.print(",\t");
    Serial.print(DHT.getTemperature(), 1);
    Serial.print(",\t");
    Serial.print(stop - start);
    Serial.println();

    // DISPLAY COUNTERS
    if (counter.total % 20 == 0)
    {
        Serial.println("\nTOT\tOK\tCRC\tTO\tUNK");
        Serial.print(counter.total);
        Serial.print("\t");
        Serial.print(counter.ok);
        Serial.print("\t");
        Serial.print(counter.crc_error);
        Serial.print("\t");
        Serial.print(counter.time_out);
        Serial.print("\t");
        Serial.print(counter.connect);
        Serial.print("\t");
        Serial.print(counter.ack_l);
        Serial.print("\t");
        Serial.print(counter.ack_h);
        Serial.print("\t");
        Serial.print(counter.unknown);
        Serial.println("\n");
    }
    delay(2000);
}


// -- END OF FILE --

