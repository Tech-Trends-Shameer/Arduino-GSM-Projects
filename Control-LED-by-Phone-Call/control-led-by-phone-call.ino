//Tech Trends Shameer
//Control LED by Phone Call

#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
 

#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4
 
#define FONA_RI_INTERRUPT  0
int led = 13; 
String techtrends;
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
 
void setup() {
  pinMode(led, OUTPUT);     
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


// Code from Loop Start
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
    
    Serial.print("Call From: ");
    Serial.println(techtrends);
    
    digitalWrite(led, HIGH);
    delay(30000);
    digitalWrite(led, LOW);
    if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) {
    Serial.println(F("Caller id notification enabled."));
    } 
    }
//Code From Loop End
  
}
 
void loop(){
     
  
  }
