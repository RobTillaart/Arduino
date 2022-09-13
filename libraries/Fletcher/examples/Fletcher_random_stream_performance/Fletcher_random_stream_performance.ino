/*
  Author: Daniel Mohr
  Date: 2022-09-13
  Purpose: shows stream performance
*/
#include "Arduino.h"

#include "printHelpers.h" // needed for Arduino Nano
#include <Fletcher16.h>
#include <Fletcher32.h>
#include <Fletcher64.h>
#include <Fletcher.h>

#ifdef ARDUINO_ARCH_AVR
#define MAX_LEN 1024
#else
#define MAX_LEN 16384
#endif
union main_value_storage {
  uint8_t uint8[MAX_LEN];
  uint16_t uint16[MAX_LEN / 2];
  uint32_t uint32[MAX_LEN / 4];
} values;

#define DO_N 23

#if defined(ARDUINO_ARCH_AVR)
String float2strn(float value, size_t n) {
  char strvalout[n];
  dtostrf(value, n, 2, strvalout);
  return strvalout;
}
#else
String float2strn(float value, size_t n) {
  String strval = String(value);
  while (strval.length() < n) {
    strval = " " + strval;
  }
  return strval;
}
#endif

uint16_t myfletcher16(uint8_t *data, const size_t length)
{
  uint8_t s1 = 0;
  uint8_t s2 = 0;
  for (size_t i = 0; i < length; i++)
  {
    // UINT8_MAX = 255 = ((((uint16_t) 1) << 8) - ((uint16_t) 1))
    s1 = (uint8_t) (((uint16_t) s1 + (uint16_t) data[i]) % UINT8_MAX);
    s2 = (uint8_t) (((uint16_t) s2 + (uint16_t) s1) % UINT8_MAX);
  }
  return (((uint16_t) s2) << 8) | ((uint16_t) s1);
}

uint32_t myfletcher32(uint16_t *data, const size_t length)
{
  uint16_t s1 = 0;
  uint16_t s2 = 0;
  for (size_t i = 0; i < length; i++)
  {
    // UINT16_MAX = 65535UL = ((((uint32_t) 1) << 16) - ((uint32_t) 1))
    s1 = (uint16_t) (((uint32_t) s1 + (uint32_t) data[i]) % UINT16_MAX);
    s2 = (uint16_t) (((uint32_t) s2 + (uint32_t) s1) % UINT16_MAX);
  }
  return (((uint32_t) s2) << 16) | ((uint32_t) s1);
}

uint64_t myfletcher64(uint32_t *data, const size_t length)
{
  uint32_t s1 = 0;
  uint32_t s2 = 0;
  for (size_t i = 0; i < length; i++)
  {
    // UINT32_MAX = 4294967295ULL = ((((uint64_t) 1) << 32) - ((uint64_t) 1))
    s1 = (uint32_t) (((uint64_t) s1 + (uint64_t) data[i]) % UINT32_MAX);
    s2 = (uint32_t) (((uint64_t) s2 + (uint64_t) s1) % UINT32_MAX);
  }
  return (((uint64_t) s2) << 32) | ((uint64_t) s1);
}

void test_fletcher16(const byte mode) {
  Serial.print("| Fletcher16 |   ");
  const uint16_t max_len = MAX_LEN;
  uint32_t t0, t1;
  delay(100);
  if (mode == 0) {
    t0 = micros();
    for (uint16_t i = 0; i < max_len; i++) {
      values.uint8[i] = (uint8_t) random(0, 1 << 8);
    }
    t1 = micros();
  } else {
    t0 = micros();
    for (uint16_t i = 0; i < max_len; i++) {
      values.uint8[i] = 255;
    }
    t1 = micros();
  }
  Serial.print(float2strn(1024.0 * (t1 - t0) / float(MAX_LEN), 8));
  Serial.print(" us/kByte |              ");
  Fletcher16 checksum_instance;
  uint16_t checksum;
  uint32_t totaltime = 0;
  for (uint16_t j = 0; j < DO_N; j++) {
    t0 = micros();
    checksum_instance.begin();
    for (uint16_t i = 0; i < max_len; i++) {
      checksum_instance.add(values.uint8[i]);
    }
    checksum = checksum_instance.getFletcher();
    t1 = micros();
    totaltime += t1 - t0;
  }
  uint16_t reference_checksum = myfletcher16(values.uint8, max_len);
  Serial.print(reference_checksum);
  Serial.print(" |                ");
  Serial.print(checksum);
  Serial.print(" | ");
  Serial.print(float2strn(1024.0 * totaltime / float(DO_N * MAX_LEN), 8));
  Serial.print(" us/kByte | ");
  if (reference_checksum == checksum) {
    Serial.print("   OK  ");
  } else {
    Serial.print(" ERROR ");
  }
  Serial.println(" |");
}

