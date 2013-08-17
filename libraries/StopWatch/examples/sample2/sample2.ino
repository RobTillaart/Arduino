#include <StopWatch.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

StopWatch sw_millis;    // MILLIS (default)
StopWatch sw_micros(StopWatch::MICROS);
StopWatch sw_secs(StopWatch::SECONDS);

void setup() {
    lcd.begin(16,2);
    Serial.begin(9600);
    sw_millis.start();
    sw_micros.start();
    sw_secs.start();
}


void loop() {
    Serial.print("sw_millis=");
    Serial.println(sw_millis.elapsed());
    Serial.print("sw_micros=");
    Serial.println(sw_micros.elapsed());
    Serial.print("sw_secs=");
    Serial.println(sw_secs.elapsed());
    
    lcd.clear();
    lcd.print("s=");
    lcd.print(sw_secs.elapsed());
    lcd.print(" ms=");
    lcd.print(sw_millis.elapsed());
    lcd.setCursor(0, 1);
    lcd.print("us=");
    lcd.print(sw_micros.elapsed());
    
    delay(1000);
}