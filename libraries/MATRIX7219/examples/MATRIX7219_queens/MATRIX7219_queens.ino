//
//    FILE: MATRIX7219_queens.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MATRIX7219 8x8 LED MATRIX MAX7219
//     URL: https://github.com/RobTillaart/MATRIX7219
//
//  this demo visualizes the eight queens problem
//

#include "MATRIX7219.h"

//  UNO
//uint8_t dataPin   = 2;
//uint8_t selectPin = 3;
//uint8_t clockPin  = 4;
//uint8_t count     = 1;

//  ESP32
uint8_t dataPin   = 21;
uint8_t selectPin = 22;
uint8_t clockPin  = 23;
uint8_t count     = 1;

MATRIX7219 mx(dataPin, selectPin, clockPin, count);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MATRIX7219_LIB_VERSION: ");
  Serial.println(MATRIX7219_LIB_VERSION);
  Serial.println();

  mx.begin();
  mx.clear();
  mx.setBrightness(3);
  mx.setReverse(true);

  brute_force_queens();
}


void loop()
{
}


//  8 queens brute force algorithm based upon
//  https://stackoverflow.com/questions/64235088/8-queens-brute-force-problem-is-not-printing-out-the-results-c


bool ok(uint8_t board[])
{
  //  for all queens
  for (uint8_t i = 0; i < 8; i++)
  {
    //  check the queens "below"
    for (uint8_t j = i + 1; j < 8; j++)
    {
      //  checks same row, up diagonal, down diagonal for other queens
      if (board[i] == board[j] || (j - i) == abs(board[j] - board[i]))
      {
        return false;
      }
    }
  }
  return true;
}


void printBoard(uint8_t board[], int count)
{
  Serial.print(millis());
  Serial.print("\tSolution: ");
  Serial.print(count);
  Serial.print("\t: ");
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print(board[i]);
    Serial.print(' ');
  }
  Serial.println();

  for (int n = 1; n < 9; n++)
  {
    mx.setRow(n, 1 << board[n - 1], 1);
  }
}


int brute_force_queens()
{
  uint8_t board[8];
  int count = 0;
  for (uint8_t i0 = 0; i0 < 8; i0 ++)
  {
    board[0] = i0;
    for (uint8_t i1 = 0; i1 < 8; i1 ++)
    {
      board[1] = i1;
      for (uint8_t i2 = 0; i2 < 8; i2 ++)
      {
        board[2] = i2;
        for (uint8_t i3 = 0; i3 < 8; i3 ++)
        {
          board[3] = i3;
          for (uint8_t i4 = 0; i4 < 8; i4 ++)
          {
            board[4] = i4;
            for (uint8_t i5 = 0; i5 < 8; i5 ++)
            {
              board[5] = i5;
              for (uint8_t i6 = 0; i6 < 8; i6 ++)
              {
                board[6] = i6;
                for (uint8_t i7 = 0; i7 < 8; i7 ++)
                {
                  board[7] = i7;

                  if (ok(board))
                  {
                    printBoard(board, ++count);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return count;
}


//  -- END OF FILE --

