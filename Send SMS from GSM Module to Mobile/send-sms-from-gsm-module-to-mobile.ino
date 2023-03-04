//Tech Trends Shameer
//Send SMS from GSM Module to Mobile

#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
 
#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4
 
#define FONA_RI_INTERRUPT  0

char sendto[21] = "+xxxxxxxxxxxx"; // Enter your Mobile Number here. Exclude country code.
char message[141] = "Welcome to Tech Trends"; 

String techtrends;
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
 
void setup() {  
  Serial.begin(115200);
  Serial.println(F("FONA incoming call example"));
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(5000);
  fonaSS.begin(4800); // if you're using software serial
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));
 
 fona.print ("AT+CSMP=17,167,0,0\r");
   fona.sendSMS(sendto, message);
   delay(1000);
}
 
void loop()
{
  //fona.sendSMS(sendto, message);
  delay(10000);
}
