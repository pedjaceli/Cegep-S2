#include <Arduino.h>
#include <Streaming.h>



// Définition des constantes

#define UNE_SECONDE   1000          // 1000 milli-secondes = 1 seconde
#define VITESSE_UART  9600
#define BOUTON        2
#define LED           3
#define ON            1
#define OFF           0


// Définition des variables globales

// ------------------
void setup() {
  // 1 - Ouvrir le port série à 9600 bps:
  Serial.begin(VITESSE_UART);
  // 2 - Afficher un message dans la console de débogage
  Serial.println("Début du programme\n\n");

  // fn broches
  pinMode(BOUTON, INPUT);
  pinMode(LED, OUTPUT);
} // setup()

// ------------------
void loop() {

  if(digitalRead(BOUTON)) {
    Serial << "Bouton = ON" <<  endl;
    digitalWrite(LED, ON);
    while (digitalRead(BOUTON));

  } else 
  {
    digitalWrite(LED, OFF);
  } // if BOUTON

  digitalWrite(LED, digitalRead(BOUTON));
  
} // loop()

