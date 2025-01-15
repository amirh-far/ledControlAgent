

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 2  // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#endif

// Replace these with your Wi-Fi credentials
const char* ssid = "Amirhosein";
const char* password = "fkmo5779";
char* data;

const char* sendGETRequest() {
  if (WiFi.status() == WL_CONNECTED) {  // Check Wi-Fi connection
    HTTPClient http;
    String serverUrl = "http://192.168.47.170/api/v1/AI/data";  // Replace with your server URL

    Serial.println("Sending GET request...");
    http.begin(serverUrl);              // Specify the URL
    int httpResponseCode = http.GET();  // Send the GET request

    if (httpResponseCode > 0) {  // Check the response
      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);

      // Get the response body
      String responseBody = http.getString();
      Serial.println("Response: " + responseBody);

      // Parse the JSON response
      JsonDocument doc;  // Adjust the size as needed
      deserializeJson(doc, responseBody);

      // Extract specific values
      const char* data;
      data = doc["data"];  // Assuming the response has a key "data"
      Serial.print("Extracted Data: ");
      Serial.println(data);
      return data;

    } else {
      Serial.print("Error on sending GET request: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Free resources
  } else {
    Serial.println("Wi-Fi not connected.");
  }
}


void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(4, OUTPUT);
  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000);
  String data = sendGETRequest();
  delay(5000);
  Serial.println(data);
  if (data == "A") {
    digitalWrite(4, HIGH);
  }
  if (data == "B") {
    digitalWrite(4, LOW);
  }
}
