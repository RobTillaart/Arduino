//
//    FILE: XMLBloodPressure.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple XML writer
//     URL: https://github.com/RobTillaart/XMLWriter


#include <XMLWriter.h>

//  BTX = BloodTestXML is no official standard afaik
XMLWriter BTX(&Serial);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("XMLWRITER_LIB_VERSION: ");
  Serial.println(XMLWRITER_LIB_VERSION);
  Serial.println();
  delay(100);

  uint32_t start = micros();
  BloodTest();
  uint32_t stop = micros();
  Serial.println();

  Serial.print("TIME: \t");
  Serial.println(stop - start);
}


void loop()
{
}


void BloodTest()
{
  BTX.setIndentSize(2);

  BTX.header();
  BTX.comment("XMLBloodPressure.ino\nThis is a demo of the XMLWriter lib for Arduino", MULTILINE); // == true (default == false)

  BTX.tagStart("btx");
  BTX.tagField("xmlns", "http://www.specifications.btx/BTX/1.0");  //  just a dummy
  BTX.tagEnd(NEWLINE, NOSLASH);
  {
    BTX.tagOpen("Document");
    {
      BTX.tagOpen("Patient");
      {
        BTX.writeNode("id", "314159265");
        BTX.writeNode("name", "John Doe");
      }
      BTX.tagClose();
      // should be a function
      BTX.tagOpen("Measurements", "2026");
      {
        BTX.tagOpen("Measurement", "2026-01-02");
        {
          BTX.writeNode("diastolic", "85");
          BTX.writeNode("systolic", "129");
          BTX.writeNode("stage", "0");
          BTX.writeNode("heartRateRest", "83");
          BTX.writeNode("O2-saturation", "100");
          BTX.writeNode("temperature", "36.9");
        }
        BTX.tagClose();
        BTX.tagOpen("Measurement", "2026-01-09");
        {
          BTX.writeNode("diastolic", "78");
          BTX.writeNode("systolic", "128");
          BTX.writeNode("stage", "0");
          BTX.writeNode("heartRateRest", "80");
          BTX.writeNode("O2-saturation", "100");
          BTX.writeNode("temperature", "36.9");
        }
        BTX.tagClose();
        BTX.tagOpen("Measurement", "2026-01-16");
        {
          BTX.writeNode("diastolic", "82");
          BTX.writeNode("systolic", "135");
          BTX.writeNode("stage", "1");
          BTX.writeNode("heartRateRest", "83");
          BTX.writeNode("O2-saturation", "100");
          BTX.writeNode("temperature", "36.9");
        }
        BTX.tagClose();
        BTX.tagOpen("Measurement", "2026-01-23");
        {
          BTX.writeNode("diastolic", "89");
          BTX.writeNode("systolic", "141");
          BTX.writeNode("stage", "2");
          BTX.writeNode("heartRateRest", "81");
          BTX.writeNode("O2-saturation", "98");
          BTX.writeNode("temperature", "37.1");
        }
        BTX.tagClose();
        BTX.tagOpen("Measurement", "2026-01-30");
        {
          BTX.writeNode("diastolic", "79");
          BTX.writeNode("systolic", "122");
          BTX.writeNode("stage", "0");
          BTX.writeNode("heartRateRest", "79");
          BTX.writeNode("O2-saturation", "98");
          BTX.writeNode("temperature", "37.0");
        }
        BTX.tagClose();
      }
      BTX.tagClose();  //  Measurements
    }
    BTX.tagClose();  //  Document
  }
  BTX.tagStart("/btx");
  BTX.tagEnd(NEWLINE, NOSLASH);
  BTX.flush();
}


// -- END OF FILE --
