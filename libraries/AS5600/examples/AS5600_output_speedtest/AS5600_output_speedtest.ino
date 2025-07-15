//
//    FILE: AS5600_output_speedtest.ino
//  AUTHOR: Pollyscracker
// PURPOSE: demo/testing
//     URL: https://github.com/RobTillaart/AS5600
//          https://forum.arduino.cc/t/questions-using-the-as5600-in-pwm-mode/1266957/12
//
//  Will not run on all boards,
//
//  Examples may use AS5600 or AS5600L devices.
//  Check if your sensor matches the one used in the example.
//  Optionally adjust the code.
//  (minor edits by Rob)


#include <Arduino.h>
#include <AS5600.h>
#include <Wire.h>


//  Uncomment the line according to your sensor type
AS5600L as5600;   //  use default Wire
// AS5600 as5600;   //  use default Wire


int iQueryN = 100;    // amount of times to request the angle per outputmode
// (minimum total process time per mode: iQueryN * delay(100)(at the end of the loop)
int Directionpin = 4; // sensor input, connect to dir of the sensor
int Analogpin = A7;   // sensor output, connect to both pins
int PWMpin = 7;       // sensor output, connect to both pins

// Set false if your microcontroller or setup works with 12Bit ADC conversion
// for use with Analog output only
bool b10BitADC = true;

bool bOutmodeAnalog = false;
bool bOutmodePWM = false;
bool bHighFreq = false;
bool bOutmodeReg = false;
bool bOutmodeRegRaw = false;
int iQcount = 0;
int iNmax = 0;
int iNmin = 0;
uint32_t ulStartTime = 0UL;
uint32_t ulTempTime = 0UL;
float fAngle = 0;
uint32_t ulAverageTime = 0;
uint32_t iLongest = 0;
uint32_t iShortest = 2147483647;

int32_t b = 0;


/*
  //  ERROR CODES
  const int     AS5600_OK                 = 0;
  const int     AS5600_ERROR_I2C_READ_0   = -100;
  const int     AS5600_ERROR_I2C_READ_1   = -101;
  const int     AS5600_ERROR_I2C_READ_2   = -102;
  const int     AS5600_ERROR_I2C_READ_3   = -103;
  const int     AS5600_ERROR_I2C_WRITE_0  = -200;
  const int     AS5600_ERROR_I2C_WRITE_1  = -201;
*/


void setup()
{
  while (!Serial);
  Serial.begin(460800);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);
  Serial.println();

  Wire.begin();

  as5600.begin();  //  set direction pin or leave blank when tied directly to gnd or vcc
  Serial.print("Error?:\t");
  Serial.println(as5600.lastError());
  delay(10);

  b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);
  if ( !b )
  {
    Serial.print("Encountered error connecting to as5600: \t");
    Serial.println(as5600.lastError());
  }
  as5600.setDirection(AS5600_CLOCK_WISE);  //  default, just be explicit. cw = dir->GND, ccw = dir->VCC
  as5600.setOutputMode(AS5600_OUTMODE_ANALOG_100);

  if (as5600.detectMagnet())
  {
    Serial.print("Magnet detected, AGC: ");
    Serial.print(as5600.readAGC());
    Serial.println("\t(Optimal value: 255/2 for 5V mcu's, 128/2 for 3V3 mcu's)");
  }
  else
  {
    if (as5600.magnetTooStrong())
    {
      Serial.println("Magnet to strong/close to sensor.");
    }
    if (as5600.magnetTooWeak())
    {
      Serial.println("Magnet to weak/far from sensor.");
    }
  }

  //////////////////////////////////////////////////////
  //
  // Configs that can influence the pull/call times
  //

  /*
    const uint8_t AS5600_POWERMODE_NOMINAL  = 0;
    const uint8_t AS5600_POWERMODE_LOW1     = 1;
    const uint8_t AS5600_POWERMODE_LOW2     = 2;
    const uint8_t AS5600_POWERMODE_LOW3     = 3;
  */
  as5600.setPowerMode(0);

  /*
    const uint8_t AS5600_HYST_OFF           = 0;
    const uint8_t AS5600_HYST_LSB1          = 1;
    const uint8_t AS5600_HYST_LSB2          = 2;
    const uint8_t AS5600_HYST_LSB3          = 3;
  */
  as5600.setHysteresis(2);

  /*
    const uint8_t AS5600_SLOW_FILT_16X      = 0;
    const uint8_t AS5600_SLOW_FILT_8X       = 1;
    const uint8_t AS5600_SLOW_FILT_4X       = 2;
    const uint8_t AS5600_SLOW_FILT_2X       = 3;
  */
  as5600.setSlowFilter(2);

  /*
    const uint8_t AS5600_FAST_FILT_NONE     = 0;
    const uint8_t AS5600_FAST_FILT_LSB6     = 1;
    const uint8_t AS5600_FAST_FILT_LSB7     = 2;
    const uint8_t AS5600_FAST_FILT_LSB9     = 3;
    const uint8_t AS5600_FAST_FILT_LSB18    = 4;
    const uint8_t AS5600_FAST_FILT_LSB21    = 5;
    const uint8_t AS5600_FAST_FILT_LSB24    = 6;
    const uint8_t AS5600_FAST_FILT_LSB10    = 7;
  */
  as5600.setFastFilter(2);

  delay(1000);
}


