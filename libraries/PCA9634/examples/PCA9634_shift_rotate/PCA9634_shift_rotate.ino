//
//    FILE: PCA9634_shift_rotate.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PCA9634 library
//     URL: https://github.com/RobTillaart/PCA9634


#include "PCA9634.h"


PCA9634 ledArray(0x20);

uint8_t arr[8];  //  working array
uint8_t channels = 8;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9634_LIB_VERSION: ");
  Serial.println(PCA9634_LIB_VERSION);
  Serial.println();

  Wire.begin();

  ledArray.begin();

  channels = ledArray.channelCount();
  //  test pulse per channel
  for (int channel = 0; channel < channels; channel++)
  {
    ledArray.setLedDriverMode(channel, PCA963X_LEDON);
    delay(200);
    ledArray.setLedDriverMode(channel, PCA963X_LEDOFF);
  }
  //  set all to PWM
  ledArray.setLedDriverMode(PCA963X_LEDPWM);


  initArray();
  ledArray.writeN(0, arr, channels);
  for (int i = 0; i < channels; i++)
  {
    delay(500);
    rotateLeft();
    ledArray.writeN(0, arr, channels);
  }
  for (int i = 0; i < channels; i++)
  {
    delay(500);
    shiftLeft(0);
    ledArray.writeN(0, arr, channels);
  }

  initArray();
  ledArray.writeN(0, arr, channels);
  for (int i = 0; i < channels; i++)
  {
    delay(500);
    rotateRight();
    ledArray.writeN(0, arr, channels);
  }
  for (int i = 0; i < channels; i++)
  {
    delay(500);
    shiftRight(0);
    ledArray.writeN(0, arr, channels);
  }
}


void loop()
{
}


void initArray()
{
  for (int i = 0; i < channels; i++)
  {
    arr[i] = i * 16 - 1;  //  0..255
  }
}


void shiftLeft(uint8_t newValue)
{
  for (int i = 0; i < channels - 1; i++)
  {
    arr[i] = arr[i + 1];
  }
  arr[channels - 1] = newValue;
}


void shiftRight(uint8_t newValue)
{
  for (int i = channels - 1; i > 0; i--)
  {
    arr[i] = arr[i - 1];
  }
  arr[0] = newValue;
}


void rotateLeft()
{
  shiftLeft(arr[0]);
}


void rotateRight()
{
  shiftRight(arr[channels - 1]);
}


//  -- END OF FILE --
