//
//    FILE: INA229_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test - performance
//     URL: https://github.com/RobTillaart/INA229

#include "INA229.h"

//  select, dataIn, dataOut, clock == SOFTWARE SPI
INA229 INA(5, 6, 7, 8);
//  select, &SPI === HW SPI
// INA229 INA(9, &SPI);


uint32_t start, stop;
//  volatile, to prevent optimization
volatile float f;
volatile uint16_t value;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA229_LIB_VERSION: ");
  Serial.println(INA229_LIB_VERSION);
  Serial.println();

  SPI.begin();
  if (!INA.begin() )
  {
    Serial.println("Could not connect. Fix and Reboot");
    while (1);
  }

  INA.setMaxCurrentShunt(10, 0.0005);

  for (long speed = 1000000; speed <= 8000000; speed *= 2)
  {
    //  setup and measure
    INA.setSPIspeed(speed);
    Serial.println("\n========================================================");
    Serial.print("Speed: ");
    Serial.println(speed);
    delay(100);
    test_core();
    test_config();
    test_adc_config();
    test_others();
    test_thresholds();
  }

  Serial.print("\nDone");
}


void loop()
{
}


void test_core()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(100);


  start = micros();
  f = INA.getBusVoltage();
  stop = micros();
  Serial.print("getBusVoltage:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  f = INA.getShuntVoltage();
  stop = micros();
  Serial.print("getShuntVoltage:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  f = INA.getCurrent();
  stop = micros();
  Serial.print("getCurrent:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  f = INA.getPower();
  stop = micros();
  Serial.print("getPower:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  f = INA.getTemperature();
  stop = micros();
  Serial.print("getTemperature:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  f = INA.getEnergy();
  stop = micros();
  Serial.print("getEnergy:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  f = INA.getCharge();
  stop = micros();
  Serial.print("getCharge:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);
}


//  GETTERS ONLY TO NOT CORRUPT SENSOR.
void test_config()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(100);

  start = micros();
  value = INA.getAccumulation();
  stop = micros();
  Serial.print("getAccumulation:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getConversionDelay();
  stop = micros();
  Serial.print("getConversionDelay:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getTemperatureCompensation();
  stop = micros();
  Serial.print("getTemperatureCompensation:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getADCRange();
  stop = micros();
  Serial.print("getADCRange:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);
}


//  GETTERS ONLY TO NOT CORRUPT SENSOR.
void test_adc_config()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(100);

  start = micros();
  value = INA.getMode();
  stop = micros();
  Serial.print("getMode:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getBusVoltageConversionTime();
  stop = micros();
  Serial.print("getBusVoltageConversionTime:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getShuntVoltageConversionTime();
  stop = micros();
  Serial.print("getShuntVoltageConversionTime:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getTemperatureConversionTime();
  stop = micros();
  Serial.print("getTemperatureConversionTime:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getAverage();
  stop = micros();
  Serial.print("getAverage:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);
}


//  GETTERS ONLY TO NOT CORRUPT SENSOR.
void test_others()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(100);

  start = micros();
  value = INA.getShuntTemperatureCoefficent();
  stop = micros();
  Serial.print("getShuntTemperatureCoefficent:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getDiagnoseAlert();
  stop = micros();
  Serial.print("getDiagnoseAlert:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);
}


//  GETTERS ONLY TO NOT CORRUPT SENSOR.
void test_thresholds()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(100);

  start = micros();
  value = INA.getShuntOvervoltageTH();
  stop = micros();
  Serial.print("getShuntOvervoltageTH:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getShuntUndervoltageTH();
  stop = micros();
  Serial.print("getShuntUndervoltageTH:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getBusOvervoltageTH();
  stop = micros();
  Serial.print("getBusOvervoltageTH:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getBusUndervoltageTH();
  stop = micros();
  Serial.print("getBusUndervoltageTH:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getTemperatureOverLimitTH();
  stop = micros();
  Serial.print("getTemperatureOverLimitTH:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getPowerOverLimitTH();
  stop = micros();
  Serial.print("getPowerOverLimitTH:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);
}


//  GETTERS ONLY TO NOT CORRUPT SENSOR.
void test_manufactur_die()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(100);

  start = micros();
  value = INA.getManufacturer();
  stop = micros();
  Serial.print("getManufacturer:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getDieID();
  stop = micros();
  Serial.print("getDieID:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  value = INA.getRevision();
  stop = micros();
  Serial.print("getRevision:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(100);
}


//  -- END OF FILE --
