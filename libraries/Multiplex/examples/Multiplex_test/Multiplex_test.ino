//
//    FILE: Multiplex_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-01-09


#include "Multiplex.h"


Multiplex mp;


class FakeStream : public Print
{
  public:
  FakeStream(uint8_t id) : _id(id) { _id = id; };

  virtual size_t write(uint8_t c) override
  {
    return Serial.write(c);
  };

  virtual size_t write(const uint8_t *buffer, size_t size)
  {
    size_t n = 0;
    n += Serial.print("stream");
    n += Serial.print(_id, DEC);
    n += Serial.print(':');

    for (uint8_t i = 0 ; i < size ; i++)
    {
      n += write(buffer[i]);
    }
    return n;
  }
  private:
  uint8_t _id = 0;
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  FakeStream stream1(1);
  FakeStream stream2(2);

  mp.add(&stream1);
  mp.print("one\n");
  mp.add(&stream2);
  mp.print("two\n");

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  mp.disable(1);
  mp.print("three\n");

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  mp.disable(0);
  mp.print("four\n");

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  mp.enable(0);
  mp.enable(1);
  mp.print("five\n");

  mp.disableStream(&stream1);
  mp.print("six\n");

  mp.enableStream(&stream1);
  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  mp.print("Done...\n");
}


void loop()
{
}


// -- END OF FILE --

