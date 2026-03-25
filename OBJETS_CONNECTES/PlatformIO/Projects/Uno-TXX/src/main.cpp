/*
  Relier deux Arduino via le port UART physique
  Code du transmetteur - sur le UNO
  NOTE: Il est important d'utiliser le câble avec les fils blanc et jaune inversés
  */

#include <Arduino.h>
#include "rgb_lcd.h"
#include "Streaming.h"

#define UART_RX             6
#define UART_TX             7
#define UART_VITESSE        9600
#define MAX_NB_ALEATOIRE    99
#define UNE_SECONDE         1000
#define LCD_DEUXIEME_LIGNE  1
#define LCD_NB_LIGNE        2
#define LCD_NB_COL          16
#define transmetteur        Serial

rgb_lcd lcd;

//--------------------------------------------------------
void setup() {
  // port natif utilisé pour la transmission vers le Mega
  transmetteur.begin(UART_VITESSE); 
  lcd.begin(LCD_NB_COL,LCD_NB_LIGNE);
  lcd.print("Transmetteur");
} // setup()

//--------------------------------------------------------
void loop() {
   // Transmettre un code à chaque seconde  
   // générer un nombre entre 0 et MAX_NB_ALEATOIRE - 1
   byte unCode = random(MAX_NB_ALEATOIRE); 
   transmetteur.write(unCode);
   lcd.setCursor(0, LCD_DEUXIEME_LIGNE);
   lcd << "Envoi de: " << unCode;
   delay(UNE_SECONDE);
} // loop()