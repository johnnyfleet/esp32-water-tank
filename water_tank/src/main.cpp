#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <math.h>
#include <NewPing.h>
//#include "time.h"

/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-hc-sr04-ultrasonic-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

//-------------------------Config Information---------------------
#include <Config.h>

/* Root certificate for HiveMQ MQTT broker */
static const char *root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";

//------------------------------------------------------------------

#define LED 2                                       /* Blue LED pin number */
#define uS_TO_S_FACTOR 1000000                      /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10                           /* Time ESP32 will go to sleep (in seconds) */
#define SOUND_SPEED 0.034                           /* define sound speed in cm/uS */
#define WATER_TANK_HEIGHT_CM 233.00                 /* full height of tank (internal) */
#define WATER_TANK_RADIUS_CM 180.00                 /* radius of tank (roughly internal) */
#define WATER_TANK_MAX_WATER_HEIGHT_CM 224.00       /* Maximum height the water level can reach before overflow - this is 100% full */
#define TRIGGER_PIN  12                             /* Arduino pin tied to trigger pin on the ultrasonic sensor. */
#define ECHO_PIN     27                             /* Arduino pin tied to echo pin on the ultrasonic sensor. */
#define MAX_DISTANCE 300                            /* Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm. */
#define MQTT_TOPIC "rtl_433/outside/water_tank/"    /* Proposed base topic to post to */
#define MSG_BUFFER_SIZE (200)                       /* Maximum message size for MQTT */


// NTP server to request epoch time
const char* ntpServer = "pool.ntp.org";

//Global variables
float distanceCM;
float percentFull;
int waterVolumeLtr;
RTC_DATA_ATTR int bootCount = 0;                    /* Boot count - persists over deep sleep */
char msg[MSG_BUFFER_SIZE];                          /* Message size for MQTT*/


WiFiClientSecure espClient;
PubSubClient client(espClient);                     /* MQTT broker library */
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); /* Setup NewPing for untrasonic sensor */
unsigned long lastMsg = 0;

// =======================================================================================================

/*
Method to print the reason by which ESP32
has been awaken from sleep
*/
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

/*
Setup Wifi - used on each startup from deep sleep
*/
void setup_wifi() {

    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PW);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

/*
Get current time - to timestamp message to MQTT broker. 
*/
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

/*
Get (roughly) unique ID made form Mac address
*/
String getDeviceID(){
    byte mac[6];
    WiFi.macAddress(mac);
    String uniq =  String(mac[0],HEX) +String(mac[1],HEX) +String(mac[2],HEX) +String(mac[3],HEX) + String(mac[4],HEX) + String(mac[5],HEX);
    return uniq;
}

void getMeasurements(){
    distanceCM = sonar.ping_median(5) * SOUND_SPEED/2;
    percentFull = (1 - (distanceCM - 9) / WATER_TANK_MAX_WATER_HEIGHT_CM ) * 100; 
    waterVolumeLtr = (((WATER_TANK_HEIGHT_CM - distanceCM)/100) * pow(WATER_TANK_RADIUS_CM/100,2) * M_PI) *1000; 

    // Prints the distance in the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distanceCM);
    Serial.print("Percent full: ");
    Serial.println(percentFull);
    Serial.print("Water volume (litres): ");
    Serial.println(waterVolumeLtr);
}

/*
Send message to MQTT broker. 
*/
void writeMQTTMessage(){
    
    snprintf (msg, MSG_BUFFER_SIZE, "{\"time\":\"%ld.000000\",\"id\":\"%s\",\"distance_cm\":%f,\"percent_full\":%f,\"water_volume_ltr\":%i,\"reboot_cycles\":%i}",getTime(),getDeviceID().c_str(),roundf(distanceCM*100.0)/100.0,roundf(percentFull*100.0)/100.0,waterVolumeLtr,bootCount);
    //snprintf (msg, MSG_BUFFER_SIZE, "the title of %ld is %f",value,distanceCM);
    Serial.print("Publish message: ");
    Serial.println(msg);
    char fullTopic[100];   // array to hold the result.
    strcpy(fullTopic,MQTT_TOPIC); // copy string one into the result.
    strcat(fullTopic,getDeviceID().c_str()); // append string two to the result.
    client.publish(fullTopic, msg);
}

//=====================================
void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection…");
        // Create a random client ID
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASS)) {
            //if (client.connect(clientId.c_str())) {
            Serial.println("connected");

        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

//================================================
void setup() {
    pinMode(LED, OUTPUT);       // Initialize the BUILTIN_LED pin as an output
    digitalWrite(LED, HIGH);    // Turn on LED (so you know when in and out of deep sleep)
    //delay(500);
    Serial.begin(115200);
    delay(500);
    setup_wifi();
    configTime(0, 0, ntpServer);// Setup NTP server location to get correct epoch time. 

    ++bootCount;                //Increment boot number and print it every reboot
    Serial.println("Boot number: " + String(bootCount));
    Serial.println("Device ID: " + String(getDeviceID()));

    //Print the wakeup reason for ESP32
    print_wakeup_reason();

    //Setup MQTT connection with TLS. 
    espClient.setCACert(root_ca);
    client.setServer(MQTT_SERVER, MQTT_PORT);

    if (!client.connected()) {
        reconnect();
    }

    //Read the distance from sensor (take 5 readings and calculate the median to minimise variance)
    getMeasurements(); 
    //Write the message to MQTT
    writeMQTTMessage();  
    
    //Set the amount of time before wake up
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");

    /*
    Now that we have setup a wake cause and if needed setup the
    peripherals state in deep sleep, we can now start going to
    deep sleep.
    In the case that no wake up sources were provided but deep
    sleep was started, it will sleep forever unless hardware
    reset occurs.
    */
    Serial.println("Going to sleep now");
    delay(1000);
    Serial.flush(); 
    esp_deep_sleep_start();

    Serial.println("This will never be printed");
}

void loop() {
    // Does nothing - due to deep sleep we never reach this far. 
    Serial.println("This will never be printed");
}