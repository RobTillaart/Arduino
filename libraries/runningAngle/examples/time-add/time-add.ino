/*
   time-add.ino: Measure the average execution time of
   runningAngle::add().

   This test sketch feeds pseudo-random angles to runningAngle::add()
   in order to measure its average execution time in CPU cycles. The
   input angles are within 0..90 deg, which ensures there will be no
   wrapping. Wrapping would make the method slightly slower, but it is
   expected to be infrequent in typical use cases.

   This test is meant to run on AVR-based Arduinos only.
*/


#include <runningAngle.h>


// Uncomment the line below in order to do the computation in radians.
//#define USE_RADIANS

// We could test both angle units within the same code. Typical user
// code, however, is likely to use only a single unit, and this can
// enable some compiler optimizations. Choosing the unit at compile time
// gives the compiler the same optimization opportunities as in typical
// user code.
#ifdef USE_RADIANS
# define ANGLE_UNIT   RADIANS
# define ANGLE_SYMBOL "rad"
# define ANGLE_MAX    (PI/2)
#else
# define ANGLE_UNIT   DEGREES
# define ANGLE_SYMBOL "deg"
# define ANGLE_MAX    90.0
#endif


// Overhead of the timing code, in CPU cycles. This was found by
// disassembling and counting cycles.
const uint16_t timing_overhead = 8;

// Iterations for averaging the execution time.
const int iterations = 100;

// Prevent unwanted optimizations. This is most useful for preventing
// constant folding when feeding constants to the filter. It can also
// prevent instruction reordering that could move parts of the
// computation of the input angle within the timed portion of the code.
static float unoptimize(float x)
{
  volatile float y = x;
  return y;
}


runningAngle heading(runningAngle::ANGLE_UNIT);

void setup() {
  Serial.begin(9600);

  heading.setMode1();

  // Set Timer 1 to count in normal mode at the full CPU frequency.
  // The timer value, TCNT1, can then be used as a clock with
  // single-cycle resolution.
  TCCR1A = 0;
  TCCR1B = _BV(CS10);

  long total_time = 0;
  for (int i = 0; i <= iterations; i++) {
    float angle = (rand() + 0.5) / (RAND_MAX + 1.0) * ANGLE_MAX;
    angle = unoptimize(angle);

    // Timed part.
    uint16_t start_time = TCNT1;
    heading.add(angle);
    uint16_t end_time = TCNT1;

    // Do not use the time of the first execution of add(), as it
    // goes through a non typical and much shorter execution path.
    if (i != 0) {

      // Add the execution time of this iteration. Note that timer
      // rollover is not an issue as long as the timed code takes
      // less that 65536 cycles, and the timing computations are
      // performed in uint16_t, as this type rolls over in the
      // same manner as the timer itself.
      total_time += end_time - start_time - timing_overhead;
    }
  }

  // Use the resulting average. Otherwise the whole averaging code
  // could be optimized away.
  Serial.print("Average angle: ");
  Serial.print(heading.getAverage());
  Serial.println(" " ANGLE_SYMBOL);

  // Print the timing result.
  Serial.print("Average time: ");
  Serial.print((float) total_time / iterations);
  Serial.println(" CPU cycles");

  // This can be used to exit a simulation on simavr.
  Serial.flush();
  cli();
  asm("sleep");
}

void loop() {}
