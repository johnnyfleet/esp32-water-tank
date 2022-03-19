
#include <Arduino.h>
#include <math.h>

/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-hc-sr04-ultrasonic-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

const int trigPin = 12;
const int echoPin = 27;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
#define WATER_TANK_HEIGHT_CM 233.00
#define WATER_TANK_RADIUS_CM 180.00
#define WATER_TANK_MAX_WATER_HEIGHT_CM 224.00

long duration;
float distanceCm;
float percentFull;
float waterVolume;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  percentFull = (1 - (distanceCm - 9) / WATER_TANK_MAX_WATER_HEIGHT_CM ) * 100; 
  waterVolume = (((WATER_TANK_HEIGHT_CM - distanceCm)/100) * pow(WATER_TANK_RADIUS_CM/100,2) * M_PI) *1000;

  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Percent full: ");
  Serial.println(percentFull);
  Serial.print("Water volume: ");
  Serial.println(waterVolume);

  delay(1000);
}