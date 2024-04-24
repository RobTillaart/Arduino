//
//    FILE: fractionExerciser.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo sketch for fraction math
//     URL: https://github.com/RobTillaart/Fraction


#include "fraction.h"


void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  Serial.print("\n\nStart fractionExcerciser: ");
  // Serial.println(FRACTION_LIB_VERSION);
  Serial.println();
  randomSeed(analogRead(A0) * 256 + analogRead(A1));
}


Fraction readFraction()
{
  int a = 0;
  int b = 0;

  while (Serial.available()) Serial.read();
  while (Serial.available() == 0);
  char c = Serial.read();
  while (c != '.' && c != '/')
  {
    a = a * 10 + c - '0';
    while (Serial.available() == 0);
    c = Serial.read();
  }
  while (Serial.available() == 0);
  c = Serial.read();
  while (c != '.')
  {
    b = b * 10 + c - '0';
    while (Serial.available() == 0);
    c = Serial.read();
  }
  Fraction fr(a, b);
  return fr;
}


char choice()
{
  while (Serial.available()) Serial.read();
  while (Serial.available() == 0);
  return Serial.read();
}


void loop()
{
  Serial.println("\n\n\which fractions exercise:");
  Serial.println("1: add ");
  Serial.println("2: subtract");
  Serial.println("3: multiply");
  Serial.println("4: divide");
  Serial.println("5: larger (>) or smaller (<)");
  Serial.println();

  int count = 0;
  switch (choice() - '0')
  {
    case 1: count = add(5); break;
    case 2: count = sub(5); break;
    case 3: count = mul(5); break;
    case 4: count = div(5); break;
    case 5: count = equ(5); break;
  }
  Serial.print("your score = ");
  Serial.println(count);
}


int add(int n)
{
  int count = 0;
  Serial.println("type n/m.");
  for (int i = 0; i < n; i++)
  {
    Fraction a(1 + random(9), 1 + random(9));
    Fraction b(1 + random(9), 1 + random(9));
    Serial.print(a.toString());
    Serial.print(" + ");
    Serial.print(b.toString());
    Serial.print(" = ");
    Fraction c = readFraction();
    Serial.print(c.toString());
    Serial.print("\t\t");
    Serial.println((a + b).toString());

    if (c == a + b ) count++;
  }
  return count;
}


int sub(int n)
{
  int count = 0;
  Serial.println("type n/m.");
  for (int i = 0; i < n; i++)
  {
    Fraction a(1 + random(9), 1 + random(9));
    Fraction b(1 + random(9), 1 + random(9));
    Serial.print(a.toString());
    Serial.print(" - ");
    Serial.print(b.toString());
    Serial.print(" = ");
    Fraction c = readFraction();
    Serial.print(c.toString());
    Serial.print("\t\t");
    Serial.println((a - b).toString());

    if (c == a - b ) count++;
  }
  return count;
}


int mul(int n)
{
  int count = 0;
  Serial.println("type n/m.");
  for (int i = 0; i < n; i++)
  {
    Fraction a(1 + random(9), 1 + random(9));
    Fraction b(1 + random(9), 1 + random(9));
    Serial.print(a.toString());
    Serial.print(" * ");
    Serial.print(b.toString());
    Serial.print(" = ");
    Fraction c = readFraction();
    Serial.print(c.toString());
    Serial.print("\t\t");
    Serial.println((a * b).toString());

    if (c == a * b ) count++;
  }
  return count;
}


int div(int n)
{
  int count = 0;
  Serial.println("type n/m.");
  for (int i = 0; i < n; i++)
  {
    Fraction a(1 + random(9), 1 + random(9));
    Fraction b(1 + random(9), 1 + random(9));
    Serial.print(a.toString());
    Serial.print(" / ");
    Serial.print(b.toString());
    Serial.print(" = ");
    Fraction c = readFraction();
    Serial.print(c.toString());
    Serial.print("\t\t");
    Serial.println((a / b).toString());

    if (c == a / b ) count++;
  }
  return count;
}


int equ(int n)
{
  int count = 0;
  Serial.println("press < = or > ");
  for (int i = 0; i < n; i++)
  {
    Fraction a(1 + random(9), 1 + random(9));
    Fraction b(1 + random(9), 1 + random(9));
    Serial.print(a.toString());
    Serial.print("\t?\t");
    Serial.print(b.toString());

    char c = choice();
    Serial.print("\t");
    Serial.println(c);

    if (c == '<' && a < b) count++;
    if (c == '=' && a == b) count++;
    if (c == '>' && a > b) count++;
  }
  return count;
}


//  -- END OF FILE --
