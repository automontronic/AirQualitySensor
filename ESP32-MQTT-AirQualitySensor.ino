#include "MQ135.h"
#include <WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
int air_quality;
unsigned long previousMillis = 0;
unsigned long interval = 30000;
const char* ssid     = "SSID";           //Replace with your network name
const char* password = "PASSWORD";  //Replave with your network password
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
// IP address for the MQTT broker
IPAddress server(127, 0, 0, 1);
// MQTT Topic
const char*  topic = "topic/name";
// WiFi Client
WiFiClient espClient;
// MQTT Client
PubSubClient client(espClient);
// String used to store air quality level
String aq_str; 
// Char array used to publish to topic
char aq[50];

// initialize and setup
void setup() {
    // A delay
    delay(1000);
    // Setup serial
    Serial.begin(115200);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    // Start the Wifi
    WiFi.begin(ssid, password);
    // Wait until connected
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // Print local IP address
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    // Setup MQTT
    client.setServer(server, 1883);
}

// Reconnect to the MQTT server
void reconnect(char* message) {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient4","dillaman","gkfs2022")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
       client.publish(topic,message);
      // ... and resubscribe
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
 unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
 
    // Read the air quality on pin A0
    int air_quality = analogRead(A0);
    // Convert the air quality to a string
    aq_str = String(air_quality);
    // Convert the air quality to a char array
    aq_str.toCharArray(aq, aq_str.length() + 1);
    
    // Make sure there is a connection MQTT
    if (!client.connected()) {
        // Reconnect and send the airquality
        reconnect(aq);
        delay(1500);
    }

    // Publish the air Quality
    client.publish(topic,aq);
   
    Serial.print(air_quality);      
    Serial.println(" PPM");

    // Wait to repoll
    delay(30000);
}

