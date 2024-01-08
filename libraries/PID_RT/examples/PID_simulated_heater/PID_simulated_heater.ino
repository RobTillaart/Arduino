//
//    FILE: PID_simulated_heater.ino
//  AUTHOR: drf5n  (based on basic example)
// PURPOSE: demo
//
//  This simulates a 20W heater block driven by the PID
//  Wokwi https://wokwi.com/projects/356437164264235009
//
//  https://github.com/RobTillaart/PID_RT/issues/5


#include "PID_RT.h"

PID_RT PID;

const int PWM_PIN = 3;  // UNO PWM pin

int op = 0;
float input = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  PID.setPoint(125);
  PID.setOutputRange(0, 255);   //  PWM range
  PID.setInterval(50);
  PID.setK(2, 5, 1);
  PID.start();

  op = analogRead(A0);
}


void loop()
{
  float heaterWatts = ((int)op)*20.0/255;   //  20W heater
  float blockTemp = simPlant(heaterWatts);  //  simulate heating
  input = blockTemp;
  //  input = analogRead(A0);
  if (PID.compute(input))
  {
    op = PID.getOutput();
    analogWrite(PWM_PIN, op);

  //  Serial.print(PID.getInput());
  //  Serial.print('\t');
  //  Serial.println(op);
  }
  report();
}


void report(void){
  static uint32_t last = 0;
  const int interval = 1000;
  if (millis() - last > interval){
    last += interval;
//    Serial.print(millis()/1000.0);
    Serial.print(PID.getSetPoint());
    Serial.print(' ');
    Serial.print(input);
    Serial.print(' ');
    Serial.println(op);
  }
}

float simPlant(float Q){ // heat input in W (or J/s)
   //  simulate a 1x1x2cm aluminum block with a heater and passive ambient cooling
   //  next line "C is not used", fails in arduino-build-ci for ESP32
   //  float C = 237;  // W/mK thermal conduction coefficient for Al
   float h    = 5;    //  W/m2K thermal convection coefficient for Al passive
   float Cps  = 0.89; //  J/g°C
   float area = 1e-4; //  m2 area for convection
   float mass = 10;   // g
   float Tamb = 25;   // °C

   static float T       = Tamb;   //   °C
   static uint32_t last = 0;      //  last call
   uint32_t interval    = 100;    //  milliseconds

   if(millis() - last >= interval){
     last += interval;
     float Qconv =  (T - Tamb) * area * h;
     T = T + (Q - Qconv) * interval / 1000 / mass / Cps ;
   }
   return T;
}


//  -- END OF FILE --