void test_fletcher32(const byte mode) {
  Serial.print("| Fletcher32 |   ");
  const uint16_t max_len = MAX_LEN / 2;
  uint32_t t0, t1;
  delay(100);
  if (mode == 0) {
    t0 = micros();
    for (uint16_t i = 0; i < max_len; i++) {
      values.uint16[i] = (uint16_t) random(0, ((uint32_t) 1) << 16);
    }
    t1 = micros();
  } else {
    t0 = micros();
    for (uint16_t i = 0; i < max_len; i++) {
      values.uint16[i] = 65535UL;
    }
    t1 = micros();
  }
  Serial.print(float2strn(1024.0 * (t1 - t0) / float(MAX_LEN), 8));
  Serial.print(" us/kByte |         ");
  Fletcher32 checksum_instance;
  uint32_t checksum;
  uint32_t totaltime = 0;
  for (uint16_t j = 0; j < DO_N; j++) {
    t0 = micros();
    checksum_instance.begin();
    for (uint16_t i = 0; i < max_len; i++) {
      checksum_instance.add(values.uint16[i]);
    }
    checksum = checksum_instance.getFletcher();
    t1 = micros();
    totaltime += t1 - t0;
  }
  uint32_t reference_checksum = myfletcher32(values.uint16, max_len);
  Serial.print(reference_checksum);
  Serial.print(" |           ");
  Serial.print(checksum);
  Serial.print(" | ");
  Serial.print(float2strn(1024.0 * totaltime / float(DO_N * MAX_LEN), 8));
  Serial.print(" us/kByte | ");
  if (reference_checksum == checksum) {
    Serial.print("   OK  ");
  } else {
    Serial.print(" ERROR ");
  }
  Serial.println(" |");
}

void test_fletcher64(const byte mode) {
  Serial.print("| Fletcher64 |   ");
  const uint16_t max_len = MAX_LEN / 4;
  uint32_t t0, t1;
  delay(100);
  if (mode == 0) {
    t0 = micros();
    for (uint16_t i = 0; i < max_len; i++) {
      values.uint32[i] = ((uint32_t) random(0, ((uint32_t) 1) << 16)) + (((uint32_t) random(0, ((uint32_t) 1) << 16)) << 16);
    }
    t1 = micros();
  } else {
    t0 = micros();
    for (uint16_t i = 0; i < max_len; i++) {
      values.uint32[i] = 4294967295ULL;
    }
    t1 = micros();
  }
  Serial.print(float2strn(1024.0 * (t1 - t0) / float(MAX_LEN), 8));
  Serial.print(" us/kByte |    ");
  Fletcher64 checksum_instance;
  uint64_t checksum;
  uint32_t totaltime = 0;
  for (uint16_t j = 0; j < DO_N; j++) {
    t0 = micros();
    checksum_instance.begin();
    for (uint16_t i = 0; i < max_len; i++) {
      checksum_instance.add(values.uint32[i]);
    }
    checksum = checksum_instance.getFletcher();
    t1 = micros();
    totaltime += t1 - t0;
  }
  uint64_t reference_checksum = myfletcher64(values.uint32, max_len);
  Serial.print(print64(reference_checksum));
  Serial.print(" | ");
  Serial.print(print64(checksum));
  Serial.print(" | ");
  Serial.print(float2strn(1024.0 * totaltime / float(DO_N * MAX_LEN), 8));
  Serial.print(" us/kByte | ");
  if (reference_checksum == checksum) {
    Serial.print("   OK  ");
  } else {
    Serial.print(" ERROR ");
  }
  Serial.println(" |");
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);
}

void loop() {
  Serial.print("Using list of ");
  Serial.print(MAX_LEN);
  Serial.println(" elements for Fletcher16");
  Serial.print("Using list of ");
  Serial.print(MAX_LEN / 2);
  Serial.println(" elements for Fletcher32");
  Serial.print("Using list of ");
  Serial.print(MAX_LEN / 4);
  Serial.println(" elements for Fletcher64");
  Serial.println("");
  Serial.println("+------------+---------------------+--------------------+----------------------+-------------------+---------+");
  Serial.println("| alg        | created random list | reference checksum | checksum             | datarate          | correct |");
  Serial.println("+------------+---------------------+--------------------+----------------------+-------------------+---------+");
  test_fletcher16(0);
  test_fletcher16(1);
  Serial.println("+------------+---------------------+--------------------+----------------------+-------------------+---------+");
  test_fletcher32(0);
  test_fletcher32(1);
  Serial.println("+------------+---------------------+--------------------+----------------------+-------------------+---------+");
  test_fletcher64(0);
  test_fletcher64(1);
  Serial.println("+------------+---------------------+--------------------+----------------------+-------------------+---------+");
  Serial.println("");
  delay(1000);
}
