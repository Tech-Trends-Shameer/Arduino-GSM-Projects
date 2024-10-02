#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"

#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4

#define FONA_RI_INTERRUPT  0
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

char PHONE_1[21] = "+XXXXXXXXXX"; // Enter your number here with country code.
char moisturealert[141]= "Soil Moisture is Low";
int soil_sensor_pin = A0;

int dry_threshold = 800; // Adjust this threshold based on your testing

void setup()
{
  pinMode(soil_sensor_pin, INPUT);
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
  int moisture_value = analogRead(soil_sensor_pin);
  Serial.print("Soil Moisture Value: ");
  Serial.println(moisture_value);
  
  delay(1000); // Sample every 1 second

  if (moisture_value > dry_threshold) { // If the value is greater than the threshold, the soil is dry
    Serial.println("Soil Moisture is Low");
    send_multi_sms();
    make_multi_call();
    delay(60000); // Wait 60 seconds before next alert to avoid spam
  }
}

void send_multi_sms() {
  if (PHONE_1 != "") {
    Serial.print("Sending SMS to Phone 1: ");
    fona.sendSMS(PHONE_1, moisturealert);
    delay(10000);
  }
}

void make_multi_call() {
  if (PHONE_1 != "") {
    Serial.print("Calling Phone 1: ");
    make_call(PHONE_1);
    delay(20000);
  }
}

void make_call(String phone) {
  Serial.println("Calling....");
  fona.println("ATD" + phone + ";");
  delay(20000); // 20-second call duration
  fona.println("ATH"); // Hang up the call
  delay(1000);  // 1-second delay before resuming
}
