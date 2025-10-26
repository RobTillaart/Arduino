//
//    FILE: logicAnalyzer.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Very simple Arduino logicAnalyzer
//    DATE: 2025-10-20
//     URL: 
//
//

void setup()
{
  Serial.begin(500000);
  Serial.println(__FILE__);
  
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  
  pinMode(13, OUTPUT);   //  use built in LED as indicator
}

void loop()
{
  int a = digitalRead(8)  * 16 + 0;
  int b = digitalRead(9)  * 16 + 32;
  int c = digitalRead(10) * 16 + 64;
  int d = digitalRead(11) * 16 + 96;

  Serial.print(a);
  Serial.print('\t');
  Serial.print(b);
  Serial.print('\t');
  Serial.print(c);
  Serial.print('\t');
  Serial.print(d);
  Serial.print('\n');
}

//  -- END OF FILE --
