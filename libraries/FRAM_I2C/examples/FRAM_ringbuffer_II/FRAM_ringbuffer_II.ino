//
//    FILE: FRAM_ringbuffer_II.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo FRAM_RINGBUFFER class.
//     URL: https://github.com/RobTillaart/FRAM_I2C
//
//  playground with 2 ring-buffers 


#include "FRAM.h"
#include "FRAM_RINGBUFFER.h"


FRAM fram;
uint32_t sizeInBytes = 0;


FRAM_RINGBUFFER fb;
FRAM_RINGBUFFER fb2;

//  demo struct
struct record
{
  uint32_t time;
  float value;
} data;


///////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FRAM_LIB_VERSION: ");
  Serial.println(FRAM_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.print("INIT ERROR: ");
    Serial.println(rv);
  }

  //  get size in bytes
  sizeInBytes = fram.getSize() * 1024;
  Serial.print("FRAMSIZE:\t");
  Serial.println(sizeInBytes);

  //  clear FRAM optional
  //  for (uint32_t addr = 0; addr < sizeInBytes; addr += 4)
  //  {
  //    fram.write32(addr, 0);
  //  }

  //  initialize the two ring buffers.
  uint32_t nextAddr = fb.begin(&fram, 80, 0);
  nextAddr = fb2.begin(&fram, 80, nextAddr);
  Serial.print("NEXTADDR:\t");
  Serial.println(nextAddr);

  //  if you want to start VERY clean...
  //  fb.wipe();
  //  fb2.wipe();

  
  if (fb.load() == false)
  {
    Serial.println("FB.LOAD() FAILED.");
    //  clear the ring buffer when it could not be loaded from FRAM.
    fb.flush();

    //  only the first 10 will fit.
    for (int i = 0; i < 15; i++)
    {
      data.time = millis();
      data.value = sin(data.time / 1024.0);
      int rv = fb.write(data);

      Serial.print(data.time);
      Serial.print("\t");
      Serial.print(data.value, 4);
      Serial.print("\t");
      Serial.println(rv);

      delay(100);
    }
    //  make it persistent.
    fb.save();
  }

  while (!fb.empty())
  {
    fb.read(data);
    Serial.print("buf 1");
    Serial.print("\t");
    Serial.print(data.time);
    Serial.print("\t");
    Serial.println(data.value, 4);

    data.value *= 2;
    fb2.write(data);
  }

  while (!fb2.empty())
  {
    fb2.read(data);
    Serial.print("buf 2");
    Serial.print("\t");
    Serial.print(data.time);
    Serial.print("\t");
    Serial.println(data.value, 4);
  }

}


void loop()
{

}

///////////////////////////////////////////////////////

void dump()
{
  Serial.print("\n");
  Serial.print("SIZE:\t");
  Serial.println(fb.size());
  Serial.print("COUNT:\t");
  Serial.println(fb.count());
  Serial.print("FULL:\t");
  Serial.println(fb.full());
  Serial.print("EMPTY:\t");
  Serial.println(fb.empty());
  Serial.print("FREE:\t");
  Serial.println(fb.free());
  Serial.print("percent:\t");
  Serial.println(fb.freePercent(), 1);
}


void dump2()
{
  Serial.print("\n");
  Serial.print("SIZE:\t");
  Serial.println(fb2.size());
  Serial.print("COUNT:\t");
  Serial.println(fb2.count());
  Serial.print("FULL:\t");
  Serial.println(fb2.full());
  Serial.print("EMPTY:\t");
  Serial.println(fb2.empty());
  Serial.print("FREE:\t");
  Serial.println(fb2.free());
  Serial.print("percent:\t");
  Serial.println(fb2.freePercent(), 1);
}


//  -- END OF FILE --
