
//
//    FILE: SGP30_demo_lora.ino
//  AUTHOR: Rob Tillaart, Anthony Powell
// PURPOSE: demo SGP30 to LORA
//     URL: https://github.com/RobTillaart/SGP30


#include <SPI.h>
#include <LoRa.h>
#include <SGP30.h>
#include <ArduinoJson.h>
#include <Wire.h>


SGP30 sgp;

// Create a unique ID for the data from each ESP32 running this code

const char* jediID = "Envirodrone";

uint32_t lastTime = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println(F("LoRa Sender"));

  if (!LoRa.begin(868E6))
  {
    Serial.println("Error: Starting LoRa failed! reboot system");
    while (1);
  }
  Serial.println(F("Enviro Drone SGP30 Sensor Start"));
  delay(1000);

  //  Initialize I2C bus

  Wire.begin();
  Wire.setClock(400000);

  //  Initialize sensor
  while (! sgp.begin())
  {
    Serial.println(F("Error: Could not detect SGP30 sensor"));
    delay(3000);
  }
}


void loop()
{
  String postData;

  //  send data once every 10 seconds
  if (millis() - lastTime >= 10000)
  {
    uint32_t start = millis();
    Serial.print("time: \t");
    Serial.println(start);


    Serial.print(millis() - start);
    Serial.println("Read SGP30 sensor.");
    sgp.measure(true);
    float co2  = sgp.getCO2();
    float tvoc = sgp.getTVOC();
    float h2   = sgp.getH2();
    float etha = sgp.getEthanol();
    Serial.print(co2);
    Serial.print("\t");
    Serial.print(tvoc);
    Serial.print("\t");
    Serial.print(h2);
    Serial.print("\t");
    Serial.print(etha);
    Serial.println();


    Serial.print(millis() - start);
    Serial.println("Create serialized JSON string.");
    StaticJsonDocument <200> doc;
    JsonObject data = doc.createNestedObject("data");
    data["CO2"] = co2;
    data["TVOC"] = tvoc;
    data["H2"] = h2;
    data["Ethanol"] = etha;
    serializeJson(doc, postData);
    Serial.println(postData);


    Serial.print(millis() - start);
    Serial.println("Send LORA packet.");
    LoRa.beginPacket();
    LoRa.print(postData);
    LoRa.endPacket();


    uint32_t stop = millis();
    Serial.print(millis() - start);
    Serial.print("Duration:\t");
    Serial.println(stop - start);
  }


}
//  -- END OF FILE --
