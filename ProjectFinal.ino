#include <TinyGPS++.h>

// Define the GPS module's serial connection (Serial1 for Arduino Uno)
#define GPS_SERIAL Serial1

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Button pin
const int buttonPin = 7;

void setup() {
  Serial.begin(9600);
  GPS_SERIAL.begin(9600);  // Initialize the hardware serial for the GPS module
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    // Button is pressed

    // Wait for a valid GPS fix
    while (!gps.location.isValid()) {
      while (GPS_SERIAL.available() > 0) {
        gps.encode(GPS_SERIAL.read());
      }
    }

    // Get latitude and longitude
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();

    Serial.print("Latitude: ");
    Serial.println(latitude, 6);  // Print latitude with 6 decimal places
    Serial.print("Longitude: ");
    Serial.println(longitude, 6);  // Print longitude with 6 decimal places


    // Send the location data to IFTTT
    sendLocationToIFTTT(latitude, longitude);

    // Delay to avoid multiple triggers from a single button press
    delay(5000);
  }
}

void sendLocationToIFTTT(float lat, float lon) {
  // Your IFTTT integration code to send location data
  // This depends on your specific IFTTT applet and its setup
}
