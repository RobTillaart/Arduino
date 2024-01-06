//
//    FILE: TM1637_alpha.ino
//  AUTHOR: William F. Dudley Jr.
// PURPOSE: demo TM1637 library
//    DATE: 2021-10-12
//     URL: https://github.com/RobTillaart/TM1637


#include "TM1637.h"

TM1637 TM;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  TM.begin(2, 3);       //  clockPin, dataPin

  TM.setBrightness(2);
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
char buff[20];
uint8_t data[10];
  strcpy(buff, "hello ");
  Serial.println("hello");
  ascii_to_7segment(buff, data);
  TM.displayRaw(data, -1);
  delay(1000);
  TM.displayClear();
  delay(1000);
}


//  -- END OF FILE --

