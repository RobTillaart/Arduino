//
//    FILE: Multiplex_softwareSerial_SDcard.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-06-13
//
// Needs to be tested with an SD card attached
// Note uses quite some RAM.


#include "Multiplex.h"
#include <SoftwareSerial.h>

//  SD CARD
#include <SPI.h>
#include <SD.h>
// SPI       PINS
// MOSI       11
// MISO       12
// CLOCK      13
// CS         10
#define CS                  10      // adjust this ChipSelect line if needed !

File logfile;

bool SDavailable = true;

// one multiplexer
Multiplex mp;


SoftwareSerial Serial_A(-1, 7);

//  SOME DUMMY TEXT
char str[] = "Lorem ipsum dolor sit amet, \
consectetuer adipiscing elit. Aenean commodo ligula eget dolor. \
Aenean massa. Cum sociis natoque penatibus et magnis dis parturient \
montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, \
pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. \
Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. \
In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. \
Nullam dictum felis eu pede mollis pretium. Integer tincidunt. \
Cras dapibus. Vivamus elementum semper nisi.";


////////////////////////////////////////////////////////////////////////


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);


  //  initialize the SD card
  if (!SD.begin(CS))
  {
    Serial.println(F("ERROR: SD card failure"));
    SDavailable = false;
  }

  if (SDavailable)
  {
    //  remove file
    SD.remove("data.txt");
    delay(1000);

    //  create new one
    logfile = SD.open("data.txt", FILE_WRITE);
    if (!logfile)
    {
      Serial.println(F("ERROR: SD card failure"));
    }
  }

  //  initialize SW serial
  Serial_A.begin(19200);

  // add both to the multiplexer.
  mp.add(&Serial_A);
  if (SDavailable) mp.add(&logfile);

  uint32_t start = micros();
  for (int i = 0; str[i] != 0; i++)
  {
    mp.print(str[i]);
  }
  mp.println("\nDone...\n");
  uint32_t stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  
  mp.flush();
}


void loop()
{
}


// -- END OF FILE --
