//
//    FILE: DHT2pin.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: demo reading an DHT with 2 pins instead of 1
//    DATE: 2016 sep 5
//     URL: https://github.com/RobTillaart/DHT2pin
//          http://arduino.cc/playground/Main/DHTLib


#include <DHT2pin.h>

DHT2pin DHT(2, 3);

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
} counter = { 0, 0, 0, 0, 0, 0, 0, 0};


uint32_t start;
uint32_t stop;

void setup()
{
  DHT.begin();

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT2PIN_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)\tTime (us)");
}

void loop()
{
  // READ DATA
  Serial.print("DHT22, \t");

  uint32_t start = micros();
  int chk = DHT.read();
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
    case DHTLIB_ERROR_CONNECT:
      counter.connect++;
      Serial.print("Connect error,\t");
      break;
    case DHTLIB_ERROR_ACK_L:
      counter.ack_l++;
      Serial.print("Ack Low error,\t");
      break;
    case DHTLIB_ERROR_ACK_H:
      counter.ack_h++;
      Serial.print("Ack High error,\t");
      break;
    default:
      counter.unknown++;
      Serial.print("Unknown error,\t");
      break;
  }
  // DISPLAY DATA
  Serial.print(DHT.humidity(), 1);
  Serial.print(",\t");
  Serial.print(DHT.temperature(), 1);
  Serial.print(",\t");
  Serial.print(stop - start);
  Serial.println();

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


//  -- END OF FILE --

