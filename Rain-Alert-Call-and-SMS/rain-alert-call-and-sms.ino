//Tech Trends Shameer
//Rain Alert Call in Mobile

#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
 
#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4
 
#define FONA_RI_INTERRUPT  0
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);


char PHONE_1[21] = "+91xxxxxxxxxx"; // Enter your Mobile Number
char PHONE_2[21] = ""; // Optional 
char PHONE_3[21] = ""; // Optional
//char welcomemessage[141] = "Welcome to Tech Trends";
char rainalertmessage[141]= "Its Raining"  ;
int rain_sensor_pin = 5;
 
int rain_flag = 0;


void setup()
{
  pinMode(rain_sensor_pin,INPUT);
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
//    fona.sendSMS(PHONE_1, welcomemessage);
    pinMode(rain_sensor_pin, INPUT);
    //pinMode(buzzer_pin, OUTPUT);
    //noTone(buzzer_pin);
}

void loop(){
  
  int rain_value= digitalRead(rain_sensor_pin);
  Serial.println(rain_value);
  if(rain_flag==0)
  {
     //tone(buzzer_pin,1000);
     Serial.println("Rain Alert.");
     rain_flag = 1;
    
     make_multi_call();

   //   send_multi_sms();
   }
   else if( rain_value == LOW)
  {
//    noTone(buzzer_pin);
    rain_flag = 0;
  }
  }

void send_multi_sms()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    fona.sendSMS(PHONE_1,rainalertmessage);
    delay(20000);
  }
 /* if(PHONE_2 != ""){
    Serial.print("Phone 2: ");
   fona.sendSMS(PHONE_2,firemessage);
   delay(1000);
  }
  if(PHONE_3 != ""){
    Serial.print("Phone 3: ");
    fona.sendSMS(PHONE_3,firemessage);
    delay(1000);
  }*/
}
void make_multi_call()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    make_call(PHONE_1);
  }
 /* if(PHONE_2 != ""){
    Serial.print("Phone 2: ");
    make_call(PHONE_2);
  }
  if(PHONE_3 != ""){
    Serial.print("Phone 3: ");
    make_call(PHONE_3);
  }*/
}

void make_call(String phone)
{
    Serial.println("calling....");
    fona.println("ATD"+phone+";");
    delay(30000); //20 sec delay
    fona.println("ATH");
    delay(1000); //1 sec delay
}
