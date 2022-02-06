#include <Arduino.h> 

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10        /* Time ESP32 will go to sleep (in seconds) */
#define LED 2

void setup(){
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, HIGH);
  Serial.println("LED is on");
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");

  delay(10000); /* stay on for 5 seconds */
  
  digitalWrite(LED, LOW);
  Serial.println("LED is off");

  Serial.println("Going to sleep now");
  Serial.flush(); 
  
  esp_deep_sleep_start();
  Serial.println("This message will never be printed");
}

void loop(){ 
}