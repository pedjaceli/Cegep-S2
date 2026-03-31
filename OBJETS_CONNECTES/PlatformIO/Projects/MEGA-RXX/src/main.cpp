/*
    Arduino MEGA
    Le récepteur via UART2 (Serial2)
*/

#include <Arduino.h>
#include "Streaming.h"
#define leTransmetteur Serial2

// Définir la structure des données
// NOTE: tampon maximum en réception UART 64 octets
struct lesDonnees {
  int id;
  char ip[16];           // Taille maximale de l'IP en format texte
  char description[10];  // Taille maximale de la description
};

lesDonnees mesDonnees;

// ----------------------------------------------------------------
void setup() {
  // Initialiser la communication série avec l'ordinateur
  Serial.begin(9600);
  
  // Initialiser la communication Serial2 (Mega utilise Serial2 pour la communication avec le transmetteur)
  leTransmetteur.begin(57600);

  Serial << "Réception des données...\n";
}

// ----------------------------------------------------------------
void loop() {
  if (leTransmetteur.available()) {
    // Attendre un peu, pour laisser le temps aux info d'arriver
    delay(100);
    Serial << "\nOctets reçus: " << Serial2.available() << endl;
 
    // Vérifier si des données sont disponibles sur Serial2
    if (leTransmetteur.available() == (int) sizeof(mesDonnees)) {
      // Lire les données reçues
      leTransmetteur.readBytes((char*)&mesDonnees, sizeof(mesDonnees));

      // Afficher les données reçues
      Serial << "\nID: " << mesDonnees.id << "\nIP: " << mesDonnees.ip 
            << "\nDescription: " << mesDonnees.description << endl;
    } else {
      Serial << "Données incomplètes ou erronées.\n";
      while(leTransmetteur.available()) {
        leTransmetteur.read(); // Vider le tampon de réception
      } 
    } // if sizeof(mesDonnees)
  } // if available()
} // loop()