#include <Arduino.h>
#include "main.h"

void setup() {
  Serial.begin(VITESSE_SERIE  ); // BAUD / 10 = 960 octets / sec
  Serial.println(F("Début du programme ..."));
  pinMode(LED, OUTPUT);
}

void loop() {
  static int i = 0;
  digitalWrite(LED, ON);
  delay(DELAI);
  digitalWrite(LED, OFF);
  delay(DELAI);
}

