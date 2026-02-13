#include <AS7331.h>
#include <Wire.h>

#define AS7331_ADDR 0x74
AS7331 uv_sensor(AS7331_ADDR);

uint8_t gains[] = {
  AS7331_GAIN_1x,
  AS7331_GAIN_2x,
  AS7331_GAIN_4x,
  AS7331_GAIN_8x,
  AS7331_GAIN_16x,
  AS7331_GAIN_32x,
  AS7331_GAIN_64x,
  AS7331_GAIN_128x,
  AS7331_GAIN_256x,
  AS7331_GAIN_512x,
  AS7331_GAIN_1024x,
  AS7331_GAIN_2048x
};

uint8_t convs[] = {
  AS7331_CONV_001,
  AS7331_CONV_002,
  AS7331_CONV_004,
  AS7331_CONV_008,
  AS7331_CONV_016,
  AS7331_CONV_032,
  AS7331_CONV_064,
  AS7331_CONV_128,
  AS7331_CONV_256,
  AS7331_CONV_512,
  AS7331_CONV_1024,
  AS7331_CONV_2048,
  AS7331_CONV_4096,
  AS7331_CONV_8192,
  AS7331_CONV_16384
};

uint8_t NUM_GAINS = sizeof(gains);
uint8_t NUM_CONVS = sizeof(convs);

uint8_t gainIndex = 0;
uint8_t convIndex = 0;
bool headerPrinted = false;

void printHeader() {
  if (headerPrinted) return;

  Serial.println(
    "millis,"
    "gain_hex,conv_hex,gain_x,conv_ms,"
    "uva_raw,uvb_raw,uvc_raw,"
    "uva_mw,uvb_mw,uvc_mw,"
    "temp_c"
  );

  headerPrinted = true;
}

void startNextMeasurement() {
  uv_sensor.setConfigurationMode();
  uv_sensor.setGain(gains[gainIndex]);
  uv_sensor.setConversionTime(convs[convIndex]);
  uv_sensor.startMeasurement();
}

void setup() {

  // debug
  //NUM_GAINS = 4;
  //NUM_CONVS = 4;

  Serial.begin(74880);
  Wire.begin(12, 14);
  delay(500);
  Serial.println();
  delay(500);
  Serial.println();

  if (!uv_sensor.begin()) {
    Serial.println("ERROR,AS7331_NOT_FOUND");
    while (1);
  }

  delay(500);
  Serial.println();

  printHeader();
  startNextMeasurement();
}

void loop() {
  if (uv_sensor.conversionReady()) {

    uint8_t gain = gains[gainIndex];
    uint8_t conv = convs[convIndex];

    uint32_t conv_ms = 1UL << conv;
    uint32_t gain_x  = 1UL << (AS7331_GAIN_1x - gain);

    // Raw counts
    uint16_t uva_raw = uv_sensor.getRawUVA();
    uint16_t uvb_raw = uv_sensor.getRawUVB();
    uint16_t uvc_raw = uv_sensor.getRawUVC();

    // Scaled values
    float uva_mw = uv_sensor.getUVA_mW();
    float uvb_mw = uv_sensor.getUVB_mW();
    float uvc_mw = uv_sensor.getUVC_mW();

    float temp_c = uv_sensor.getCelsius();
    if (temp_c > 80) {
      Serial.println("OFF");
    }

    // CSV
    Serial.print(millis()); Serial.print(",");
    Serial.print("0x"); Serial.print(gain, HEX); Serial.print(",");
    Serial.print("0x"); Serial.print(conv, HEX); Serial.print(",");
    Serial.print(gain_x); Serial.print(",");
    Serial.print(conv_ms); Serial.print(",");

    Serial.print(uva_raw); Serial.print(",");
    Serial.print(uvb_raw); Serial.print(",");
    Serial.print(uvc_raw); Serial.print(",");

    Serial.print(uva_mw, 6); Serial.print(",");
    Serial.print(uvb_mw, 6); Serial.print(",");
    Serial.print(uvc_mw, 6); Serial.print(",");

    Serial.println(temp_c, 3);

    convIndex++;
    if (convIndex >= NUM_CONVS) {
      convIndex = 0;
      gainIndex++;
      delay(1000);
    }

    if (gainIndex >= NUM_GAINS) {
      gainIndex = 0;
      Serial.println("NEXT");  // instructs the computer receiving the data to advance to the next light intensity
      delay(1000);
    }

    startNextMeasurement();
  }

  delay(5);
  processSerial();
}

void processSerial() {
  while (Serial.available() > 0) {
    switch (Serial.read()) {
      case 'M':
        uv_sensor.startMeasurement();
        Serial.println("startMeasurement");
        break;
      case 'R' :
        uv_sensor.softwareReset();
        Serial.println("softwareReset");
        break;
    }
  }
}
