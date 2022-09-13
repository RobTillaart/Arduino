/*
  Author: Daniel Mohr
  Date: 2022-09-10
  Purpose: shows stream performance for different implementations
*/
#include "Arduino.h"
#include <stdio.h>

#include "printHelpers.h" // needed for Arduino Nano

#include "basic.h"
#include "Fletcher_v0.1.3.h"
#include "Fletcher_v0.1.4.h"
#include "Fletcher_v0.1.5.h"
#include "Fletcher_v0.1.6.h"
#include "Fletcher_next.h"
#include "Fletcher_if_statement.h"
#include "Fletcher_bit_shift.h"
#include "Fletcher_overflow.h"

#ifdef ARDUINO_ARCH_AVR
#define MAX_LEN 500
#else
#define MAX_LEN 16384
#endif
union main_value_storage {
  uint8_t uint8[MAX_LEN];
  uint16_t uint16[MAX_LEN/2];
  uint32_t uint32[MAX_LEN/4];
} values;

#define DO_N 23

#define n_implementations 9

uint16_t checksum16[n_implementations];
uint32_t checksum32[n_implementations];
uint64_t checksum64[n_implementations];
uint32_t totaltime16[n_implementations];
uint32_t totaltime32[n_implementations];
uint64_t totaltime64[n_implementations];
uint32_t n16 = 0;
uint32_t n32 = 0;
uint32_t n64 = 0;
bool checksum_correct16[n_implementations];
bool checksum_correct32[n_implementations];
bool checksum_correct64[n_implementations];

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

void test_fletcher16() {
  const size_t max_len = MAX_LEN;
  for (byte mode = 0; mode < 2; mode++) {
    for (size_t i = 0; i < max_len; i++) {
      if (mode == 0) {
        values.uint8[i] = (uint8_t) random(0, 1 << 8);
      } else {
        values.uint8[i] = (uint8_t) ((((uint16_t) 1) << 8) - 1);
      }
    }
    uint32_t t0, t1;
    for (uint16_t j = 0; j < DO_N; j++) {
      size_t index;
      /* reference */
      index = 0;
      t0 = micros();
      checksum16[index] = basic_fletcher16(values.uint8, max_len);
      t1 = micros();
      totaltime16[index] += t1 - t0;
      /* 0.1.3 */
      index = 1;
      t0 = micros();
      checksum16[index] = fletcher16_v0_1_3(values.uint8, max_len);
      t1 = micros();
      totaltime16[index] += t1 - t0;
      if (checksum16[index] != checksum16[0]) {
        checksum_correct16[index] = false;
      }
      /* 0.1.4 */
      index = 2;
      t0 = micros();
      checksum16[index] = fletcher16_v0_1_4(values.uint8, max_len);
      t1 = micros();
      totaltime16[index] += t1 - t0;
      if (checksum16[index] != checksum16[0]) {
        checksum_correct16[index] = false;
      }
      /* 0.1.5 */
      index = 3;
      t0 = micros();
      checksum16[index] = fletcher16_v0_1_5(values.uint8, max_len);
      t1 = micros();
      totaltime16[index] += t1 - t0;
      if (checksum16[index] != checksum16[0]) {
        checksum_correct16[index] = false;
      }
      /* 0.1.6 */
      index = 4;
      t0 = micros();
      checksum16[index] = fletcher16_v0_1_6(values.uint8, max_len);
      t1 = micros();
      totaltime16[index] += t1 - t0;
      if (checksum16[index] != checksum16[0]) {
        checksum_correct16[index] = false;
      }
      /* next */
      index = 5;
      t0 = micros();
      checksum16[index] = fletcher16_next(values.uint8, max_len);
      t1 = micros();
      totaltime16[index] += t1 - t0;
      if (checksum16[index] != checksum16[0]) {
        checksum_correct16[index] = false;
      }
      /* if_statement */
      index = 6;
      t0 = micros();
      checksum16[index] = fletcher16_if_statement(values.uint8, max_len);
      t1 = micros();
      totaltime16[index] += t1 - t0;
      if (checksum16[index] != checksum16[0]) {
        checksum_correct16[index] = false;
      }
      /* bit_shift */
      index = 7;
      t0 = micros();
      checksum16[index] = fletcher16_bit_shift(values.uint8, max_len);
      t1 = micros();
      totaltime16[index] += t1 - t0;
      if (checksum16[index] != checksum16[0]) {
        checksum_correct16[index] = false;
      }
    }
  }
  n16 += DO_N;
}

