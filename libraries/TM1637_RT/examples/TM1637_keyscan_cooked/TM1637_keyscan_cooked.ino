//
//    FILE: TM1637_keypress_cooked.ino
//  AUTHOR: William F. Dudley Jr.
// PURPOSE: demo TM1637 library - keyScan() cooked output
//    DATE: 2021-10-26
//     URL: https://github.com/RobTillaart/TM1637


#include "TM1637.h"

TM1637 TM;


//  Note: In my experience, the TM1637 boards need a pull up
//  resistor from DIO to 3.3V for keyScan() to work.  1000 ohms
//  seems to work well, but value isn't critical.


char buff[8];
uint8_t last_keypress, bptr;


#define dispCLOCK   3
#define dispDATA    4



void setup()
{
  Serial.begin(115200);
  delay(200);
  Serial.print("\n");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.println(__TIME__);
  Serial.println(__FILE__);

  TM.begin(dispCLOCK, dispDATA);

  TM.setBrightness(1);
  TM.displayClear();
  bptr = 0;
  last_keypress = 0;
  memset(buff, '\0', sizeof(buff)/sizeof(char));
}


char button_poll(void) {
char c;
static unsigned long last_key_time;
  uint8_t keypress = TM.keyScan();
  c = '\0';
  //  TM.displayHex(keypress);        //  uncomment to see raw data on LED
  //  Serial.print("kp ");            //  uncomment to see raw
  //  Serial.println(keypress, HEX);  //  uncomment to see raw
  if(keypress < 0xfe) {
    if(last_keypress != keypress || (millis() - last_key_time) > 500) {
      last_keypress = keypress;
      last_key_time = millis();
      switch(keypress) {
        case 0xf4 :
          c = 'o';
          break;
        case 0xf3 :
          c = 'e';
          break;
        case 0xf5 :
          c = 'l';
          break;
        case 0xf0 :
          c = 'h';
          break;
      }
      if(c) {
        Serial.print(F("KEYPRESS "));
        Serial.print(keypress, HEX);
        Serial.print(F(" -> "));
        Serial.println(c);
        return c;
      }
    }
  }
  return '\0';
}


void ascii_to_7segment(char *buff, uint8_t *data) {
  for(int8_t i = 0, j=5 ; j > -1 && i < 12 && buff[i] ; i++) {
    if(isalpha(buff[i])) { buff[i] = tolower(buff[i]); }
    if(buff[i] >= '0' && buff[i] <= '9') {
      data[j--] = buff[i] - '0';
    }
    else if(buff[i] >= 'a' && buff[i] <= 'f') {
      data[j--] = buff[i] - 'a' + 10;
    }
    else if(buff[i] >= 'g' && buff[i] <= 'z') {
      data[j--] = buff[i] - 'g' + 18;
    }
    else if(buff[i] == '.') {
      data[j+1] |= 0x80;        //  decimal point on previous digit
    }
    else {
      data[j--] = 0x10;  //  blank
    }
  }
}


void loop()
{
uint8_t data[10];
char c;
  c = button_poll();
  if(c) {
    buff[bptr++] = c;
    if(bptr > 5) { bptr = 0; }
    Serial.println(buff);
    //  convert ASCII chars in "buff" to 7 segment representations in "data"
    ascii_to_7segment(buff, data);
    TM.displayRaw(data, -1);
  }
  delay(50);
}


//  -- END OF FILE --

