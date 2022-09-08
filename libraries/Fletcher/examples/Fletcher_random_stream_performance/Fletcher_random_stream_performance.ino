/*
  Author: Daniel Mohr
  Date: 2022-09-07
  Purpose: shows stream performance
*/
#include "Arduino.h"

#include "printHelpers.h" // needed for Arduino Nano
#include <Fletcher16.h>
#include <Fletcher32.h>
#include <Fletcher64.h>

#ifdef ARDUINO_ARCH_AVR
#define MAX_LEN 1024
#else
#define MAX_LEN 16384
#endif

#define DO_N 23

void setup()
{
  Serial.begin(115200);
  while (!Serial);
}

void test_fletcher16() {
  Serial.println("Fletcher16");
  const uint16_t max_len = MAX_LEN;
  uint8_t values[max_len];
  uint32_t t0, t1;
  delay(100);
  t0 = micros();
  for (uint16_t i = 0; i < max_len; i++) {
    values[i] = (uint8_t) random(0, 1 << 8);
  }
  t1 = micros();
  Serial.print("Created random list: ");
  Serial.print(1024.0 * (t1 - t0) / float(MAX_LEN));
  Serial.println(" us/kByte.");
  Fletcher16 checksum_instance;
  uint16_t checksum;
  uint32_t totaltime = 0;
  for (uint16_t j = 0; j < DO_N; j++) {
    t0 = micros();
    checksum_instance.begin();
    for (uint16_t i = 0; i < max_len; i++) {
      checksum_instance.add(values[i]);
    }
    checksum = checksum_instance.getFletcher();
    t1 = micros();
    totaltime += t1 - t0;
  }
  Serial.print("Checksum: ");
  Serial.println(checksum);
  Serial.print("Created checksum: ");
  Serial.print(1024.0 * totaltime / float(DO_N * MAX_LEN));
  Serial.println(" us/kByte.");
}

void test_fletcher32() {
  Serial.println("Fletcher32");
  const uint16_t max_len = MAX_LEN / 2;
  uint16_t values[max_len];
  uint32_t t0, t1;
  delay(100);
  t0 = micros();
  for (uint16_t i = 0; i < max_len; i++) {
    values[i] = (uint16_t) random(0, ((uint32_t) 1) << 16);
  }
  t1 = micros();
  Serial.print("Created random list: ");
  Serial.print(1024.0 * (t1 - t0) / float(MAX_LEN));
  Serial.println(" us/kByte.");
  Fletcher32 checksum_instance;
  uint32_t checksum;
  uint32_t totaltime = 0;
  for (uint16_t j = 0; j < DO_N; j++) {
    t0 = micros();
    checksum_instance.begin();
    for (uint16_t i = 0; i < max_len; i++) {
      checksum_instance.add(values[i]);
    }
    checksum = checksum_instance.getFletcher();
    t1 = micros();
    totaltime += t1 - t0;
  }
  Serial.print("Checksum: ");
  Serial.println(checksum);
  Serial.print("Created checksum: ");
  Serial.print(1024.0 * totaltime / float(DO_N * MAX_LEN));
  Serial.println(" us/kByte.");
}

void test_fletcher64() {
  Serial.println("Fletcher64");
  const uint16_t max_len = MAX_LEN / 4;
  uint32_t values[max_len];
  uint32_t t0, t1;
  delay(100);
  t0 = micros();
  for (uint16_t i = 0; i < max_len; i++) {
    values[i] = ((uint32_t) random(0, ((uint32_t) 1) << 16)) + (((uint32_t) random(0, ((uint32_t) 1) << 16)) << 16);
  }
  t1 = micros();
  Serial.print("Created random list: ");
  Serial.print(1024.0 * (t1 - t0) / float(MAX_LEN));
  Serial.println(" us/kByte.");
  Fletcher64 checksum_instance;
  uint64_t checksum;
  uint32_t totaltime = 0;
  for (uint16_t j = 0; j < DO_N; j++) {
    t0 = micros();
    checksum_instance.begin();
    for (uint16_t i = 0; i < max_len; i++) {
      checksum_instance.add(values[i]);
    }
    checksum = checksum_instance.getFletcher();
    t1 = micros();
    totaltime += t1 - t0;
  }
  Serial.print("Checksum: ");
  Serial.println(print64(checksum));
  Serial.print("Created checksum: ");
  Serial.print(1024.0 * totaltime / float(DO_N * MAX_LEN));
  Serial.println(" us/kByte.");
}

void loop() {
  Serial.print("Using list of ");
  Serial.print(MAX_LEN);
  Serial.println(" elements for Fletcher16");
  Serial.print("Using list of ");
  Serial.print(MAX_LEN/2);
  Serial.println(" elements for Fletcher32");
  Serial.print("Using list of ");
  Serial.print(MAX_LEN/4);
  Serial.println(" elements for Fletcher64");
  Serial.println("");
  test_fletcher16();
  Serial.println("");
  delay(1000);
  test_fletcher32();
  Serial.println("");
  delay(1000);
  test_fletcher64();
  Serial.println("");
  delay(1000);
  Serial.println("");
}
