//
//    FILE: fastHaverSine.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: fastHaverSine is a faster function than haversine for short distances (< 1km).
//    DATE: 2015-07-18
//     URL: http://forum.arduino.cc/index.php?topic=336729


#define NUMTESTS 8

float ts[NUMTESTS][4] = {
  {50, 5, 51, 5},
  {50, 5, 50, 6},
  {50, 5, 50.1, 5},
  {50, 5, 50, 5.1},
  {50, 5, 50.1, 5.1},
  {50, 5, 50.01, 5.01},
  {50, 5, 50.001, 5.001},
  {50, 5, 50.0001, 5.0001},
};


uint32_t start;
uint32_t stop;


void setup()
{
  Serial.begin(115200);
  Serial.println("Start fastHaverSine()");

  start = micros();
  float d = HaverSine(50, 5, 50.01, 5.01);
  stop = micros();
  Serial.println("HAVERSINE");
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.print("DIST: ");
  Serial.println(d);

  start = micros();
  d = fastHaverSine(50, 5, 50.01, 5.01);
  stop = micros();
  Serial.println("\nFASTHAVERSINE");
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.print("DIST: ");
  Serial.println(d);

  start = micros();
  d = fastHaverSine2(50, 5, 50.01, 5.01);
  stop = micros();
  Serial.println("\nFASTHAVERSINE2");
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.print("DIST: ");
  Serial.println(d);

  for (int i = 0; i < NUMTESTS; i++)
  {
    Serial.print("\ntest: ");
    Serial.print(i);
    Serial.print("\t\t");
    for (int j = 0; j < 4; j++)
    {
      Serial.print("\t");
      Serial.print(ts[i][j], 1);
    }
    Serial.println();
    d = HaverSine(ts[i][0], ts[i][1], ts[i][2], ts[i][3]);
    Serial.println(d);
    d = fastHaverSine(ts[i][0], ts[i][1], ts[i][2], ts[i][3]);
    Serial.println(d);
  }

  Serial.println("\nrelative error map test\nLAT/LONG:\t45-50\nSTEPSIZE:\t0.2 degrees");
  float y = 45.0;
  while (y <= 50.0)
  {
    float x = 45.0;
    while (x <= 50.0)
    {
      float d1 = HaverSine(45.0, 45.0, x, y);
      float d2 = fastHaverSine(45.0, 45.0, x, y);
      float relError = 100.0 * abs(d2 - d1) / d1;
      Serial.print(relError, 3);
      Serial.print("\t");
      x += 0.2;
    }
    Serial.println();
    y += 0.2;
  }
  Serial.println();


  Serial.println("\nrelative error map test\nLAT/LONG:\t45-46\nSTEPSIZE:\t0.05 degrees");
  y = 45.0;
  while (y <= 46.0)
  {
    float x = 45.0;
    while (x <= 46.0)
    {
      float d1 = HaverSine(45.0, 45.0, x, y);
      float d2 = fastHaverSine(45.0, 45.0, x, y);
      float relError = 100.0 * abs(d2 - d1) / d1;
      Serial.print(relError, 3);
      Serial.print("\t");
      x += 0.05;
    }
    Serial.println();
    y += 0.05;
  }
  Serial.println();


  Serial.println("\nrelative error map test\nLAT/LONG:\t45-45.1\nSTEPSIZE:\t0.005 degrees");
  y = 45.0;
  while (y <= 45.1)
  {
    float x = 45.0;
    while (x <= 45.1)
    {
      float d1 = HaverSine(45.0, 45.0, x, y);
      float d2 = fastHaverSine(45.0, 45.0, x, y);
      float relError = 100.0 * abs(d2 - d1) / d1;
      Serial.print(relError, 3);
      Serial.print("\t");
      x += 0.005;
    }
    Serial.println();
    y += 0.005;
  }
  Serial.println();


  Serial.println("done...");
}

void loop()
{
}

double fastHaverSine(double lat1, double long1, double lat2, double  long2)
{
  // assume the sphere has circumference 1 on the equator
  // to keep the number in same order of magnitude
  // helps to keep precision
  double dx = lat2 - lat1;
  double dy = (long2 - long1) * cos(lat2 * (PI / 180.0));
  double dist = sqrt(dx * dx + dy * dy);
  return dist * 111194.93;              // correct for earth sizes ;)
}

double fastHaverSine2(double lat1, double long1, double lat2, double  long2)
{
  // assume the sphere has circumference 1 on the equator
  // to keep the number in same order of magnitude
  // helps to keep precision
  double dx = lat2 - lat1;
  double dy = (long2 - long1) * cos(lat2 * (PI / 180.0));
  return hypot(dx, dy) * 111194.93;              // correct for earth sizes ;)
}

double HaverSine(double lat1, double lon1, double lat2, double lon2)
{
  double ToRad = PI / 180.0;
  double R = 6371000;   // radius earth in meter

  double dLat = (lat2 - lat1) * ToRad;
  double dLon = (lon2 - lon1) * ToRad;

  double a = sin(dLat / 2) * sin(dLat / 2) +
             cos(lat1 * ToRad) * cos(lat2 * ToRad) *
             sin(dLon / 2) * sin(dLon / 2);

  double c = 2 * atan2(sqrt(a), sqrt(1 - a));

  double d = R * c;
  return d;
}


