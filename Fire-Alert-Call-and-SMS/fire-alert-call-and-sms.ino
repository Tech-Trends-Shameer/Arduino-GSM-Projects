//Tech Trends Shameer
//Fire Alert Call & SMS in Mobile

#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
 
#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4
 
#define FONA_RI_INTERRUPT  0
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);


char PHONE_1[21] = "+91xxxxxxxxxx"; // Enter your Mobile Number
char firemessage[141]= "Fire is Detected"  ;
int flame_sensor_pin = 5;
int fire_flag = 0;


void setup()
{
  pinMode(flame_sensor_pin,INPUT);
  Serial.begin(115200);
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(5000);
  fonaSS.begin(9600); // if you're using software serial
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }

   fona.print ("AT+CSMP=17,167,0,0\r");
    Serial.println(F("FONA is OK"));
    pinMode(flame_sensor_pin, INPUT);
}

void loop(){
  
  int flame_value= digitalRead(flame_sensor_pin);
  if(flame_value == HIGH && fire_flag==1)
  {     
     Serial.println("Fire Detected.");
     fire_flag = 0;
    
     make_multi_call();
     send_multi_sms();
   }
   else if( flame_value == LOW)
  {
//    noTone(buzzer_pin);
    fire_flag = 1;
  }
  }

void send_multi_sms()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    fona.sendSMS(PHONE_1,firemessage);
    delay(1000);
  }

}
void make_multi_call()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    make_call(PHONE_1);
  }
 
}

void make_call(String phone)
{
    Serial.println("calling....");
    fona.println("ATD"+phone+";");
    delay(10000); //10 sec delay
    fona.println("ATH");
    delay(1000); //1 sec delay
}
