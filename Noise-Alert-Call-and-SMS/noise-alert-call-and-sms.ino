#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"

#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4

#define FONA_RI_INTERRUPT  0
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

char PHONE_1[21] = "+91XXXXXXXXXX"; // Enter your Country code followed by your phone number
char noisealert[141]= "High Noise Alert";
int sensor_pin = A0;

int threshold = 400; // Adjust this threshold based on your testing

void setup()
{
  pinMode(sensor_pin, INPUT);
  Serial.begin(115200);
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(5000);
  
  fonaSS.begin(9600); // if you're using software serial
  if (!fona.begin(fonaSS)) { // Can also try fona.begin(Serial1)
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }

  fona.print("AT+CSMP=17,167,0,0\r");
  Serial.println(F("FONA is OK"));
}

void loop() {
  int noise_value = analogRead(sensor_pin);
  Serial.print("Noise Value: ");
  Serial.println(noise_value);
  
  delay(1000); // Sample every 1 second

  if (noise_value > threshold) { // If the value is greater than the threshold, you will get earthquake alert
    Serial.println("High Noise Alert");
    send_multi_sms();
    make_multi_call();
    delay(10000); // Wait 60 seconds before next alert to avoid spam
  }
}

void send_multi_sms() {
  if (PHONE_1 != "") {
    Serial.print("Sending SMS to Phone 1: ");
    fona.sendSMS(PHONE_1, noisealert);
    delay(10000);
  }
}

void make_multi_call() {
  if (PHONE_1 != "") {
    Serial.print("Calling Phone 1: ");
    make_call(PHONE_1);
    delay(10000);
  }
}

void make_call(String phone) {
  Serial.println("Calling....");
  fona.println("ATD" + phone + ";");
  delay(10000); // 20-second call duration
  fona.println("ATH"); // Hang up the call
  delay(1000);  // 1-second delay before resuming
}
