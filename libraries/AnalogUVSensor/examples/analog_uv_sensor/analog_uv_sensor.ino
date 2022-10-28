//
//    FILE: UV_sensor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-09-21

//  this example is not using the library,
//  sort of minimal version


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
}


void loop()
{
  Serial.println(indexUV(A0, 5.0, 1023));  //  assume UNO analogue port
  delay(1000);
}


float indexUV(uint16_t pin, int16_t analog_max, float voltage_max)
{
  uint16_t raw = analogRead(pin);
  float millivolt = (voltage_max * raw * 1000) / analog_max;

  if (millivolt < 50)
  {
    return 0.0;
  }
  if (millivolt < 227)
  {
    //  linear interpolation between 0..1
    float uvi = 0.0 + (millivolt - 50.0) / (227.0 - 50.0);
    return uvi;
  }
  //  linear interpolation between 1..11
  //  formula derived with spreadsheet.
  float uvi = 0.0104865310 * millivolt - 1.289154988;
  return uvi;
}


// -- END OF FILE --
