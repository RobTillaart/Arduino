//
//    FILE: INA226_calibrate.ino
//  AUTHOR: Prashant Kumar
// PURPOSE: accurate calibration of shunt resistance, current zero offset, bus voltage scaling and full user control
//     url: https://github.com/pk17r/INA226


#include "INA226.h"


INA226 INA(0x40);


void setup()
{
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA226_LIB_VERSION: ");
  Serial.println(INA226_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }

  /* STEPS TO CALIBRATE INA226
   * 1. Set shunt equal to shunt resistance in ohms. This is the shunt resistance between IN+ and IN- pins of INA226 in your setup.
   * 2. Set current_LSB_mA (Current Least Significant Bit mA) equal to your desired least count resolution for IOUT in milli amps. Expected value to be in multiples of 0.050 o 0.010. Recommended values: 0.050, 0.100, 0.250, 0.500, 1, 2, 2.5 (in milli Ampere units).
   * 3. Set current_zero_offset_mA = 0, bus_V_scaling_e4 = 10000.
   * 4. Build firmware and flash microcontroller.
   * 5. Attach a power supply with voltage 5-10V to INA226 on VBUS/IN+ and GND pins, without any load.
   * 6. Start Serial Monitor and note Current values. Update current_zero_offset_mA = current_zero_offset_mA + average of 10 Current values in milli Amperes.
   * NOTE: Following adjustments shouldn't change values by more than 15-20%.
   * 7. Now measure Bus Voltage using a reliable Digital MultiMeter (DMM). Update bus_V_scaling_e4 = bus_V_scaling_e4 / (Displayed Bus Voltage on Serial Monitor) * (DMM Measured Bus Voltage). Can only be whole numbers.
   * 8. Now set DMM in current measurement mode. Use a resistor that will generate around 50-100mA IOUT measurement between IN- and GND pins with DMM in series with load. Note current measured on DMM.
   * 9. Update shunt = shunt * (Displayed IOUT on Serial Monitor) / (DMM Measured IOUT).
   * 10. Build firmware and flash microcontroller. Your INA 226 is now calibrated. It should have less than 1% error in Current and Voltage measurements over a wide range like [5mA, 1A] and [5V, 20V].
   */

  /* USER SET VALUES */

  float shunt = 0.020;                      /* shunt (Shunt Resistance in Ohms). Lower shunt gives higher accuracy but lower current measurement range. Recommended value 0.020 Ohm. Min 0.001 Ohm */
  float current_LSB_mA = 0.05;              /* current_LSB_mA (Current Least Significant Bit in milli Amperes). Recommended values: 0.050, 0.100, 0.250, 0.500, 1, 2, 2.5 (in milli Ampere units) */
  float current_zero_offset_mA = 0;         /* current_zero_offset_mA (Current Zero Offset in milli Amperes, default = 0) */
  uint16_t bus_V_scaling_e4 = 10000;        /* bus_V_scaling_e4 (Bus Voltage Scaling Factor, default = 10000) */

  if(INA.configure(shunt, current_LSB_mA, current_zero_offset_mA, bus_V_scaling_e4))
    Serial.println("\n***** Configuration Error! Chosen values outside range *****\n");
  else
    Serial.println("\n***** INA 226 CONFIGURE *****");
  Serial.print("Shunt:\t");
  Serial.print(shunt, 4);
  Serial.println(" Ohm");
  Serial.print("current_LSB_mA:\t");
  Serial.print(current_LSB_mA * 1e+3, 1);
  Serial.println(" uA / bit");
  Serial.print("\nMax Measurable Current:\t");
  Serial.print(INA.getMaxCurrent(), 3);
  Serial.println(" A");


  /* CALIBRATION */

  float bv = 0, cu = 0;
  for (int i = 0; i < 10; i++) {
    bv += INA.getBusVoltage();
    cu += INA.getCurrent_mA();
    delay(150);
  }
  bv /= 10;
  cu /= 10;
  Serial.println("\nAverage Bus and Current values for use in Shunt Resistance, Bus Voltage and Current Zero Offset calibration:");
  bv = 0;
  for (int i = 0; i < 10; i++) {
    bv += INA.getBusVoltage();
    delay(100);
  }
  bv /= 10;
  Serial.print("\nAverage of 10 Bus Voltage values = ");
  Serial.print(bv, 3);
  Serial.println("V");
  cu = 0;
  for (int i = 0; i < 10; i++) {
    cu += INA.getCurrent_mA();
    delay(100);
  }
  cu /= 10;
  Serial.print("Average of 10 Current values = ");
  Serial.print(cu, 3);
  Serial.println("mA");

  Serial.println("\nCALIBRATION VALUES TO USE:\t(DMM = Digital MultiMeter)");
  Serial.println("Step 5. Attach a power supply with voltage 5-10V to INA226 on VBUS/IN+ and GND pins, without any load.");
  Serial.print("\tcurrent_zero_offset_mA = ");
  Serial.print(current_zero_offset_mA + cu, 3);
  Serial.println("mA");
  if(cu > 5)
    Serial.println("********** NOTE: No resistive load needs to be present during current_zero_offset_mA calibration. **********");
  Serial.print("\tbus_V_scaling_e4 = ");
  Serial.print(bus_V_scaling_e4);
  Serial.print(" / ");
  Serial.print(bv, 3);
  Serial.println(" * (DMM Measured Bus Voltage)");
  Serial.println("Step 8. Set DMM in current measurement mode. Use a resistor that will generate around 50-100mA IOUT measurement between IN- and GND pins with DMM in series with load. Note current measured on DMM.");
  Serial.print("\tshunt = ");
  Serial.print(shunt);
  Serial.print(" * ");
  Serial.print(cu, 3);
  Serial.println(" / (DMM Measured IOUT)");
  if(cu < 40)
    Serial.println("********** NOTE: IOUT needs to be more than 50mA for better shunt resistance calibration. **********");
  delay(1000);

  /* MEASUREMENTS */

  Serial.println("\nBUS(V) SHUNT(mV) CURRENT(mA) POWER(mW)");
  for (int i = 0; i < 5; i++)
  {
    bv = INA.getBusVoltage();
    float sv = INA.getShuntVoltage_mV();
    cu = INA.getCurrent_mA();
    float po = (bv - sv / 1000) * cu;
    Serial.print(bv, 3);
    Serial.print("\t");
    Serial.print(sv, 3);
    Serial.print("\t\t");
    Serial.print(cu, 1);
    Serial.print("\t");
    Serial.print(po, 1);
    Serial.println();
    delay(1000);
  }
}

void loop()
{

}

//  -- END OF FILE --

