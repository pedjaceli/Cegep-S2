/*
    Arduino UNO 
    Le transmetteur, via SoftwareSerial sur D7 et D6
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Streaming.h"

#define DELAI_ENTRE_TRANSMISSION  1000

// Définir les pins pour la communication SoftwareSerial
SoftwareSerial lienAvecRecepteur(7, 6); // RX, TX

struct Temps {
  uint8_t heure;
  uint8_t minute;
  uint8_t seconde;
};

struct lesDonnees {
  int id;
  char ip[16];           // Taille maximale de l'IP en format texte
  char description[10];  // Taille maximale de la description
  Temps heure;
}; // 31 octets 

// Exemple d'utilisation
lesDonnees mesDonnees = {1, "10.10.0.1", "E0000001", {0, 0, 0}};

// ----------------------------------------------------------------
void setup() {
  // Initialiser la communication série avec l'ordinateur
  // Pour les traces au moniteur
  Serial.begin(9600);
  
  // Initialiser la communication SoftwareSerial vers le récepteur
  lienAvecRecepteur.begin(57600);
  
  Serial << "Démarrage de la transmission des données...\n";
} // setup

// ----------------------------------------------------------------
void loop() {
  static int compteur=0;
  mesDonnees.id = compteur++;
  Serial << "\nid: " << mesDonnees.id << "\nIP: " << mesDonnees.ip << "\nDescription: " << mesDonnees.description << endl;
  // Envoyer les données via SoftwareSerial
  // (byte*)&mesDonnees -> passe la localisation de la structure en mémoire,
  // et indique de la traiter comme une série d'octets
  lienAvecRecepteur.write((byte*)&mesDonnees, sizeof(mesDonnees));
  Serial << "Octets envoyés: " << sizeof(mesDonnees) << endl;

  // À l'occasion, simuler une erreur de transmission
  // avec une autre transmission sans délai, de mesDonnees-1.
  if (random(0, 100) < 10) {
    lienAvecRecepteur.write((byte*)&mesDonnees, sizeof(mesDonnees)-1);
    Serial << "Erreur de transmission: " << sizeof(mesDonnees)-1 << " octets envoyés.\n";
    delay(DELAI_ENTRE_TRANSMISSION); 
  } // Ce qui va totaliser 55 (27+28) octets coté récepteur, au lieu de 28 octets

  // Attendre un peu avant de renvoyer les données
  // Si ce délai est trop court, il risque d'avoir une congestion à niveau du récepteur.
  // Faites des tests de fiabilité.
  delay(DELAI_ENTRE_TRANSMISSION); // 1 seconde d'attente
} // loop