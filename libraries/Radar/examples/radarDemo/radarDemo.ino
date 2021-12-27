//
//    FILE: radarDemo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of the radar library
//    DATE: 29-03-2015
//     URL: https://github.com/RobTillaart/RADAR


#include "radar.h"

uint32_t del = 150;

RADAR radar(10, 11);


void setup()
{
  Serial.begin(115200);
  Serial.print("Start radarDemo, lib version: ");
  Serial.println(RADAR_LIB_VERSION);
  Serial.println();

  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();

  gohome();
  Serial.println();
  Serial.print(millis());
  Serial.println("\tdone...");
}


void loop()
{
}


void test1()
{
  Serial.print(millis());
  Serial.println("\t1. home position");
  radar.setHomePosition(0, 0);
  radar.gotoHomePosition();
  wait();
}


void test2()
{
  Serial.print(millis());
  Serial.println("\t2. gotoPan 20");
  radar.gotoPan(20);
  wait();
  Serial.println();
}


void test3()
{
  Serial.print(millis());
  Serial.println("\t3. gotoTilt 60");
  radar.gotoTilt(60);
  wait();
  Serial.println();
}


void test4()
{
  Serial.print(millis());
  Serial.println("\t4. gotoPanTilt 60 20");
  radar.gotoPanTilt(60, 20);
  wait();
  Serial.println();
}


void test5()
{
  Serial.print(millis());
  Serial.println("\t5. home position");
  radar.gotoHomePosition();
  wait();
  Serial.println();
}


void test6()
{
  Serial.print(millis());
  Serial.println("\t6. setPosition");
  for (int i = 0; i < 10; i++)
  {
    radar.setPosition(i, random(90), random(90));
  }
  Serial.println();
}


void test7()
{
  Serial.print(millis());
  Serial.println("\t7. gotoPosition");
  for (int i = 0; i < 10; i++)
  {
    radar.gotoPosition(i);
    int16_t p, t;
    radar.getPosition(i, p, t);
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(i);
    Serial.print("\t");
    Serial.print(p);
    Serial.print("\t");
    Serial.println(t);

    wait();
    Serial.println();
  }
}


void gohome()
{
  Serial.print(millis());
  Serial.println("\tgo home position");
  radar.gotoHomePosition();
  wait();
  Serial.println();
}


void wait()
{
  Serial.println("\nTIME\t\tPAN\tTILT");
  do
  {
    Serial.print(millis());
    Serial.print("\t*\t");
    Serial.print(radar.getPan());
    Serial.print("\t");
    Serial.println(radar.getTilt());
    delay(del);
  }  while (radar.isMoving());
  Serial.print(millis());
  Serial.print("\t*\t");
  Serial.print(radar.getPan());
  Serial.print("\t");
  Serial.println(radar.getTilt());
}


// -- END OF FILE --
