#include <Arduino.h>
/*
 Code du récepteur - sur le Mega
*/

#define UART_VITESSE        9600
// Le RX du UNO doit être connecté au TX du MEGA et TX -> RX
// Utiliser le cable avec les fils jaune et blanc inversés
// Connecter le UNO sur le port Serial2 du MEGA
#define recepteur           Serial2 

//--------------------------------------------------------
void setup() {
  Serial.begin(UART_VITESSE);
  Serial.println("Démarrage du récepteur...");
  recepteur.begin(UART_VITESSE);
}

//--------------------------------------------------------
void loop() {  
  byte unCode;
  if (recepteur.available()) {
    unCode = recepteur.read();
    // afficher la valeur du byte reçu
    Serial.print("Code recu = ");
    Serial.println(unCode);
   } // si byte disponible sur le UART
}