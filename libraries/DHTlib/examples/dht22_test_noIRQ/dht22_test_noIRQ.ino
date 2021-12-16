//
//    FILE: dht22_test_noIRQ.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DHT library test sketch for DHT22 && Arduino
//     URL: https://github.com/RobTillaart/DHTlib


#include <dht.h>

dht DHT;

#define DHT22_PIN 5


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
    uint32_t sumtime;
    uint32_t mintime;
} stat = { 0,0,0,0,0,0,0,0, 0, 9999};


void setup()
{
    Serial.begin(115200);
    Serial.println("dht22_test.ino");
    Serial.print("LIBRARY VERSION: ");
    Serial.println(DHT_LIB_VERSION);
    Serial.println();

    Serial.print("IRQ:\t");
    Serial.println( DHT.getDisableIRQ() );
    DHT.setDisableIRQ(true);
    Serial.print("IRQ:\t");
    Serial.println( DHT.getDisableIRQ() );

    Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)\tTime (us)");
}


void loop()
{
    // READ DATA
    Serial.print("DHT22, \t");

    uint32_t start = micros();
    int chk = DHT.read22(DHT22_PIN);
    uint32_t stop = micros();

    stat.total++;
    switch (chk)
    {
    case DHTLIB_OK:
        stat.ok++;
        Serial.print("OK,\t");
        break;
    case DHTLIB_ERROR_CHECKSUM:
        stat.crc_error++;
        Serial.print("Checksum error,\t");
        break;
    case DHTLIB_ERROR_TIMEOUT:
        stat.time_out++;
        Serial.print("Time out error,\t");
        break;
    case DHTLIB_ERROR_CONNECT:
        stat.connect++;
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        stat.ack_l++;
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        stat.ack_h++;
        Serial.print("Ack High error,\t");
        break;
    default:
        stat.unknown++;
        Serial.print("Unknown error,\t");
        break;
    }
    // DISPLAY DATA
    Serial.print(DHT.humidity, 1);
    Serial.print(",\t");
    Serial.print(DHT.temperature, 1);
    Serial.print(",\t");
    uint32_t duration = stop - start;
    stat.sumtime += duration;
    stat.mintime = min(stat.mintime, duration);
    Serial.print(duration);
    Serial.println();

    if (stat.total % 20 == 0)
    {
        Serial.println("\nTOT\tOK\tCRC\tTIMO\tCON\tACKL\tACKH\tAVG\MIN");
        Serial.print(stat.total);
        Serial.print("\t");
        Serial.print(stat.ok);
        Serial.print("\t");
        Serial.print(stat.crc_error);
        Serial.print("\t");
        Serial.print(stat.time_out);
        Serial.print("\t");
        Serial.print(stat.connect);
        Serial.print("\t");
        Serial.print(stat.ack_l);
        Serial.print("\t");
        Serial.print(stat.ack_h);
        Serial.print("\t");
        Serial.print(stat.unknown);
        Serial.print("\t");
        Serial.print(1.0 * stat.sumtime / stat.total);
        Serial.print("\t");
        Serial.print(1.0 * stat.mintime);
        Serial.println("\n");
    }
    delay(500);
}


// -- END OF FILE --

