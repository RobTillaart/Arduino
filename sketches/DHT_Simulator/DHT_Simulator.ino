//
//    FILE: DHT_simulator.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: 
//    DATE: 2014-06-14
//     URL:
//
// Released to the public domain
//

// TODO
// - robustness
// - timeout loops
// - get timing accurate

const int dataPin = 5;
byte b[5];

void setup() 
{
  Serial.begin(115200);
  Serial.println("Start ");

  pinMode(dataPin, INPUT_PULLUP);
}

void loop() 
{
  // T = -200 .. 1800
  analogRead(A2);
  int T = analogRead(A2) * 2 - 200; 

  // H = 0 .. 1000
  analogRead(A0);
  int H = analogRead(A0);
  if (H > 1000) 
  {
    H = 1000;                
  }
  //  Serial.print(H);
  //  Serial.print("\t");
  //  Serial.println(T);

  // WAKE UP SIGNAL DETECTED
  if (digitalRead(dataPin) == LOW)     
  {
    uint32_t start = micros();
    // wait until signal goes high // todo timeout onblocking loop?
    while (digitalRead(dataPin) == LOW);
    if (micros() - start > 500) // serious request...
    {

      pinMode(dataPin, OUTPUT);
      // send ACK    
      digitalWrite(dataPin, LOW);
      delayMicroseconds(80);             // overhead digitalwrite (2..4us)
      digitalWrite(dataPin, HIGH);
      delayMicroseconds(80);

      DHTsend(H, T);

      digitalWrite(dataPin, LOW);
      delayMicroseconds(50);
      pinMode(dataPin, INPUT_PULLUP);

      //  for (int i = 0; i < 5; i++)
      //  {
      //    Serial.print(b[i]);
      //    Serial.print(" ");
      //  }
      //  Serial.println();

      Serial.print(H);
      Serial.print("\t");
      Serial.println(T);
    }
  }
}

void DHTsend(int H, int T)
{
  // prepare data
  b[0] = H / 256;
  b[1] = H & 255;

  uint16_t t;
  if (T >= 0) 
  {
    t = T;
    b[2] = 0;
  }
  else 
  {
    t = -T;
    b[2] = 0x80;
  }
  Serial.println(t);

  b[2] |= (t / 256);
  b[3] = (t & 255);

  b[4] = b[0] + b[1] + b[2] + b[3];          // CRC

  for (int i = 0; i < 5; i++)
  {
    DHTsendbyte(b[i]);
  }
}

void DHTsendbyte(byte b)
{
  byte mask = 128;
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(dataPin, LOW);
    delayMicroseconds(45);                // overhead digitalwrite (2..4us)
    digitalWrite(dataPin, HIGH);

    if (b & mask) delayMicroseconds(60);  // idem
    else delayMicroseconds(24);           // idem

    mask >>= 1;
  }
}
















