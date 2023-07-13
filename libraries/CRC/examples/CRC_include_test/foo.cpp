
#include "Arduino.h"
#include "foo.h"
#include "CrcFastReverse.h"

int foo(int n)
{
  return reverse8bits(n);
}
