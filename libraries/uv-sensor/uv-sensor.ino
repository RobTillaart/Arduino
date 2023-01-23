//
//    FILE: UV_sensor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-09-21


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
}


void loop()
{
  Serial.println(indexUV(A0, 1023, 5.0));  //  assume UNO analog port
  delay(1000);
}


float indexUV(uint16_t pin, int16_t analog_max, float voltage_max)
{
  uint16_t raw = analogRead(pin);
  float millivolt = (voltage_max * raw * 1000) / analog_max;
  float uvi = 0.0;
  
  if (millivolt < 50)
  {
    return uvi;
  }
  if (millivolt < 227)
  {
    //  linear interpolation between 0..1
    uvi = (millivolt - 50) / (227 - 50);
    return uvi;
  }
  //  linear interpolation between 1..11
  //  formula derived with spreadsheet.
  uvi = 0.0104865310 * millivolt - 1.289154988;
  return uvi;
}


//  -- END OF FILE --

