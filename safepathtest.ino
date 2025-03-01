#include <SoftwareSerial.h>

#define BUTTON_PIN 2
#define A6_TX 10
#define A6_RX 11

SoftwareSerial a6Serial(A6_TX, A6_RX);

const char* phoneNumber = "+250794092577";

float latitude = 0.3476;
float longitude = 32.5825;

int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("SafeGuard Starting...");

  a6Serial.begin(115200);
  delay(2000);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (initA6()) {
    Serial.println("A6 GPRS Pro initialized!");
  } else {
    Serial.println("A6 initialization failed after retries!");
  }
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        Serial.println("Button Pressed! Sending SMS...");
        sendEmergencySMS();
      }
    }
  }
  lastButtonState = reading;

  while (a6Serial.available()) {
    Serial.write(a6Serial.read());
  }
}

bool initA6() {
  for (int i = 0; i < 3; i++) {
    a6Serial.println("AT");
    delay(1000);
    String response = "";
    unsigned long timeout = millis() + 1000;
    while (millis() < timeout) {
      if (a6Serial.available()) {
        response += (char)a6Serial.read();
      }
    }
    Serial.println("AT Attempt " + String(i + 1) + ": " + response);
    if (response.indexOf("OK") >= 0) {
      a6Serial.println("AT+CMGF=1");
      delay(1000);
      response = "";
      timeout = millis() + 1000;
      while (millis() < timeout) {
        if (a6Serial.available()) {
          response += (char)a6Serial.read();
        }
      }
      if (response.indexOf("OK") >= 0) {
        return true;
      }
    }
    delay(1000);
  }
  return false;
}

void sendEmergencySMS() {
  String dateTime = "2025-02-27 14:30:00";
  String mapsLink = "https://maps.google.com/?q=" + String(latitude, 6) + "," + String(longitude, 6);
  String message = "ALERT: I'm in danger!\nDate/Time: " + dateTime + 
                  "\nLocation: Lat " + String(latitude, 6) + ", Lon " + String(longitude, 6) + 
                  "\nTrack me: " + mapsLink;

  while (a6Serial.available()) {
    a6Serial.read();
  }

  a6Serial.println("AT+CMGF=1");
  delay(500);

  a6Serial.print("AT+CMGS=\"");
  a6Serial.print(phoneNumber);
  a6Serial.println("\"");
  delay(500);
  a6Serial.print(message);
  delay(100);
  a6Serial.write(26);
  delay(2000);

  String response = "";
  unsigned long timeout = millis() + 2000;
  while (millis() < timeout) {
    if (a6Serial.available()) {
      response += (char)a6Serial.read();
    }
  }
  Serial.println("SMS Response: " + response);
  if (response.indexOf("+CMGS") >= 0 && response.indexOf("OK") >= 0) {
    Serial.println("SMS Sent Successfully!");
  } else {
    Serial.println("SMS Failed!");
  }
}