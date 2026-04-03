//
//    FILE: SHT4x_advancedFunctions.ino
//  AUTHOR: Xorlent (https://github.com/Xorlent)
// PURPOSE: Auto mode functions for automatic heating and equilibrium detection
//     URL: https://github.com/RobTillaart/SHT4x
//
//  This file contains reusable functions that can be copied to your own project.
//  
//  Auto mode handles high-humidity conditions automatically:
//  - Measures initial conditions
//  - Applies intelligent heating if needed (based on temp/humidity)
//  - Waits for temperature equilibrium after heating
//  - Returns final temperature and humidity values
//
//  Usage:
//    1. Call requestAuto() to start measurement
//    2. Poll autoReady() until it returns true (at least every 50 ms)
//    3. Get results with getAutoTemperature() and getAutoHumidity()
//
//  Debug Output Control:
//    Define SHT4X_DEBUG as true in your sketch to enable debug serial output:
//      #define SHT4X_DEBUG true

//  Debug output macros
#if SHT4X_DEBUG
  #define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
  #define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#else
  #define DEBUG_PRINT(...)
  #define DEBUG_PRINTLN(...)
#endif

enum AutoState {
  AUTO_IDLE,
  AUTO_WAITING_HEATED,
  AUTO_EQUILIBRIUM_CHECK,
  AUTO_COMPLETE
};

/////////////////////////////////////////////////////////////////
//
//  STATE VARIABLES
//

AutoState autoState = AUTO_IDLE;
uint32_t autoStartTime;
uint32_t lastEquilibriumSample;
uint16_t equilibriumTimeout;
float dTthreshold;
bool needsHeating;

measType equilibriumMeasurementType;
float temperatureWindow[EQUILIBRIUM_WINDOW_SIZE];
uint8_t windowIndex;
uint8_t windowCount;
float originalTemperature;
float originalHumidity;

/////////////////////////////////////////////////////////////////
//
//  FUNCTIONS
//

//  Starts an automatic measurement cycle
//  Returns: true if started successfully, false on error
bool requestAuto(measType initialMeasurement, 
                 uint16_t timeout, 
                 float threshold)
{
  equilibriumTimeout = timeout;
  dTthreshold = threshold;
  autoState = AUTO_IDLE;
  
  DEBUG_PRINTLN("\n=== Starting Auto Mode ===");
  autoStartTime = millis();

  //  Take initial blocking measurement to assess conditions
  if (!sht.read(initialMeasurement, true))
  {
    DEBUG_PRINTLN("ERROR: Failed to read initial measurement");
    return false;
  }
  
  originalTemperature = sht.getTemperature();
  originalHumidity = sht.getHumidity();

  //  Decide if heated mode is needed
  measType heatedMode;
  needsHeating = false;
  
  if (originalTemperature < 55.0f && originalHumidity >= 85.0f) 
  {
    heatedMode = SHT4x_MEASUREMENT_LONG_HIGH_HEAT;
    needsHeating = true;
    DEBUG_PRINTLN("High humidity detected: Using HIGH heat (200mW, 1s)");
  } 
  else if (originalTemperature >= 55.0f && originalTemperature < 65.0f && originalHumidity >= 85.0f) 
  {
    heatedMode = SHT4x_MEASUREMENT_LONG_MEDIUM_HEAT;
    needsHeating = true;
    DEBUG_PRINTLN("High humidity detected: Using MEDIUM heat (110mW, 1s)");
  } 
  else if (originalTemperature < 65.0f && originalHumidity > 75.0f && originalHumidity < 85.0f) 
  {
    heatedMode = SHT4x_MEASUREMENT_LONG_LOW_HEAT;
    needsHeating = true;
    DEBUG_PRINTLN("Elevated humidity detected: Using LOW heat (20mW, 1s)");
  }
  
  if (!needsHeating)
  {
    autoState = AUTO_COMPLETE;
    return true;
  }
  
  //  Request async heated measurement
  DEBUG_PRINTLN("Requesting heated measurement...");
  if (!sht.requestData(heatedMode))
  {
    DEBUG_PRINTLN("ERROR: Failed to request heated measurement");
    return false;
  }

  equilibriumMeasurementType = initialMeasurement;
  autoState = AUTO_WAITING_HEATED;
  return true;
}


