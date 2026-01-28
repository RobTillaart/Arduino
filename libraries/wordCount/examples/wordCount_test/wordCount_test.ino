//
//    FILE: wordCount_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
//     URL: https://github.com/RobTillaart/wordCount


#include "wordCount.h"

wordCount wc(&Serial);

char lorem[] = "Lorem ipsum dolor sit amet, \
consectetuer adipiscing elit. Aenean commodo ligula eget dolor. \
Aenean massa. Cum sociis natoque penatibus et magnis dis parturient \
montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, \
pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. \
Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. \
In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. \
Nullam dictum felis eu pede mollis pretium. Integer tincidunt. \
Cras dapibus. Vivamus elementum semper nisi. \
Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, \
consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, \
viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus \
varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies \
nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui.";


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("WORDCOUNT_LIB_VERSION: ");
  Serial.println(WORDCOUNT_LIB_VERSION);
  Serial.println();


  wc.println();
  Serial.println(wc.chars());
  Serial.println(wc.words());
  Serial.println(wc.lines());
  wc.reset();
  

  wc.println("Hello");
  Serial.println(wc.chars());
  Serial.println(wc.words());
  Serial.println(wc.lines());
  wc.reset();
  
  wc.println("Hello\nHello");
  Serial.println(wc.chars());
  Serial.println(wc.words());
  Serial.println(wc.lines());

  wc.println("Hello world from the Moon");
  wc.println("Hello world from Mars");
  Serial.println(wc.chars());
  Serial.println(wc.words());
  Serial.println(wc.lines());

  wc.println("Hello back from Earth");

  Serial.println(wc.chars());
  Serial.println(wc.words());
  Serial.println(wc.lines());

  wc.reset();
  wc.println(lorem);
  Serial.println(wc.chars());
  Serial.println(wc.words());
  Serial.println(wc.lines());

  wc.reset();
  wc.print("phone = 0123654789");
  Serial.println(wc.chars());
  Serial.println(wc.digits());

  Serial.println();
  wc.reset();
  wc.println(lorem);
  wc.println("\n\n\n");  //  just add dummy lines.
  Serial.print("BPS:\t");
  Serial.println(wc.Bps());
  Serial.print("kBPS:\t");
  Serial.println(wc.kBps());
  Serial.print("MBPS:\t");
  Serial.println(wc.MBps());
  Serial.print("WPS:\t");
  Serial.println(wc.wordsPerSecond());
  Serial.print("LPS:\t");
  Serial.println(wc.linesPerSecond());
  Serial.print("ACL:\t");
  Serial.println(wc.averageCharsPerLine());
}

void loop()
{
}


//  -- END OF FILE --
