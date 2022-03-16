
//
//    FILE: HX_set_persistent.ino
//  AUTHOR: Felix Moli Grao la base de Rob Tillaart
// PURPOSE: HX711 demo


//scale.set_offset(-186985);
//scale.set_scale(14.18);


#include "HX711.h"
#include <EEPROM.h>


int eeAddress = 0;
#define EEPROM_SIZE 100


bool forced = false; // indicates that we want to enter calibration mode
HX711 scale;
byte buttonTare= 2;

uint8_t dataPin = 6;
uint8_t clockPin = 7;
//uint8_t dataPin  = 19;    // for esp32
//uint8_t clockPin = 18;    // for esp32

//scale.set_offset(-181815);
//scale.set_scale(13.79);
struct Bascula {
  float scala;
  long offSet;
};

Bascula bascula;

void SaveStruct(int eeAddress, Bascula bascula) {
  EEPROM.put(eeAddress, bascula);
  Serial.println( "Save custom object to EEPROM: " );
  Serial.println( bascula.scala );
  Serial.println( bascula.offSet );
}

Bascula LoadStruct(int eeAddress) {
  EEPROM.get( eeAddress, bascula );
  Serial.println( "Read custom object from EEPROM: " );
  Serial.print("scale: ");Serial.println( bascula.scala );
  Serial.print("offset: ");Serial.println( bascula.offSet );
  return bascula;
}


void setup()
{
  Serial.begin(115200);
  pinMode(buttonTare, INPUT_PULLUP);
  bascula = LoadStruct(0);//load off eeprom 

  scale.set_scale(bascula.scala); //read scale from eeprom position 0
  scale.set_offset(bascula.offSet); //read offSet from eeprom position 100
  scale.begin(dataPin, clockPin);// initiate communication

  if ((bascula.scala == 0.00) || (bascula.offSet == 0) || (forced == true)) {

    Serial.print("UNITS: ");
    Serial.println(scale.get_units(10));

    Serial.println("\nEmpty the scale, press a key to continue");
    while (!Serial.available());
    while (Serial.available()) Serial.read();

    scale.tare();
    Serial.print("UNITS: ");
    bascula.offSet=scale.get_units(10);
    Serial.println(bascula.offSet);


    Serial.println("\nPut 1000 gram in the scale, press a key to continue");
    while (!Serial.available());
    while (Serial.available()) Serial.read();

    scale.calibrate_scale(1000, 5);
    Serial.print("UNITS: ");
    bascula.scala=scale.get_units(10);
    Serial.println(bascula.scala);

    Serial.println("\nScale is calibrated, your calibration values:");

    long scaleOffset = scale.get_offset();
    Serial.print("\nOffset \t");
    Serial.println(scaleOffset);

    float scaleFactor = scale.get_scale();
    Serial.print("Scale \t");
    Serial.println(scaleFactor);

    Serial.println("\nUse this code for setting zero and calibration factor permanently:");

    Serial.print("\nscale.set_offset(");
    Serial.print(scaleOffset);
    Serial.println(");");
    Serial.print("scale.set_scale(");
    Serial.print(scaleFactor);
    Serial.println(");");

    Serial.println("\nPress a key to continue");
    while (!Serial.available());
    while (Serial.available()) Serial.read();

//scale.set_offset(-88627);
//scale.set_scale(101.05);

    bascula.scala=scaleFactor;
    bascula.offSet=scaleOffset; 
    SaveStruct( 0, bascula);//Save to eeprom 
  
  } else {
    Serial.println("The scale is calibrated... press to continue");
    while (!Serial.available());
    while (Serial.available()) Serial.read();
    scale.set_offset(bascula.offSet);
    scale.set_scale(bascula.scala);
  }
}


void loop()
{
  if (digitalRead(buttonTare)==false){
      scale.tare();
      delay(500);
       }

  Serial.print("UNITS: ");
  Serial.println(scale.get_units(15));
  delay(250);
}
