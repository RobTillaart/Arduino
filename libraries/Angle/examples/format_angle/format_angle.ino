/*
 * Printing a formatted Angle example.
 *
 * Written by: Christopher Andrews (https://github.com/Chris--A)
 *
 * Licenced under MIT, free to use, blah blah...
 *
 * URL: https://github.com/RobTillaart/Angle
 */

#include <Angle.h>

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ANGLE_LIB_VERSION: ");
  Serial.println(ANGLE_LIB_VERSION);
  Serial.println();

  Angle angle( 23, 12, 10, 123 );

  Serial.println( angle );                  // Print the most verbose version ( same as angle.format(T) )
  Serial.println( "-------------------" );
  Serial.println( angle.format(D) );        // Print only degree value.
  Serial.println( angle.format(M) );        // Output includes minutes.
  Serial.println( angle.format(S) );        // Output includes minutes, seconds.
  Serial.println( angle.format(T) );        // Output includes minutes, seconds, tenthousands.
}

void loop() {}
