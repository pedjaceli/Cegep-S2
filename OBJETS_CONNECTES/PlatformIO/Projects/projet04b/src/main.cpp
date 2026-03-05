#include <Arduino.h>

#define BROCHE_DEL      3         // LED sur pin 3
#define DELAI           20
#define UNE_SECONDE     1000

void setup() {
  pinMode(BROCHE_DEL, OUTPUT);    // Broche de la DEL en mode OUTPUT
} // setup()

void loop() {
    static byte intensiteDEL = 255;

    analogWrite(BROCHE_DEL, intensiteDEL); // Allumer la DEL avec le mode PWM
    intensiteDEL--;               // Diminuer la valeur d'intensité de la DEL

    if (intensiteDEL == 0) {      // Si intensité de la DEL est = 0 alors remettre à 255
      intensiteDEL = 255;
      delay(UNE_SECONDE / 2);     // Laisser la DEL éteinte pendant 1/2 sec.
    } // if (intensiteDEL == 0)

    delay(DELAI); // Ralentir un peu la variation d'intensité de la DEL.
} // loop()