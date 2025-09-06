//
//    FILE: dhtint_getRaw.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DHTINT

//  DHT PIN layout from left to right
//  =================================
//  FRONT : DESCRIPTION
//  pin 1 : VCC
//  pin 2 : DATA
//  pin 3 : Not Connected
//  pin 4 : GND


#include "dhtint.h"

DHTINT mySensor(5);   //  ESP 16    UNO 5    MKR1010 5

uint32_t count = 0;
uint32_t start, stop;

uint32_t errors[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


void setup()
{
  while(!Serial);        //  MKR1010 needs this
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DHTINT_LIB_VERSION: ");
  Serial.println(DHTINT_LIB_VERSION);
  Serial.println();

  //  MKR1010 needs this
  //  mySensor.setDisableIRQ(false);
}


void loop()
{
  count++;
  //  show counters for OK and errors.
  if (count % 50 == 0)
  {
    Serial.println();
    Serial.println("OK \tCRC \tTOA \tTOB \tTOC \tTOD \tSNR \tBS \tWFR \tUNK");
    for (uint8_t i = 0; i < 10; i++)
    {
      Serial.print(errors[i]);
      Serial.print('\t');
    }
    Serial.println();
    Serial.println();
  }

  if (count % 10 == 0)
  {
    Serial.println();
    Serial.println("TIM\tCNT\tSTAT\tHUMI\tTEMP\tTIME\tTYPE");
  }
  Serial.print(millis());
  Serial.print("\t");
  Serial.print(count);
  Serial.print("\t");

  start = micros();
  int chk = mySensor.read();
  stop = micros();

  switch (chk)
  {
    case DHTLIB_OK:
      Serial.print("OK,\t");
      errors[0]++;
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("CRC,\t");
      errors[1]++;
      break;
    case DHTLIB_ERROR_TIMEOUT_A:
      Serial.print("TOA,\t");
      errors[2]++;
      break;
    case DHTLIB_ERROR_TIMEOUT_B:
      Serial.print("TOB,\t");
      errors[3]++;
      break;
    case DHTLIB_ERROR_TIMEOUT_C:
      Serial.print("TOC,\t");
      errors[4]++;
      break;
    case DHTLIB_ERROR_TIMEOUT_D:
      Serial.print("TOD,\t");
      errors[5]++;
      break;
    case DHTLIB_ERROR_SENSOR_NOT_READY:
      Serial.print("SNR,\t");
      errors[6]++;
      break;
    case DHTLIB_ERROR_BIT_SHIFT:
      Serial.print("BS,\t");
      errors[7]++;
      break;
    case DHTLIB_WAITING_FOR_READ:
      Serial.print("WFR,\t");
      errors[8]++;
      break;
    default:
      Serial.print("U");
      Serial.print(chk);
      Serial.print(",\t");
      errors[9]++;
      break;
  }

  //  DISPLAY DATA
  Serial.print(mySensor.getRawHumidity(), HEX);
  Serial.print(",\t");
  Serial.print(mySensor.getRawTemperature(), HEX);
  Serial.print(",\t");
  Serial.print(stop - start);
  Serial.print(",\t");
  Serial.println(mySensor.getType());

  delay(1000);
}


//  -- END OF FILE --