void test_fletcher32() {
  const size_t max_len = MAX_LEN / 2;
  for (byte m = 0; m < 2; m++) {
    for (size_t i = 0; i < max_len; i++) {
      if (m == 0) {
        values.uint16[i] = (uint16_t) random(0, ((uint32_t) 1) << 16);
      } else {
        values.uint16[i] = (uint16_t) ((((uint32_t) 1) << 16) - 1);
      }
    }
    uint32_t t0, t1;
    for (uint16_t j = 0; j < DO_N; j++) {
      size_t index;
      /* reference */
      index = 0;
      t0 = micros();
      checksum32[index] = basic_fletcher32(values.uint16, max_len);
      t1 = micros();
      totaltime32[index] += t1 - t0;
      /* 0.1.3 */
      index = 1;
      t0 = micros();
      checksum32[index] = fletcher32_v0_1_3(values.uint16, max_len);
      t1 = micros();
      totaltime32[index] += t1 - t0;
      if (checksum32[index] != checksum32[0]) {
        checksum_correct32[1] = false;
      }
      /* 0.1.4 */
      index = 2;
      t0 = micros();
      checksum32[index] = fletcher32_v0_1_4(values.uint16, max_len);
      t1 = micros();
      totaltime32[index] += t1 - t0;
      if (checksum32[index] != checksum32[0]) {
        checksum_correct32[1] = false;
      }
      /* 0.1.5 */
      index = 3;
      t0 = micros();
      checksum32[index] = fletcher32_v0_1_5(values.uint16, max_len);
      t1 = micros();
      totaltime32[index] += t1 - t0;
      if (checksum32[index] != checksum32[0]) {
        checksum_correct32[1] = false;
      }
      /* 0.1.6 */
      index = 4;
      t0 = micros();
      checksum32[index] = fletcher32_v0_1_6(values.uint16, max_len);
      t1 = micros();
      totaltime32[index] += t1 - t0;
      if (checksum32[index] != checksum32[0]) {
        checksum_correct32[1] = false;
      }
      /* next */
      index = 5;
      t0 = micros();
      checksum32[index] = fletcher32_next(values.uint16, max_len);
      t1 = micros();
      totaltime32[index] += t1 - t0;
      if (checksum32[index] != checksum32[0]) {
        checksum_correct32[1] = false;
      }
      /* if_statement */
      index = 6;
      t0 = micros();
      checksum32[index] = fletcher32_if_statement(values.uint16, max_len);
      t1 = micros();
      totaltime32[index] += t1 - t0;
      if (checksum32[index] != checksum32[0]) {
        checksum_correct32[1] = false;
      }
      /* bit_shift */
      index = 7;
      t0 = micros();
      checksum32[index] = fletcher32_bit_shift(values.uint16, max_len);
      t1 = micros();
      totaltime32[index] += t1 - t0;
      if (checksum32[index] != checksum32[0]) {
        checksum_correct32[1] = false;
      }
#ifdef ARDUINO_ARCH_AVR
      /* overflow */
      index = 8;
      t0 = micros();
      checksum32[index] = fletcher32_overflow(values.uint16, max_len);
      t1 = micros();
      totaltime32[index] += t1 - t0;
      if (checksum32[index] != checksum32[0]) {
        checksum_correct32[1] = false;
      }
#endif
    }
  }
  n32 += DO_N;
}

