#include <WiFi.h>
#include <NetworkClient.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 2  // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#endif

String ssid = "Amirhosein";
String ssid_pass = "fkmo5779";


void handleAPIRequest() {
  // Handle POST request
  if (server.hasArg("plain")) {  // Check for JSON payload
    String body = server.arg("plain");
    Serial.println("Received: " + body);
    server.send(200, "application/json", "{\"status\":\"success\"}");
  } else {
    server.send(400, "application/json", "{\"status\":\"error\",\"message\":\"No data received\"}");
  }
}

NetworkServer server(80);


void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, ssid_pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("================== Connecting to Wifi ==================");
  }
  Serial.println();
  Serial.println(ssid);
  Serial.println("Connected to Wi-Fi! IP address: " + WiFi.localIP().toString());

  // Start the server
  server.begin();
  Serial.println("Server started!");
}

void loop() {
  NetworkClient client = server.accept();  // Listen for incoming clients

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    String postData = "";         // To store POST data payload
    bool isPost = false;          // Flag to check if it's a POST request

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);          // Print received data to Serial Monitor

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // If POST, read content-length and payload
            if (isPost) {
              while (client.available()) {
                char c = client.read();
                postData += c;  // Read POST data payload
              }

              Serial.println("Received POST Data:");
              Serial.println(postData);

              // Handle the POST data here (e.g., parse JSON or control the LED)
              if (postData.indexOf("\"state\":\"on\"") >= 0) {

                digitalWrite(LED_BUILTIN, HIGH);  // Turn LED on
              } else if (postData.indexOf("\"state\":\"off\"") >= 0) {
                digitalWrite(LED_BUILTIN, LOW);   // Turn LED off
              }

              // Send a response
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: application/json");
              client.println();
              client.println("{\"status\":\"success\",\"message\":\"LED state updated\"}");
              break;
            } else {
              // Send a response for non-POST requests
              client.println("HTTP/1.1 400 Bad Request");
              client.println("Content-Type: text/plain");
              client.println();
              client.println("Invalid Request");
              break;
            }
          }

          // Check if the request is POST
          if (currentLine.startsWith("POST")) {
            isPost = true;
          }
          currentLine = "";  // Clear the current line
        } else if (c != '\r') {
          currentLine += c;  // Append characters to the current line
        }
      }
    }
    client.stop();  // Close the connection
    Serial.println("Client Disconnected.");
  }
}
