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
  Serial.println(__FILE__);
  Serial.print("lib version: ");
  Serial.println(ANGLECONVERTOR_LIB_VERSION);
  Serial.println();

  //  if double = 8 bytes adjust #decimals
  uint8_t decimals = 7;
  if (sizeof(double) == 8) decimals = 15;

  conv.setDegrees(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getDegrees(), decimals);

  conv.setRadians(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getRadians(), decimals);

  conv.setGradians(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getGradians(), decimals);

  conv.setAngularMil(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getAngularMil(), decimals);

  conv.setBinaryRadians(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getBinaryRadians(), decimals);

  conv.setCentiTurn(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getCentiTurn(), decimals);

  conv.setDiameterPart(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getDiameterPart(), decimals);

  conv.setHexacontade(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getHexacontade(), decimals);

  conv.setHourAngle(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getHourAngle(), decimals);

  conv.setMilliTurn(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getMilliTurn(), decimals);

  conv.setMinuteTime(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getMinuteTime(), decimals);

  conv.setOctant(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getOctant(), decimals);

  conv.setPechus(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getPechus(), decimals);

  conv.setPoints(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getPoints(), decimals);

  conv.setQuadrant(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getQuadrant(), decimals);

  conv.setQuarterPoint(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getQuarterPoint(), decimals);

  conv.setSecondsTime(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getSecondsTime(), decimals);

  conv.setSextant(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getSextant(), decimals);

  conv.setSign(1.0);
  Serial.print(conv.getDegrees(), decimals);
  Serial.print("\t");
  Serial.print(conv.getRadians(), decimals);
  Serial.print("\t");
  Serial.println(conv.getSign(), decimals);

  conv.setTurn(1.0);
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
