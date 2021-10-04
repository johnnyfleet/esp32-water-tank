/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Ping.h>
#include <Wire.h>

#include <Config.h>

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = MQTT_SERVER;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

// LED Pin
const int ledPin = 4;

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PW);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  setup_wifi();

  pinMode(ledPin, OUTPUT);
}

void loop() {
  Serial.print("Pinging www.google.com. ");
  bool success = Ping.ping("www.google.com", 3);
 
  if(!success){
      Serial.println("Ping failed");
      return;
  }
  
  Serial.println("Ping succesful.");

  delay(1000);

}
