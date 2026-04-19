#pragma once
//
//    FILE: geomath.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
//    DATE: 2015-07-18
// PURPOSE: Arduino library with geographic math functions
//     URL: https://github.com/RobTillaart/geomath


#include "Arduino.h"


#define GEOMATH_LIB_VERSION        (F("0.1.4"))

constexpr double GRAVITY_STANDARD = 9.80655;
constexpr double GRAVITY_EQUATOR  = 9.780327;
constexpr double GRAVITY_POLES    = 9.832185;


//  collection of Math with latitude  / longitude
//  use double for precision

/*

//  DISTANCE
double haverSine()
double fastHaverSine()
double radius(double lat, double radius);
double equator(double radius);
double angle(double radius, double distance);  //  angle between a person standing right in Iceland and Zambia

*/


//  REFERENCE
//  latitude in degrees.
//  altitude in meters relative to sea level.
float gravity(float latitude, float altitude = 0.0f)
{
  //  see example Estimate_gravity.ino
  //  https://en.wikipedia.org/wiki/Gravity_of_Earth
  //  Geodetic Reference System 1980
  float phi = latitude * (PI / 180.0f);
  float s1 = sin(phi) * sin(phi);
  float s2 = sin(2 * phi) * sin(2 * phi);
  float g = GRAVITY_EQUATOR * (1.0f + 0.0053024f * s1 - 0.0000058f * s2);
  
  if (altitude != 0.0f)
  {
    g -= (3.086E-6 * altitude);
  }
  return g;
}


float gravityFast(double latitude)
{
  //  see example Estimate_gravity.ino
  //  linear interpolation, very fast and relative error < 0.06%
  const float Gdelta = (GRAVITY_POLES - GRAVITY_EQUATOR) / 90.0f;
  float glinear = GRAVITY_EQUATOR + Gdelta * latitude;
  return glinear;

  //  first version, as assumed not linear.
  //  const float Gdelta = GRAVITY_POLES - GRAVITY_EQUATOR;
  //  float phi = latitude * (PI / 180.0f);
  //  float g = GRAVITY_EQUATOR + sin(phi) * Gdelta;
  //  return g;

  //  improved version - uses "weighted acceleration" due to rotation.
  //  const float Gaverage = (GRAVITY_POLES + GRAVITY_EQUATOR) / 2;
  //  const float Gdelta   = (GRAVITY_POLES - GRAVITY_EQUATOR) / 2;
  //  float phi = latitude * (PI / 180.0f);
  //  float g = Gaverage + Gdelta * (sin(phi2) - cos(phi2));
  //  return g;
}


double fastHaverSine(double lat1, double long1, double lat2, double  long2)
{
  //  assume the sphere has circumference 1 on the equator
  //  to keep the number in same order of magnitude
  //  helps to keep precision
  double dx = lat2 - lat1;
  double dy = (long2 - long1) * cos(lat2 * (PI / 180.0));
  double dist = sqrt(dx * dx + dy * dy);
  return dist * 111194.93;              //  correct for earth sizes ;)
}


double fastHaverSine2(double lat1, double long1, double lat2, double  long2)
{
  //  assume the sphere has circumference 1 on the equator
  //  to keep the number in same order of magnitude
  //  helps to keep precision
  double dx = lat2 - lat1;
  double dy = (long2 - long1) * cos(lat2 * (PI / 180.0));
  return hypot(dx, dy) * 111194.93;              //  correct for earth sizes ;)
}


double HaverSine(double lat1, double lon1, double lat2, double lon2)
{
  double ToRad = PI / 180.0;
  double R = 6371000;   //  radius earth in meter

  double dLat = (lat2 - lat1) * ToRad;
  double dLon = (lon2 - lon1) * ToRad;

  double a = sin(dLat / 2) * sin(dLat / 2) +
             cos(lat1 * ToRad) * cos(lat2 * ToRad) *
             sin(dLon / 2) * sin(dLon / 2);

  double c = 2 * atan2(sqrt(a), sqrt(1 - a));

  double d = R * c;
  return d;
}


/////////////////////////////////////////////////
//
//  SPHERE CLASS - should have two radii - equator vs poles
//
class sphere
{
public:
  sphere(float radius)
  {
    _radius = radius;
  }

  //  returns distance in same units as used in constructor.
  float circumference(float latitude)
  {
    return TWO_PI * _radius * cos(latitude * (PI / 180.0));
  }

  //  return degrees
  float angle(float distance)
  {
    float a = fmod(distance, _radius * TWO_PI) / _radius;
    return a * (180.0 / PI);
  }


private:
  float _radius;
  float _radius_twopi;  //  optimization.
};



//  -- END OF FILE --