void test_fletcher64() {
  const size_t max_len = MAX_LEN / 4;
  for (byte m = 0; m < 2; m++) {
    for (size_t i = 0; i < max_len; i++) {
      if (m == 0) {
        values.uint32[i] = ((uint32_t) random(0, ((uint32_t) 1) << 16)) + (((uint32_t) random(0, ((uint32_t) 1) << 16)) << 16);
      } else {
        values.uint32[i] = (uint32_t) ((((uint64_t) 1) << 32) - 1);
      }
    }
    uint32_t t0, t1;
    for (uint16_t j = 0; j < DO_N; j++) {
      size_t index;
      /* reference */
      index = 0;
      t0 = micros();
      checksum64[index] = basic_fletcher64(values.uint32, max_len);
      t1 = micros();
      totaltime64[index] += t1 - t0;
      /* 0.1.3 */
      index = 1;
      t0 = micros();
      checksum64[index] = fletcher64_v0_1_3(values.uint32, max_len);
      t1 = micros();
      totaltime64[index] += t1 - t0;
      if (checksum64[index] != checksum64[0]) {
        checksum_correct64[1] = false;
      }
      /* 0.1.4 */
      index = 2;
      t0 = micros();
      checksum64[index] = fletcher64_v0_1_4(values.uint32, max_len);
      t1 = micros();
      totaltime64[index] += t1 - t0;
      if (checksum64[index] != checksum64[0]) {
        checksum_correct64[1] = false;
      }
      /* 0.1.5 */
      index = 3;
      t0 = micros();
      checksum64[index] = fletcher64_v0_1_5(values.uint32, max_len);
      t1 = micros();
      totaltime64[index] += t1 - t0;
      if (checksum64[index] != checksum64[0]) {
        checksum_correct64[1] = false;
      }
      /* 0.1.6 */
      index = 4;
      t0 = micros();
      checksum64[index] = fletcher64_v0_1_6(values.uint32, max_len);
      t1 = micros();
      totaltime64[index] += t1 - t0;
      if (checksum64[index] != checksum64[0]) {
        checksum_correct64[1] = false;
      }
      /* next */
      index = 5;
      t0 = micros();
      checksum64[index] = fletcher64_next(values.uint32, max_len);
      t1 = micros();
      totaltime64[index] += t1 - t0;
      if (checksum64[index] != checksum64[0]) {
        checksum_correct64[1] = false;
      }
      /* if_statement */
      index = 6;
      t0 = micros();
      checksum64[index] = fletcher64_if_statement(values.uint32, max_len);
      t1 = micros();
      totaltime64[index] += t1 - t0;
      if (checksum64[index] != checksum64[0]) {
        checksum_correct64[1] = false;
      }
      /* bit_shift */
      index = 7;
      t0 = micros();
      checksum64[index] = fletcher64_bit_shift(values.uint32, max_len);
      t1 = micros();
      totaltime64[index] += t1 - t0;
      if (checksum64[index] != checksum64[0]) {
        checksum_correct64[1] = false;
      }
      /* overflow */
      index = 8;
      t0 = micros();
      checksum64[index] = fletcher64_overflow(values.uint32, max_len);
      t1 = micros();
      totaltime64[index] += t1 - t0;
      if (checksum64[index] != checksum64[0]) {
        checksum_correct64[1] = false;
      }
    }
  }
  n64 += DO_N;
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  for (uint16_t i = 0; i < n_implementations; i++) {
    checksum16[i] = 0;
    checksum32[i] = 0;
    checksum64[i] = 0;
    totaltime16[i] = 0;
    totaltime32[i] = 0;
    totaltime64[i] = 0;
    checksum_correct16[i] = true;
    checksum_correct32[i] = true;
    checksum_correct64[i] = true;
  }
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
  test_fletcher16();
  test_fletcher32();
  test_fletcher64();
  // generate output
  Serial.println("data rate in us/kByte:");
  Serial.println("+------------+----------+----------+----------+----------+----------+----------+----------+----------+----------+");
  Serial.println("| alg        | basic    | 0.1.3    | 0.1.4    | 0.1.5    | 0.1.6    | next     | if       | shift    | overflow |");
  Serial.println("+------------+----------+----------+----------+----------+----------+----------+----------+----------+----------+");
  Serial.print("| fletcher16 | ");
  for (uint16_t i = 0; i < n_implementations; i++) {
    Serial.print(float2strn(1024.0 * totaltime16[i] / float(n16 * MAX_LEN), 8));
    Serial.print(" | ");
  }
  Serial.println("\n+------------+----------+----------+----------+----------+----------+----------+----------+----------+----------+");
  Serial.print("| fletcher32 | ");
  for (uint16_t i = 0; i < n_implementations; i++) {
    Serial.print(float2strn(1024.0 * totaltime32[i] / float(n32 * MAX_LEN), 8));
    Serial.print(" | ");
  }
  Serial.println("\n+------------+----------+----------+----------+----------+----------+----------+----------+----------+----------+");
  Serial.print("| fletcher64 | ");
  for (uint16_t i = 0; i < n_implementations; i++) {
    Serial.print(float2strn(1024.0 * totaltime64[i] / float(n64 * MAX_LEN), 8));
    Serial.print(" | ");
  }
  Serial.println("\n+------------+----------+----------+----------+----------+----------+----------+----------+----------+----------+\n");
  Serial.println("checksum always OK?");
  Serial.println("+------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+");
  Serial.println("| alg        | basic | 0.1.3 | 0.1.4 | 0.1.5 | 0.1.6 | next  | if    | shift | overf |");
  Serial.println("+------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+");
  Serial.print("| fletcher16 | ");
  for (uint16_t i = 0; i < n_implementations; i++) {
    if (checksum_correct16[i]) {
      Serial.print("     ");
    } else {
      Serial.print("fail ");
    }
    Serial.print(" | ");
  }
  Serial.println("\n+------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+");
  Serial.print("| fletcher32 | ");
  for (uint16_t i = 0; i < n_implementations; i++) {
    //Serial.print(checksum_correct32[i]);
    if (checksum_correct32[i]) {
      Serial.print("     ");
    } else {
      Serial.print("fail ");
    }
    Serial.print(" | ");
  }
  Serial.println("\n+------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+");
  Serial.print("| fletcher64 | ");
  for (uint16_t i = 0; i < n_implementations; i++) {
    //Serial.print(checksum_correct64[i]);
    if (checksum_correct64[i]) {
      Serial.print("     ");
    } else {
      Serial.print("fail ");
    }
    Serial.print(" | ");
  }
  Serial.println("\n+------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+\n");
  Serial.println("");
}
