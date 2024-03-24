//
//    FILE: dhtnew_endless_insideFunction.ino
// AUTHORS: Rob Tillaart, Vladislaw Kuzmin
// PURPOSE: Demonstration example of endless DHT values' reporting in a function
//    DATE: 2021-02-19
//    (c) : MIT

//  DHT PINs' layout from left to right
//  =================================
//  FRONT : DESCRIPTION
//  pin 1 : VCC
//  pin 2 : DATA
//  pin 3 : Not Connected
//  pin 4 : GND


#include <dhtnew.h>

uint64_t previousMillis;
uint32_t count = 0;
uint32_t start, stop;

uint32_t errors[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


void setup()
{
  while(!Serial);     //  MKR1010 needs this

  Serial.begin(115200);
  Serial.println("DHT_endless.ino");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();

  //  MKR1010 needs this
  //  mySensor.setDisableIRQ(false);

}


void DHTt(const uint8_t pin)
{
  if (millis() - previousMillis > 2000)
  {
    previousMillis = millis();
    DHTNEW mySensor(pin);

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
    Serial.print(mySensor.getHumidity(), 1);
    Serial.print(",\t");
    Serial.print(mySensor.getTemperature(), 1);
    Serial.print(",\t");
    Serial.print(stop - start);
    Serial.print(",\t");
    Serial.println(mySensor.getType());
  }
}


void loop()
{
  DHTt(2);
}


//  -- END OF FILE --