float measurePWMAngle()
{
  // wait for LOW
  while (digitalRead(PWMpin) == HIGH);
  // wait for HIGH
  while (digitalRead(PWMpin) == LOW);
  uint32_t rise = micros();

  // wait for LOW
  while (digitalRead(PWMpin) == HIGH);
  uint32_t highPeriod = micros() - rise;

  // wait for HIGH
  while (digitalRead(PWMpin) == LOW);
  uint32_t fullPeriod = micros() - rise;

  float bitTime = fullPeriod / 4351.0;
  float dataPeriod = highPeriod - 128 * bitTime;
  float angle = 360.0 * dataPeriod / (4095 * bitTime);
  return angle;
}


float measureAnalogAngle()
{
  float angle = 0.0;
  uint16_t rawangle = analogRead(Analogpin);
  if (b10BitADC) angle = 360.0 / 1023 * rawangle;
  else angle = 360.0 / 4095 * rawangle;
  return angle;
}


void loop()
{
  if ( !bOutmodeAnalog)
  {
    if (iQcount == 0)
    {
      as5600.setOutputMode(AS5600_OUTMODE_ANALOG_100);
      Serial.println("Starting analog timing..");
      delay(10);
    }
    if ( iQcount < iQueryN)
    {
      ulStartTime = micros();
      fAngle = measureAnalogAngle();
      ulTempTime = (micros() - ulStartTime);

      // Uncomment to see angle results per request
      /*
        Serial.print("[Analog] - ");
        Serial.print(iQcount);
        Serial.print("    \t");
        Serial.print(ulTempTime);
        Serial.print("µs to retrieve angle: ");
        Serial.print(fAngle);
        Serial.print("  \tangle in register: ");
        Serial.println(as5600.readAngle() * AS5600_RAW_TO_DEGREES);
      */

      if ( ulTempTime > iLongest )
      {
        iLongest = ulTempTime;
        iNmax++;
      }
      if ( ulTempTime < iShortest)
      {
        iShortest = ulTempTime;
        iNmin++;
      }
      ulAverageTime += ulTempTime;
      iQcount++;

      if ( iQcount == iQueryN )
      {
        ulAverageTime = ulAverageTime / iQcount;

        Serial.println();
        Serial.print("finished ANALOG ANGLE timing, avarage query time(µs): ");
        Serial.println(ulAverageTime);
        Serial.print("Fastest: ");
        Serial.print(iShortest);
        Serial.print(" (");
        Serial.print(iNmin);
        Serial.println(")");
        Serial.print("Slowest: ");
        Serial.print(iLongest);
        Serial.print(" (");
        Serial.print(iNmax);
        Serial.println(")");
        Serial.println();

        // Set output mode to PWM
        as5600.setOutputMode(AS5600_OUTMODE_PWM);
        as5600.setPWMFrequency(AS5600_PWM_115);
        bOutmodeAnalog = true;
        bOutmodePWM = false;
        bHighFreq = false;
        iQcount = 0;
        iShortest = 2147483647;
        iLongest = 0;
        iNmax = 0;
        iNmin = 0;
        ulAverageTime = 0UL;
      }
    }
  }
  else if (!bOutmodePWM)
  {
    if (iQcount == 0)
    {
      if ( !b )
      {
        Serial.print("Encountered error connecting to as5600: \t");
        Serial.println(as5600.lastError());
        Serial.println("as5600 not connected");

        //as5600.begin();
        b = as5600.isConnected();
        Serial.print("Connect: ");
        Serial.println(b);
        if (!b)
        {
          Serial.print("Failed to establish connection(check adress), error: \t");
          Serial.println(as5600.lastError());
        }
      }
      // Set output mode to PWM
      as5600.setOutputMode(AS5600_OUTMODE_PWM);
      if ( !bHighFreq )
      {
        as5600.setPWMFrequency(AS5600_PWM_115);
        Serial.println("Starting Low frequency(115) PWM timing..");
      }
      else
      {
        as5600.setPWMFrequency(AS5600_PWM_920);
        Serial.println("Starting High frequency(920) PWM timing..");
      }
      delay(10);
    }
    if ( iQcount < iQueryN)
    {
      //  uint16_t preAngle = as5600.readAngle();
      ulStartTime = micros();
      fAngle = measurePWMAngle();
      ulTempTime = (micros() - ulStartTime);

      // Uncomment to see angle results per request
      /*
        if(bHighFreq)
        {
          Serial.print("[PWM HIGH] - ");
          Serial.print(iQcount);
          Serial.print("  \t");
          Serial.print(ulTempTime);
          Serial.print("µs to retrieve angle: ");
          Serial.print(fAngle);
          Serial.print("   \tPRE-call angle from register: ");
          Serial.print(preAngle * AS5600_RAW_TO_DEGREES);
          Serial.print("\tPOST-call angle from register: ");
          Serial.println(as5600.readAngle() * AS5600_RAW_TO_DEGREES);
        }
        else
        {
          Serial.print("[PWM LOW] -  ");
          Serial.print(iQcount);
          Serial.print("  \t");
          Serial.print(ulTempTime);
          Serial.print("µs to retrieve angle: ");
          Serial.print(fAngle);
          Serial.print("   \tPRE-call angle from register: ");
          Serial.print(preAngle * AS5600_RAW_TO_DEGREES);
          Serial.print("\tPOST-call angle from register: ");
          Serial.println(as5600.readAngle() * AS5600_RAW_TO_DEGREES);
        }
      */
      if ( ulTempTime > iLongest )
      {
        iLongest = ulTempTime;
        iNmax++;
      }
      if ( ulTempTime < iShortest)
      {
        iShortest = ulTempTime;
        iNmin++;
      }
      ulAverageTime += ulTempTime;
      iQcount++;

      if ( iQcount == iQueryN )
      {
        ulAverageTime = ulAverageTime / iQcount;

        Serial.println();
        if ( !bHighFreq )
        {
          Serial.print("finished PWM ANGLE timing at lowest frequency (115Hz), avarage query time(µs): ");
          Serial.println(ulAverageTime);
          Serial.print("Fastest: ");
          Serial.print(iShortest);
          Serial.print(" (");
          Serial.print(iNmin);
          Serial.println(")");
          Serial.print("Slowest: ");
          Serial.print(iLongest);
          Serial.print(" (");
          Serial.print(iNmax);
          Serial.println(")");
          bHighFreq = true;
        }
        else
        {
          Serial.print("finished PWM ANGLE timing at highest frequency (920Hz), avarage query time(µs): ");
          Serial.println(ulAverageTime);
          Serial.print("Fastest: ");
          Serial.print(iShortest);
          Serial.print(" (");
          Serial.print(iNmin);
          Serial.println(")");
          Serial.print("Slowest: ");
          Serial.print(iLongest);
          Serial.print(" (");
          Serial.print(iNmax);
          Serial.println(")");
          bOutmodePWM = true;
          bOutmodeReg = false;
          bOutmodeRegRaw = false;
        }
        Serial.println();
        iQcount = 0;
        iShortest = 2147483647;
        iLongest = 0;
        ulAverageTime = 0UL;
        iNmax = 0;
        iNmin = 0;
      }

    }
  }
  else if (!bOutmodeRegRaw)
  {
    if ( iQcount == 0)
    {
      if (!bOutmodeReg)  Serial.println("Starting read angle register timing..");
      else Serial.println("Starting read RAW angle register timing..");
    }
    if ( iQcount < iQueryN)
    {
      if ( !bOutmodeReg )
      {
        ulStartTime = micros();
        fAngle = as5600.readAngle() * AS5600_RAW_TO_DEGREES;
      }
      else
      {
        ulStartTime = micros();
        fAngle = as5600.rawAngle() * AS5600_RAW_TO_DEGREES;
      }
      ulTempTime = (micros() - ulStartTime);

      // Uncomment to see angle results per request
      /*
        if(!bOutmodeReg)
        {
          Serial.print("[REGISTER] - ");
          Serial.print(iQcount);
          Serial.print(" \t");
          Serial.print(ulTempTime);
          Serial.print("µs to retrieve angle: ");
          Serial.print(fAngle);
          Serial.print("   \tPOST-call angle from register: ");
          Serial.println(as5600.readAngle() * AS5600_RAW_TO_DEGREES);
        }
        else
        {
          Serial.print("[RAW REGISTER] - ");
          Serial.print(iQcount);
          Serial.print(" \t");
          Serial.print(ulTempTime);
          Serial.print("µs to retrieve angle: ");
          Serial.print(fAngle);
          Serial.print("   \tPOST-call angle from register: ");
          Serial.println(as5600.readAngle() * AS5600_RAW_TO_DEGREES);
        }
      */

      if ( ulTempTime > iLongest )
      {
        iLongest = ulTempTime;
        iNmax++;
      }
      if ( ulTempTime < iShortest)
      {
        iShortest = ulTempTime;
        iNmin++;
      }
      ulAverageTime += ulTempTime;
      iQcount++;

      if ( iQcount == iQueryN )
      {
        ulAverageTime = ulAverageTime / iQcount;

        Serial.println();
        if ( !bOutmodeReg )
        {
          bOutmodeReg = true;
          Serial.print("finished register read ANGLE timing, avarage query time: ");
          Serial.println(ulAverageTime);
          Serial.print("Fastest: ");
          Serial.print(iShortest);
          Serial.print(" (");
          Serial.print(iNmin);
          Serial.println(")");
          Serial.print("Slowest: ");
          Serial.print(iLongest);
          Serial.print(" (");
          Serial.print(iNmax);
          Serial.println(")");
        }
        else if (!bOutmodeRegRaw)
        {
          bOutmodeRegRaw = true;
          Serial.print("finished register read RAW ANGLE timing, avarage query time: ");
          Serial.println(ulAverageTime);
          Serial.print("Fastest: ");
          Serial.print(iShortest);
          Serial.print(" (");
          Serial.print(iNmin);
          Serial.println(")");
          Serial.print("Slowest: ");
          Serial.print(iLongest);
          Serial.print(" (");
          Serial.print(iNmax);
          Serial.println(")");
          bOutmodeAnalog = false;
          bOutmodePWM = false;
          bHighFreq = false;
        }
        Serial.println();
        iQcount = 0;
        iShortest = 2147483647;
        iLongest = 0;
        ulAverageTime = 0UL;
        iNmax = 0;
        iNmin = 0;
      }
    }
  }
  delay(100);
}


//  ------
