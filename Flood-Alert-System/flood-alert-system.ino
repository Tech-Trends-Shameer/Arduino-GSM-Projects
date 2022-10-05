//Tech Trends Shameer
//Flood Alert Call and SMS

#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
 
 
#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4
    
 

int resval = 0;  // holds the value
int respin = A3; // Water Level Sensor Pin 


#define FONA_RI_INTERRUPT  0
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);


char PHONE_1[21] = ""; // Enter your Mobile Number 

char tempalert[141]= "Flood Alert"  ; 
void setup()
{
//  pinMode(gas_sensor_pin,INPUT);
  Serial.begin(115200);
//  dht.begin();
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(5000);
  fonaSS.begin(9600); // if you're using software serial
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }

   fona.print ("AT+CSMP=17,167,0,0\r");
    Serial.println(F("FONA is OK"));
   //fona.sendSMS(PHONE_1, welcomemessage);
//    pinMode(gas_sensor_pin, INPUT);
 
}

void loop(){
  
 
  resval = analogRead(respin); 
  
  
  Serial.print("Water Level:");
  Serial.println(resval);

  
  if(resval>200 )
  {    
     Serial.println("Flood Alert");  
     make_multi_call();
     send_multi_sms();
   }
  
  }

void send_multi_sms()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    fona.sendSMS(PHONE_1,tempalert);
    delay(20000);
  }
   
   
}
void make_multi_call()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    make_call(PHONE_1);
    delay(20000);
  }
   
}

void make_call(String phone)
{
    Serial.println("calling....");
    fona.println("ATD"+phone+";");
    delay(20000); //20 sec delay
    fona.println("ATH");
    delay(1000); //1 sec delay
}
