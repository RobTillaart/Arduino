//
//    FILE: map2colour_temperature.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: map2colour demo
//     URL: https://github.com/RobTillaart/map2colour


//  demo simulates a temperature sensor and its mapping upon colours
//  temp -20,    5,     10,     30,    35,    50,  200
//        Red  yellow  black   black  yellow  red  red
//  note that the middle area 10..30 has no colour (black).


#include "Arduino.h"
#include "map2colour.h"


map2colour mct;
map2colour mch;

//  should be in increasing order; and 7 elements
//  temperature
float Tvalues[7] = { -20, 5, 10, 30, 35, 50, 200 };
uint32_t Tcolours[7] =
{
  0x00FF0000, 0x00FFFF00, 0x00000000,
  0x00000000, 0x00FFFF00, 0x00FF0000,
  0x00FF0000
};

//  humidity  around 35 is perfect
float Hvalues[7] = { 0, 20, 30, 35, 40, 50, 100 };
uint32_t Hcolours[7] =
{
  M2C_RED, M2C_RED, M2C_YELLOW,
  M2C_LIME, M2C_YELLOW, M2C_RED,
  M2C_RED
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAP2COLOUR_LIB_VERSION: ");
  Serial.println(MAP2COLOUR_LIB_VERSION);
  Serial.println();

  mct.begin(Tvalues, Tcolours);
  mch.begin(Hvalues, Hcolours);

  for (int i = -20; i < 60; i++)
  {
    uint32_t rgb = mct.map2RGB(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(rgb, HEX);
  }
  Serial.println();

  for (int i = 20; i < 50; i++)
  {
    uint32_t rgb = mch.map2RGB(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(rgb, HEX);
  }
  Serial.println();

}


void loop()
{
  float temperature = analogRead(A0)/10;  //  add your sensor
  uint32_t rgb = mct.map2RGB(temperature);
  Serial.print("T: ");
  Serial.print(rgb, HEX);                 //  replace with PWM-RGB led 
  Serial.print("\t\t");
  
  float humidity = analogRead(A1)/10;     //  add your sensor
  rgb = mch.map2RGB(humidity);
  Serial.print("H: ");
  Serial.println(rgb, HEX);               //  replace with PWM-RGB led 
  delay(1000);
}


// -- END OF FILE --

