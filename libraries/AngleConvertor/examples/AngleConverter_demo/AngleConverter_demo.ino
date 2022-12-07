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

  conv.setDegrees(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getDegrees(), 7);

  conv.setRadians(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getRadians(), 7);

  conv.setGradians(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getGradians(), 7);

  conv.setAngularMil(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getAngularMil(), 7);

  conv.setBinaryRadians(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getBinaryRadians(), 7);

  conv.setCentiTurn(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getCentiTurn(), 7);

  conv.setDiameterPart(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getDiameterPart(), 7);

  conv.setHexacontade(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getHexacontade(), 7);

  conv.setHourAngle(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getHourAngle(), 7);

  conv.setMilliTurn(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getMilliTurn(), 7);

  conv.setMinuteTime(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getMinuteTime(), 7);

  conv.setOctant(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getOctant(), 7);

  conv.setPechus(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getPechus(), 7);

  conv.setPoints(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getPoints(), 7);

  conv.setQuadrant(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getQuadrant(), 7);

  conv.setQuarterPoint(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getQuarterPoint(), 7);

  conv.setSecondsTime(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getSecondsTime(), 7);

  conv.setSextant(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getSextant(), 7);

  conv.setSign(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getSign(), 7);

  conv.setTurn(1.0);
  Serial.print(conv.getRadians(), 7);
  Serial.print("\t");
  Serial.println(conv.getTurn(), 7);

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
