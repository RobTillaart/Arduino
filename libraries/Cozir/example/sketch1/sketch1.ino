#include <cozir.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include <SoftwareSerial.h>
  SoftwareSerial nss(3,2);
#else
  #include <NewSoftSerial.h>
  NewSoftSerial nss(3,2);
#endif


COZIR czr(nss);

void setup()
{
  Serial.begin(9600);
  Serial.println("Setup");
  delay(1000);
}

void loop()
{
  Serial.println("Loop");
  float t = czr.Celsius();
  float f = czr.Fahrenheit();
  float h = czr.Humidity();
  uint16_t c = czr.CO2();
  
  Serial.print("Celcius = ");
  Serial.println(t);
  Serial.print("Fahrenheit = ");
  Serial.println(f);
  Serial.print("Humidity = ");
  Serial.println(h);
  Serial.print("CO2 = ");
  Serial.println(c);
  
  delay(3000);
}
