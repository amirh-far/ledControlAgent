#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const int A_LED = 4;
const int B_LED = 33;
const char* ssid = "Amirhosein";
const char* password = "fkmo5779";
JsonDocument doc;

void sendGETRequest() {
  if (WiFi.status() == WL_CONNECTED) {  // Check Wi-Fi connection
    HTTPClient http;
    String serverUrl = "http://192.168.167.170/api/v1/AI/data";  // Replace with your server URL

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
      deserializeJson(doc, responseBody);

    } else {
      Serial.print("Error on sending GET request: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Free resources
  } else {
    Serial.println("Wi-Fi not connected.");
  }
}

void sendPOSTRequest(String log) {
  HTTPClient http;
  String api_url = "http://192.168.167.170/api/v1/AI/log";
  http.begin(api_url);
  http.addHeader("Content-Type", "application/json");

  // JSON payload for the OpenAI API
  String payload = "{";
  payload += "\"log\":";
  payload += "\"";
  payload += log;
  payload += "\"";
  payload += "}";
  Serial.println(payload);

  int httpResponseCode = http.POST(payload);
  String response = "";

  if (httpResponseCode > 0) {
    response = http.getString();
  } else {
    response = "Error: " + String(httpResponseCode);
  }
  http.end();
}


void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(A_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);

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
  sendGETRequest();

  String log = "";
  for (int i = 0; i < doc["codes"].size(); i++) {
    const char* code = doc["codes"][i];

    Serial.println(code);
    if (doc["codes"][i] == "A1") {
      digitalWrite(A_LED, HIGH);
      log += "Kitchen LED Turned ON Sucessfuly, ";
    }
    if (doc["codes"][i] == "A0") {
      digitalWrite(A_LED, LOW);
      log += "Kitchen LED Turned OFF Sucessfuly, ";
    }
    if (doc["codes"][i] == "B1") {
      digitalWrite(B_LED, HIGH);
      log += "Room LED Turned ON Sucessfuly, ";
    }
    if (doc["codes"][i] == "B0") {
      digitalWrite(B_LED, LOW);
      log += "Room LED Turned ON Sucessfuly, ";
    }
  }
  sendPOSTRequest(log);
}