//  Check if auto measurement is complete
//  Returns: true when complete, false if still in progress
bool autoReady()
{
  if (autoState == AUTO_COMPLETE)
  {
    return true;
  }
  
  if (autoState == AUTO_IDLE)
  {
    return false;
  }
  
  //  Check for equalibrium timeout
  if ((millis() - autoStartTime) > equilibriumTimeout)
  {
    DEBUG_PRINTLN("TIMEOUT: Returning most recent values");
    autoState = AUTO_COMPLETE;
    return true;
  }
  
  if (autoState == AUTO_WAITING_HEATED)
  {
    if (sht.dataReady())
    {
      //  Read the heated measurement data
      if (!sht.readData(true))
      {
        DEBUG_PRINTLN("ERROR: Failed to read heated measurement");
        autoState = AUTO_COMPLETE;
        return true;
      }
      // Set sampled humidity from sensor
      DEBUG_PRINT("Heated measurement complete: ");
      DEBUG_PRINT(sht.getTemperature(), 2);
      DEBUG_PRINT("°C, ");
      DEBUG_PRINT(sht.getHumidity(), 1);
      DEBUG_PRINTLN("%RH");
      DEBUG_PRINTLN("Waiting for temperature equilibrium...");
      
      //  Initialize equilibrium checking state
      autoState = AUTO_EQUILIBRIUM_CHECK;
      lastEquilibriumSample = millis();
      windowIndex = 0;
      windowCount = 0;
      
      //  Start first equilibrium sample
      if (!sht.requestData(equilibriumMeasurementType))
      {
        DEBUG_PRINTLN("ERROR: Failed to request equilibrium measurement");
        autoState = AUTO_COMPLETE;
        return true;
      }
    }
    return false;
  }
  
  if (autoState == AUTO_EQUILIBRIUM_CHECK)
  {
    //  Check if it's time to read next sample (250ms interval)
    if ((millis() - lastEquilibriumSample) >= 250)
    {
      if (sht.dataReady())
      {
        //  Read the data
        if (!sht.readData(true))
        {
          DEBUG_PRINTLN("ERROR: Failed to read equilibrium sample");
          autoState = AUTO_COMPLETE;
          return true;
        }
        
        //  Add temperature to sliding window
        temperatureWindow[windowIndex] = sht.getTemperature();
        windowIndex = (windowIndex + 1) % EQUILIBRIUM_WINDOW_SIZE;
        if (windowCount < EQUILIBRIUM_WINDOW_SIZE)
        {
          windowCount++;
        }
        
        //  Check for equilibrium if we have a full 2-second window
        if (windowCount >= EQUILIBRIUM_WINDOW_SIZE)
        {
          //  Calculate average dT/dt across all consecutive samples
          float totalRate = 0.0;
          uint8_t numRates = EQUILIBRIUM_WINDOW_SIZE - 1;
          
          for (uint8_t i = 0; i < numRates; i++)
          {
            uint8_t currentIndex = (windowIndex + i) % EQUILIBRIUM_WINDOW_SIZE;
            uint8_t nextIndex = (windowIndex + i + 1) % EQUILIBRIUM_WINDOW_SIZE;
            
            float dT = abs(temperatureWindow[nextIndex] - temperatureWindow[currentIndex]);
            float dt = 0.25;  // 250ms between samples
            totalRate += dT / dt;
          }
          
          float avgRate = totalRate / numRates;
          
          DEBUG_PRINT("  Equilibrium check: avg dT/dt = ");
          DEBUG_PRINT(avgRate, 3);
          DEBUG_PRINT(" °C/s (threshold: ");
          DEBUG_PRINT(dTthreshold, 3);
          DEBUG_PRINTLN(" °C/s)");
          
          if (avgRate <= dTthreshold)
          {
            DEBUG_PRINT("Equilibrium reached! Final: ");
            DEBUG_PRINT(originalTemperature, 2);
            DEBUG_PRINT("°C (original), ");
            DEBUG_PRINT(sht.getTemperature(),2);
            DEBUG_PRINT("°C (settled), ");
            DEBUG_PRINT(sht.getHumidity(), 1);
            DEBUG_PRINTLN("%RH (final)");
            autoState = AUTO_COMPLETE;
            return true;
          }
        }
        
        //  Start next equilibrium sample
        if (!sht.requestData(equilibriumMeasurementType))
        {
          DEBUG_PRINTLN("ERROR: Failed to request next equilibrium sample");
          autoState = AUTO_COMPLETE;
          return true;
        }
        
        lastEquilibriumSample = millis();
      }
    }
    return false;
  }
  
  return false;
}


//  Returns: Temperature in Celsius
float getAutoTemperature()
{
  if(!needsHeating) return originalTemperature;
  return sht.getTemperature();
}


//  Returns: Relative humidity in %
float getAutoHumidity()
{
  if(!needsHeating) return originalHumidity;
  return sht.getHumidity();
}
//  -- END OF FILE --
