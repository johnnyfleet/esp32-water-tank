/*Arduino example sketch to control a JSN-SR04T ultrasonic distance sensor with NewPing libary and Arduino. More info: https://www.makerguides.com */
// Include the library:
#include <NewPing.h>

// Define Trig and Echo pin:
#define trigPin 12
#define echoPin 27

// Define maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500 cm:
#define MAX_DISTANCE 400
// NewPing setup of pins and maximum distance.

NewPing sonar = NewPing(trigPin, echoPin, MAX_DISTANCE);

void setup() {
  // Open the Serial Monitor at 115200 baudrate to see ping results:
  Serial.begin(115200);
}
void loop() {

    float distance = sonar.ping_median(5);

  if(distance>400 || distance<2) Serial.println("Out of range");
  else
  {
    Serial.print("Distance: ");
    Serial.print(distance, 1); Serial.println(" cm");
  }
 
  delay(50);
}