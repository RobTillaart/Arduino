//
//    FILE: generatorFreeWave.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo function generators
//     URL: https://github.com/RobTillaart/FunctionGenerator


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  Serial.println();

  Serial.println("int16_t arr[101] =\n{");
  for (int i = 0; i < 101; i++)
  {
    //  sin(t) + 0.25*sin(5t)
    float f = sin(i * 0.01 * 2 * PI);
    float g = sin(i * 0.05 * 2 * PI);
    int16_t v = 8000 * (f + 0.25 * g);
    Serial.print("");
    Serial.print(v);
    Serial.print(",");
    if (i > 0 and i % 5 == 0) Serial.println();
  }
  Serial.println("};");
}


void loop()
{
}


//  -- END OF FILE --
