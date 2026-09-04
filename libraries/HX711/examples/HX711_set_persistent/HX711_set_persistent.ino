//
//    FILE: HX711_set_persistent.ino
//  AUTHOR: Felix Moli Grao la base de Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711
//
//  Note RT: fixed issue #75, + minor edits
//
//  This example shows how the scale and offset could be stored in and
//  retrieved from the internal EEPROM of the MCU.
//  This code is not written to be optimal or perfect for all cases.
//
//  There are different ways to store the scale and offset.
//  In this example the data is stored always together as one struct.
//  In another application it might be better to be able to store
//  the values separately, or store them in an external EEPROM.
//  For that latter check e.g. https://github.com/RobTillaart/I2C_EEPROM


#include "HX711.h"
#include <EEPROM.h>


bool forced = false; // indicates that we want to enter calibration mode
HX711 scale;

//  adjust the pins if needed
const uint8_t buttonTare = 2;
const uint8_t dataPin = 6;
const uint8_t clockPin = 7;
//  const uint8_t dataPin  = 19;    //  for ESP32
//  const uint8_t clockPin = 18;    //  for ESP32


//  example values
//  scale.set_offset(-181815);
//  scale.set_scale(13.79);
struct Bascula {
  float scala;
  long offSet;
};

Bascula bascula;

//  messages can be commented if not needed
void SaveStruct(int eeAddress, Bascula bascula) {
  EEPROM.put(eeAddress, bascula);
  Serial.println( "Save custom object to EEPROM: " );
  Serial.println( bascula.scala );
  Serial.println( bascula.offSet );
}

//  messages can be commented if not needed
Bascula LoadStruct(int eeAddress) {
  EEPROM.get( eeAddress, bascula );
  Serial.println( "Read custom object from EEPROM: " );
  Serial.print("scale: "); Serial.println( bascula.scala );
  Serial.print("offset: "); Serial.println( bascula.offSet );
  return bascula;
  //  note RT: strange to return a global variable here,
  //           for demo it works and I leave it for now as is.
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HX711_LIB_VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  //  intialize the scale
  pinMode(buttonTare, INPUT_PULLUP);
  scale.begin(dataPin, clockPin);

  //  load values from EEPROM
  bascula = LoadStruct(0);

  //  if no stored values calibrate the scale.
  if ((bascula.scala == 0.00) || (bascula.offSet == 0) || (forced == true)) {

    Serial.print("UNITS: ");
    Serial.println(scale.get_units(10));

    Serial.println("\nEmpty the scale, press a key to continue");
    while (!Serial.available());
    while (Serial.available()) Serial.read();

    scale.tare();
    Serial.print("UNITS: ");
    bascula.offSet = scale.get_units(10);
    Serial.println(bascula.offSet);

    Serial.println("\nPut 1000 gram in the scale, press a key to continue");
    while (!Serial.available());
    while (Serial.available()) Serial.read();

    scale.calibrate_scale(1000, 5);
    Serial.print("UNITS: ");
    bascula.scala = scale.get_units(10);
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

    bascula.scala = scaleFactor;
    bascula.offSet = scaleOffset;
    SaveStruct( 0, bascula);  //  Save to EEPROM

  } else {

    Serial.println("The scale is calibrated... press to continue");
    while (!Serial.available());
    while (Serial.available()) Serial.read();

    //  use the values from EEPROM.
    scale.set_offset(bascula.offSet);
    scale.set_scale(bascula.scala);
  }
}


void loop()
{
  if (digitalRead(buttonTare) == false) {
    scale.tare();
    delay(500);
  }

  Serial.print("UNITS: ");
  Serial.println(scale.get_units(15));
  delay(250);
}
