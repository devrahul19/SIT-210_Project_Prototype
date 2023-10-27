
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

char ssid[] = "FTTH-C997";          // Your WiFi SSID
char pass[] = "rrrrrrrr";      // Your WiFi Password
char server[] = "api.thingspeak.com";  // ThingSpeak server
String apiKey = "f03fb4825807447c50dc146f7d57676d";         // Your ThingSpeak API Key

int vibrationPin = 2;  // The pin where the vibration sensor is connected
int sensorValue = 0;   // Variable to store the sensor value
int count = 0;         // Counter for number of readings

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, 80);

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  // Read the sensor value
  sensorValue = digitalRead(vibrationPin);

  // If vibration is detected, send data to ThingSpeak
  if (sensorValue == HIGH) {
    count++;

    // Create the data to send
    String data = "field1=" + String(count);

    // Make a POST request to ThingSpeak
    String url = "/update";
    client.post(url, "application/x-www-form-urlencoded", data);
    int statusCode = client.responseStatusCode();
    
    if (statusCode == 200) {
      Serial.println("Data sent to ThingSpeak successfully.");
    } else {
      Serial.print("Failed to send data. HTTP error code: ");
      Serial.println(statusCode);
    }

    delay(15000);  // Wait for 15 seconds before the next reading
  }
  delay(100);  // Check the sensor every 100 milliseconds
}
