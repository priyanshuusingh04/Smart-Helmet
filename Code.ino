#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <AltSoftSerial.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Emergency phone number (WITHOUT '+')
const String EMERGENCY_PHONE = "918081551010"; // Replace with your number

// Default coordinates if GPS fails
#define DEFAULT_LAT "30.968742714756125"
#define DEFAULT_LON "76.4715745241708"

// SIM900A GSM Module Pins
#define rxPin 2
#define txPin 3

// GPS Neo-6M Module Pins
#define gpsRxPin 8
#define gpsTxPin 9

// Initialize modules
SoftwareSerial sim900a(rxPin, txPin);
AltSoftSerial neogps(gpsRxPin, gpsTxPin);
TinyGPSPlus gps;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// Variables
String latitude, longitude;
int sensitivity = 20; // Impact sensitivity (adjust as needed)
boolean impact_detected = false;
unsigned long impact_time;

void setup() {
  Serial.begin(9600);
  sim900a.begin(9600);
  neogps.begin(9600);

  // Initialize GSM module
  Serial.println("Initializing SIM900A...");
  initModule("AT", "OK", 2000);          // Handshake
  initModule("ATE1", "OK", 2000);       // Echo on (as original SIM800L code)
  initModule("AT+CPIN?", "OK", 2000);   // Check SIM
  initModule("AT+CMGF=1", "OK", 2000);  // SMS text mode
  initModule("AT+CNMI=1,1,0,0,0", "OK", 2000); // SMS notifications

  // Initialize accelerometer
  if (!accel.begin()) {
    Serial.println("ADXL345 not found!");
    while (1);
  }

  Serial.println("System Ready");
}

void loop() {
  detectImpact();
  
  if (impact_detected && (millis() - impact_time >= 10000)) { // 10s delay
    sendAlert();  // SMS first
    delay(2000);
    makeCall();   // Then call
    impact_detected = false;
  }

  // Debugging: Press 't' in Serial Monitor to test
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 't') {
      getGps();
      sendAlert();
      makeCall();
    }
  }
}

// Impact detection (buzzer code removed)
void detectImpact() {
  sensors_event_t event;
  accel.getEvent(&event);
  float magnitude = sqrt(event.acceleration.x * event.acceleration.x + 
                        event.acceleration.y * event.acceleration.y + 
                        event.acceleration.z * event.acceleration.z);

  if (magnitude >= sensitivity) {
    Serial.print("Impact detected! Magnitude: ");
    Serial.println(magnitude);
    getGps();
    impact_detected = true;
    impact_time = millis();
  }
}

void initModule(String cmd, char *res, int t) {
  while (1) {
    Serial.println(cmd);
    sim900a.println(cmd);
    delay(100);
    while (sim900a.available() > 0) {
      if (sim900a.find(res)) {
        Serial.println(res);
        delay(t);
        return;
      }
    }
    delay(t);
  }
}

void getGps() {
  unsigned long start = millis();
  while (millis() - start < 5000) {
    while (neogps.available()) {
      if (gps.encode(neogps.read())) {
        if (gps.location.isValid()) {
          latitude = String(gps.location.lat(), 6);
          longitude = String(gps.location.lng(), 6);
          Serial.print("Lat: "); Serial.println(latitude);
          Serial.print("Lng: "); Serial.println(longitude);
          return;
        }
      }
    }
  }
  latitude = DEFAULT_LAT;
  longitude = DEFAULT_LON;
  Serial.println("GPS failed - Using default coordinates");
}

void sendAlert() {
  sim900a.println("AT+CMGF=1");
  delay(500);
  sim900a.print("AT+CMGS=\"+");
  sim900a.print(EMERGENCY_PHONE);
  sim900a.println("\"");
  delay(500);
  
  String message = "ACCIDENT ALERT!\n";
  message += "Location: http://maps.google.com/maps?q=";
  message += latitude + "," + longitude;
  
  sim900a.print(message);
  delay(500);
  sim900a.write(26);
  Serial.println("SMS sent");
  delay(2000);
}

// Original SIM800L call function preserved
void makeCall() {
  while (sim900a.available()) sim900a.read();

  sim900a.println("AT+CLIP=1");
  delay(1000);
  
  String callCommand = "ATD +" + EMERGENCY_PHONE + ";";
  sim900a.println(callCommand);
  
  Serial.print("Attempting call: ");
  Serial.println(callCommand);

  unsigned long timeout = millis();
  bool callConnected = false;
  
  while (millis() - timeout < 30000) {
    while (sim900a.available()) {
      String response = sim900a.readStringUntil('\n');
      Serial.println(response);
      
      if (response.indexOf("OK") != -1) {
        callConnected = true;
        break;
      }
      if (response.indexOf("NO CARRIER") != -1) break;
      if (response.indexOf("BUSY") != -1) break;
    }
    if (callConnected) break;
  }

  if (callConnected) {
    Serial.println("Call connected");
    delay(20000);
  } else {
    Serial.println("Call failed");
  }
  
  sim900a.println("ATH");
  Serial.println("Call ended");
  delay(1000);
}