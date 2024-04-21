//
//    FILE: I2C_eeprom_cyclic_store.ino
//  AUTHOR: Tomas Hübner
// VERSION: 1.0.0
// PURPOSE: Simple example of how to use cyclic storage.
//     URL: https://github.com/RobTillaart/I2C_EEPROM


#include <I2C_eeprom.h>
#include <I2C_eeprom_cyclic_store.h>

#define MEMORY_SIZE 8192      //  Total capacity of the EEPROM (8K == 8192 == 0x2000)
#define PAGE_SIZE 64          //  Size of write page of device, use datasheet to find!


struct SampleData {
public:
  uint32_t counter;
  //  Must use fixed length string, avoid using the String class.
  char message[32];
};


SampleData data;

I2C_eeprom ee(0x50, MEMORY_SIZE);
I2C_eeprom_cyclic_store<SampleData> cs;


void setup()
{
  Serial.begin(115200);
  while(!Serial);

  Wire.begin();

  ee.begin();

  cs.begin(ee, PAGE_SIZE, MEMORY_SIZE/PAGE_SIZE);

  if(!cs.read(data))
  {
    // The eeprom is uninitialized
    data.counter = 1;
    sprintf(data.message, "Initialized to %x", data.counter);
    cs.write(data);
  }

}

void loop()
{
  Serial.println(data.message);

  data.counter++;
  sprintf(data.message, "Written %x times", data.counter);
  cs.write(data);

  delay(10000);
}
