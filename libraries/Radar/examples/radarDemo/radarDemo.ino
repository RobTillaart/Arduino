//
//    FILE: radarDemo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE:
//    DATE:
//     URL:
//
// Released to the public domain
//

#include "radar.h"

uint32_t del = 250;

RADAR radar(10, 11);

void setup()
{
  Serial.begin(115200);
  Serial.print("Start radarDemo, lib version: ");
  Serial.println(RADAR_LIB_VERSION);
  Serial.println();

  Serial.print(millis());
  Serial.println("\t1. home position");
  radar.setHomePosition(0, 0);
  radar.gotoHomePosition();
  wait();

  Serial.print(millis());
  Serial.println("\t2. gotoPan 20");
  radar.gotoPan(20);
  wait();
  Serial.println();

  Serial.print(millis());
  Serial.println("\t3. gotoTilt 60");
  radar.gotoTilt(60);
  wait();
  Serial.println();

  Serial.print(millis());
  Serial.println("\t4. gotoPanTilt 60 20");
  radar.gotoPanTilt(60, 20);
  wait();
  Serial.println();

  Serial.print(millis());
  Serial.println("\t5. home position");
  radar.gotoHomePosition();
  wait();
  Serial.println();

  Serial.print(millis());
  Serial.println("\t6. setPosition");
  for (int i = 0; i < 10; i++)
  {
    radar.setPosition(i, random(90), random(90));
  }
  Serial.println();

  Serial.print(millis());
  Serial.println("\t7. gotoPosition");
  for (int i = 0; i < 10; i++)
  {
    radar.gotoPosition(i);
    int p, t;
    radar.getPosition(i, &p, &t);
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
  Serial.print(millis());
  Serial.println("\t8. home position");
  radar.gotoHomePosition();
  wait();
  Serial.println();

  Serial.println();
  Serial.print(millis());
  Serial.println("\tdone...");
}

void loop()
{
}

void wait()
{
  do
  {
    int p = radar.getPan();
    int t = radar.getTilt();
    Serial.print(millis());
    Serial.print("\t*\t");
    Serial.print(p);
    Serial.print("\t");
    Serial.println(t);
    delay(del);
  }  while (radar.isMoving());
}
