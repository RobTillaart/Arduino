//
//    FILE: AngleConverter_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo sketch to test angleConvertor class
//    DATE: 2022-12-01
//     URL: https://github.com/RobTillaart/AngleConvertor
//


#include "AngleConvertor.h"

AngleConvertor conv;



void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ANGLECONVERTOR_LIB_VERSION: ");
  Serial.println(ANGLECONVERTOR_LIB_VERSION);
  Serial.println();

  //  if double = 8 bytes adjust #decimals
  uint8_t decimals = 6;
  if (sizeof(double) == 8) decimals = 12;

  // Serial.println("UNIT    \tDEGREES \tRADIANS \tUNIT");

  conv.setDegrees(1.0);
  Serial.print("Degrees \t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getDegrees(), decimals);

  conv.setRadians(1.0);
  Serial.print("Radians \t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getRadians(), decimals);

  conv.setGradians(1.0);
  Serial.print("Gradians\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getGradians(), decimals);

  conv.setAngularMil(1.0);
  Serial.print("AngularMil\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getAngularMil(), decimals);

  conv.setBinaryRadians(1.0);
  Serial.print("BinaryRadians\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getBinaryRadians(), decimals);

  conv.setCentiTurn(1.0);
  Serial.print("CentiTurn\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getCentiTurn(), decimals);

  conv.setDiameterPart(1.0);
  Serial.print("DiameterPart\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getDiameterPart(), decimals);

  conv.setHexacontade(1.0);
  Serial.print("Hexacontade\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getHexacontade(), decimals);

  conv.setHourAngle(1.0);
  Serial.print("HourAngle\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getHourAngle(), decimals);

  conv.setMilliRadians(1.0);
  Serial.print("MilliRadians\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getMilliRadians(), decimals);

  conv.setMilliTurn(1.0);
  Serial.print("MilliTurn\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getMilliTurn(), decimals);

  conv.setMinuteTime(1.0);
  Serial.print("MinuteTime\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getMinuteTime(), decimals);

  conv.setOctant(1.0);
  Serial.print("Octant  \t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getOctant(), decimals);

  conv.setPechus(1.0);
  Serial.print("Pechus  \t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getPechus(), decimals);

  conv.setPercent(1.0);
  Serial.print("Percent \t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getPercent(), decimals);

  conv.setPoints(1.0);
  Serial.print("Points  \t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getPoints(), decimals);

  conv.setQuadrant(1.0);
  Serial.print("Quadrant\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getQuadrant(), decimals);

  conv.setQuarterPoint(1.0);
  Serial.print("QuarterPoint\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getQuarterPoint(), decimals);

  conv.setSecondsTime(1.0);
  Serial.print("SecondsTime\t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getSecondsTime(), decimals);

  conv.setSextant(1.0);
  Serial.print("Sextant \t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getSextant(), decimals);

  conv.setSign(1.0);
  Serial.print("Sign    \t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getSign(), decimals);

  conv.setTurn(1.0);
  Serial.print("Turn    \t");
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getTurn(), decimals);

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
