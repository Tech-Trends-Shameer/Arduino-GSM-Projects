#include "Adafruit_FONA.h"
#include <SoftwareSerial.h>

// Define pins for FONA module
#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

// Define pins for relays
#define RELAY_1 8
#define RELAY_2 7
#define RELAY_3 6
#define RELAY_4 5

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

char replybuffer[255];
char authorizedNumber[] = "+91XXXXXXXXXX";  // Replace with your authorized mobile number with country code
char senderNumber[21];  // Buffer to store sender's number

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  fonaSS.begin(4800); // FONA baud rate
  
  // Initialize relays as OUTPUT
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);

  // Turn off all appliances initially
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, LOW);
  
  // Initialize FONA module
  if (!fona.begin(fonaSS)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));
}

void loop() {
  uint16_t smsIndex;

  if (fona.available()) {
    smsIndex = fona.getNumSMS(); // Get number of SMS in memory
    if (smsIndex > 0) {
      if (fona.readSMS(1, replybuffer, 250, &smsIndex)) { // Read the SMS at location 1
        Serial.print(F("Message received: ")); Serial.println(replybuffer);

        // Now get the sender's number
        if (fona.getSMSSender(1, senderNumber, 20)) {
          Serial.print(F("Message sent by: ")); Serial.println(senderNumber);

          // Check if the sender is the authorized number
          if (strcmp(senderNumber, authorizedNumber) == 0) {
            controlAppliance(replybuffer);  // Only process the message if it’s from the authorized number
          } else {
            Serial.println(F("Unauthorized sender. Ignoring message."));
          }
        }

        // Delete the SMS to prevent memory overflow
        fona.deleteSMS(1);
      }
    }
  }
}

void controlAppliance(char* message) {
  if (strstr(message, "LIGHT1 ON") != NULL) {
    digitalWrite(RELAY_1, HIGH); // Turn on light (Relay 1)
    Serial.println(F("Light1 turned ON"));
  } else if (strstr(message, "LIGHT1 OFF") != NULL) {
    digitalWrite(RELAY_1, LOW); // Turn off light (Relay 1)
    Serial.println(F("Light1 turned OFF"));
  }

if (strstr(message, "LIGHT2 ON") != NULL) {
    digitalWrite(RELAY_2, HIGH); // Turn on light (Relay 1)
    Serial.println(F("Light2 turned ON"));
  } else if (strstr(message, "LIGHT2 OFF") != NULL) {
    digitalWrite(RELAY_2, LOW); // Turn off light (Relay 1)
    Serial.println(F("Light2 turned OFF"));
  }

  if (strstr(message, "LIGHT3 ON") != NULL) {
    digitalWrite(RELAY_3, HIGH); // Turn on light (Relay 1)
    Serial.println(F("Light3 turned ON"));
  } else if (strstr(message, "LIGHT3 OFF") != NULL) {
    digitalWrite(RELAY_3, LOW); // Turn off light (Relay 1)
    Serial.println(F("Light3 turned OFF"));
  }

  if (strstr(message, "LIGHT4 ON") != NULL) {
    digitalWrite(RELAY_4, HIGH); // Turn on light (Relay 1)
    Serial.println(F("Light4 turned ON"));
  } else if (strstr(message, "LIGHT4 OFF") != NULL) {
    digitalWrite(RELAY_4, LOW); // Turn off light (Relay 1)
    Serial.println(F("Light4 turned OFF"));
  }
  // Add more commands as needed for other appliances (Relay 3, 4, etc.)
}
