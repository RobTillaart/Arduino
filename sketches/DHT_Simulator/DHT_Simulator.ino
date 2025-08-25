//
//    FILE: DHT_simulator.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Simulation of the DHT protocol
//    DATE: 2014-06-14
//     URL: https://github.com/RobTillaart/DHT_Simulator

// TODO
// - split loop into some functions?


//  SET ACTUAL PINS PER PLATFORM
const int dataPin     = 5;    //  connect to MCU ( !! also connect GND !! )
const int CRCPin      = 6;    //  connect switch to simulate CRC errors.
const int TimeOutPin  = 7;    //  connect switch to simulate timeout errors.
const int PulseLenPin = 8;    //  connect switch to simulate pulselength errors.


#if defined(__AVR__)
const int humPin  = A0;       //  analog pins for potmeters.
const int tempPin = A2;
#elif defined(ESP32)
const int humPin  = 14;
const int tempPin = 15;
#elif defined(ESP8266)
const int humPin  = 2;
const int tempPin = 3;
#else // CI
const int humPin  = A0;
const int tempPin = A2;
#endif


//  DATA TO SEND
byte b[5];                //  actual bytes sent
int humidity;             //  humidity * 10     - prevent float operations
int temperature;          //  temperature * 10


//  CONFIGURE
const bool randomize = true;   //  use random generator
const bool debug     = false;  //  test data generation

bool CRCerror        = false;  //  inject CRC error
bool TimeOutError    = false;  //
bool PulseLenError   = false;  //
uint32_t   count     = 0;      //  count values per second generated
uint32_t   lastTime  = 0;      //  keep track of timing


/////////////////////////////////////////


void setup()
{
  Serial.begin(115200);
  Serial.print("Start ");
  Serial.println(__FILE__);

  pinMode(dataPin,     INPUT_PULLUP);
  pinMode(CRCPin,      INPUT_PULLUP);
  pinMode(TimeOutPin,  INPUT_PULLUP);
  pinMode(PulseLenPin, INPUT_PULLUP);
}


void loop()
{
  yield();    //  keep ESP happy

  count++;
  uint32_t now = millis();
  if (now - lastTime >= 1000)
  {
    uint32_t nps = round((1000.0 * count) / (now - lastTime));
    Serial.print("DATA PER SECOND: ");
    Serial.println(nps);
    lastTime = now;
    count = 0;
  }

  if (randomize)
  {
    humidity = random(20, 1000);
    temperature = random(-200, 1800);
  }
  else
  {
    analogRead(humPin);
    humidity = analogRead(humPin);
    analogRead(tempPin);
    temperature = analogRead(tempPin) * 2 - 200;
  }
  humidity = constrain(humidity, 0, 1000);
  temperature = constrain(temperature, -200, 1800);

  if (debug)
  {
    Serial.print(humidity);
    Serial.print("\t");
    Serial.print(temperature);
    Serial.println();
  }


  //  READ "ERROR" PINS
  CRCerror        = digitalRead(CRCPin) == LOW;
  TimeOutError    = digitalRead(TimeOutPin) == LOW;
  PulseLenError   = digitalRead(PulseLenPin) == LOW;


  //  WAKE UP SIGNAL DETECTED
  if (digitalRead(dataPin) == LOW)
  {
    uint32_t start = micros();
    //  wait max 1500 us until signal goes high
    while (digitalRead(dataPin) == LOW)
    {
      if (micros() - start > 1500)
      {
        // Serial.println("ERROR: low puise too long");
        return;
      }
    }
    if (micros() - start > 500)     //  serious request...
    {
      DHTsend(humidity, temperature);

      Serial.print(humidity);
      Serial.print("\t");
      Serial.print(temperature);
      Serial.print("\t");
      for (int i = 0; i < 5; i++)
      {
        if (b[i] < 0x10) Serial.print('0');
        Serial.print(b[i], HEX);
        Serial.print(' ');
      }
      Serial.println();
    }
    else
    {
      Serial.println("ERROR: low puise too short");
    }
  }
}


void DHTsend(int H, int T)
{
  pinMode(dataPin, OUTPUT);
  //  SEND ACK
  digitalWrite(dataPin, LOW);
  delayMicroseconds(80);                  //  80 us
  digitalWrite(dataPin, HIGH);
  delayMicroseconds(80);                  //  80 us

  if (TimeOutError)
  {
    delayMicroseconds(100);  //  inject extra 100 microseconds
  }

  //  PREPARE DATA
  b[0] = H / 256;
  b[1] = H & 255;

  b[2] = 0;
  if (T < 0)
  {
    T = -T;
    b[2] = 0x80;
  }

  b[2] |= T / 256;
  b[3] = T & 255;

  //  CRC
  b[4] = b[0] + b[1] + b[2] + b[3];
  if (CRCerror) b[4]++;          //  inject CRC error

  //  SEND DATA
  for (int i = 0; i < 5; i++)
  {
    DHTsendbyte(b[i]);
  }

  //  END OF TRANSMISSION SIGNAL
  digitalWrite(dataPin, LOW);
  delayMicroseconds(50);                  //  50 us
  pinMode(dataPin, INPUT_PULLUP);
}


//  timing manual tuned
void DHTsendbyte(byte b)
{
  byte mask = 128;
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(dataPin, LOW);
    delayMicroseconds(45);                //  50 us
    if (PulseLenError)
    {
      delayMicroseconds(10);              //  inject extra pulse length  // TWEAK amount
    }
    digitalWrite(dataPin, HIGH);
    if (b & mask) delayMicroseconds(60);  //  70 us
    else delayMicroseconds(24);           //  26 us
    mask >>= 1;
  }
}

//  -- END OF FILE --
