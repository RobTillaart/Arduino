//
//    FILE: ansi_dht22.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ANSI


#include <dhtnew.h>
DHTNEW mySensor(5);   //  datapin  UNO 5  ESP 16  MKR1010 5


#include "ansi.h"
ANSI ansi(&Serial);


float t;
float h;



void setup()
{
  while (!Serial);    //  MKR1010 needs this
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DHTNEW_LIB_VERSION: \t");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.print("ANSI_LIB_VERSION: \t");
  Serial.println(ANSI_LIB_VERSION);
  Serial.println();

  mySensor.setType(22);

  //  SPLASH SCREEN
  ansi.clearScreen();
  ansi.gotoXY(10, 4);
  ansi.bold();
  ansi.print("DEMO DHT22 ON ANSI TERMINAL");
  ansi.normal();
  delay(5000);
}


void loop()
{
  int chk = mySensor.read();

  //  DISPLAY TEMPERATURE
  ansi.gotoXY(10, 6);
  ansi.print("TEMP:       ");
  ansi.gotoXY(16, 6);

  float t = mySensor.getTemperature();
  ansi.foreground(ansi.white);
  if (t > 25) ansi.foreground(ansi.yellow);
  if (t > 30) ansi.foreground(ansi.red);
  ansi.print(t, 1);

  //  DISPLAY HUMIDITY (dummy)
  ansi.gotoXY(10, 7);
  ansi.print(" HUM:       ");
  ansi.gotoXY(16, 7);
  
  float h = mySensor.getHumidity();
  ansi.foreground(ansi.white);
  if (h > 50) ansi.foreground(ansi.yellow);
  if (h > 70) ansi.foreground(ansi.red);
  ansi.print(h,1);

  delay(2000);
}


//  -- END OF FILE --
