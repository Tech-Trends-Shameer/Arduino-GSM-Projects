//Tech Trends Shameer
//Caller ID Project Using GSM SIM Module

#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  

#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4
 
#define FONA_RI_INTERRUPT  0

String techtrends;
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
 
void setup() {
     lcd.begin();
    lcd.setCursor(3,0);
    lcd.print("Tech Trends");
    lcd.setCursor(5,1);
    lcd.print("Shameer");
  Serial.begin(115200);
  Serial.println(F("FONA incoming call example"));
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(3000);
  fonaSS.begin(4800); // if you're using software serial
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));
 
  if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) {
    Serial.println(F("Caller id notification enabled."));
  }
  else {
    Serial.println(F("Caller id notification disabled"));
  }
}
 
void loop(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  GSM SIM 800C ");
    lcd.setCursor(0,1);
    lcd.print("CallerID Project"); 
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    Serial.print("GSM Kit Not Working");
     }
     else
  fona.callerIdNotification(true, FONA_RI_INTERRUPT);
  char phone[32] ={0};
   
  if(fona.incomingCallNumber(phone)){
   Serial.println(F("RING!"));
    Serial.print(F("Phone Number: "));
    techtrends=phone;
    lcd.clear();
    Serial.print("Call From: ");
    Serial.println(techtrends);
    lcd.setCursor(0,0);
    lcd.print("Ringing !!!");
    lcd.setCursor(3,1);
    lcd.print(techtrends);
    delay(15000);
    if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) {
    Serial.println(F("Caller id notification enabled."));
    } 
    }
  }
