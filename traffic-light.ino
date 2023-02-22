#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
 
#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4
 
#define FONA_RI_INTERRUPT  0
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);


char PHONE_1[21] = "xxxxxxxxxx"; // Enter your Number here.

 
char alert[141]= "You Violated Traffic rules Rs 1000/- debited from your account"  ;

int pirsensor = 0; 

const int PIN_RED = 8;
const int PIN_YELLOW = 9;
const int PIN_GREEN = 10;

const int DELAY_RED = 20000;
const int DELAY_YELLOW = 1000;
const int DELAY_GREEN = 5000;

void setup()
{
  pinMode(5,INPUT);
	  pinMode(PIN_RED, INPUT);
  pinMode(PIN_YELLOW, INPUT);
  pinMode(PIN_GREEN, INPUT);
	
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
	
	


  allOff();
}

void loop(){  

  // Red
  digitalWrite(PIN_RED, HIGH);
  delay(DELAY_RED);	
	
  int pirsensor = digitalRead(5);
  int ledvalue = digitalRead(PIN_RED);
  Serial.print("Sensor Value:");
  Serial.println(pirsensor);
  Serial.print("LED Value:");
  Serial.println(ledvalue);
  if(ledvalue==1)
  {     
     if(pirsensor==1)
     {
     Serial.println("Violation Alert");
     send_multi_sms();
     make_multi_call();     
     }
  }
  else  
  { 
    pirsensor = 0;
    Serial.println("Safe");
  }
 
	
	
	
  digitalWrite(PIN_RED, LOW);

  // Green
  digitalWrite(PIN_GREEN, HIGH);
  delay(DELAY_GREEN);
  digitalWrite(PIN_GREEN, LOW);

  // Orange / Yellow
  digitalWrite(PIN_YELLOW, HIGH);
  delay(DELAY_YELLOW);
  digitalWrite(PIN_YELLOW, LOW);
  
  
 
  
 }

void send_multi_sms()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    fona.sendSMS(PHONE_1,alert);
    delay(5000);
  } 
}
void make_multi_call()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    make_call(PHONE_1);
    delay(5000);
  } 
}

void make_call(String phone)
{
    Serial.println("calling....");
    fona.println("ATD"+phone+";");
    delay(5000); //20 sec delay
    fona.println("ATH");
    delay(1000); //1 sec delay
}

void allOff()
{
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_GREEN, LOW);
}
