//
//    FILE: dht22_in_function.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-02-19
// PURPOSE: show usage of DHT object in a function
//          based on issue #8
//     URL: https://github.com/RobTillaart/DHTlib


#include "dht.h"

#define DHTPIN 8


void printDHT(const uint8_t pin)   // uint8_t is an 8 bit unsigned integer
{
  // This command questions a DHT22 on a specific 'pin'.
  // on success, it prints  "OK;{temperature};{humidity};"
  // on error,   it prints  "ERR;DHTt;{errorCode};".
  //
  //    param 'pin': int
  //        The pin, where the DHT22 is connected.

  dht DHT;

  int chk = DHT.read22(pin);
  if (chk == DHTLIB_OK)
  {
    Serial.print("OK;");
    Serial.print(DHT.temperature);
    Serial.print(";");
    Serial.print(DHT.humidity);
    Serial.println(";");
    return;
  }

  Serial.print("ERR;DHTt;");
  switch (chk)
  {
    case DHTLIB_ERROR_CHECKSUM:
      Serial.println("CHSM;");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.println("TIMO");
      break;
    case DHTLIB_ERROR_CONNECT:
      Serial.println("NCNN");
      break;
    case DHTLIB_ERROR_ACK_L:
      Serial.println("ACKL");
      break;
    case DHTLIB_ERROR_ACK_H:
      Serial.println("ACKH");
      break;
    default:
      Serial.println("UNKN");
      break;
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println("\n");
}


void loop()
{
  static uint32_t lastTime = 0;     // holds its value after every iteration of loop
  if (millis() - lastTime >= 2000)  // print every 2000 milliseconds
  {
    lastTime = millis();
    printDHT(DHTPIN);
  }

  // add your other code here
}


// -- END OF FILE --

