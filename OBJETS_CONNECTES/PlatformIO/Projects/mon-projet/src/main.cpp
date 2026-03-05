#include <Arduino.h>

void setup() {

  Serial.begin(9600);
  Serial.println("Bonjour Arduino!");
 
}

void loop() {
  static int i = 0;
   Serial.println(String(i++) + " - Bonjour Arduino!");
 
}

