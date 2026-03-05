/*
   Projet:  TP01 - Partie 01
   Fichier: main.cpp
   Auteur:  Yannick Kananin
   Date:    2026-02-28
   -----------------------------------------------
   Description:
      Station de contrôle 420-1C4 version 1.0
      - Contrôle LED1 (D2), LED2 (D3), Relai (D4)
      - Affichage température et humidité (SHT31)
      - Affichage temps écoulé (jours/heures/minutes/secondes)
      - Affichage sur LCD RGB (Alarme + temps écoulé)
   -----------------------------------------------
   M-A-J: Fin de la partie 1
*/

// ============================================================
// Inclusion du fichier d'entête du projet
// ============================================================
#include "projet.h"

// ============================================================
// Déclaration des objets
// ============================================================
ANSI    ansi(&Serial);
SHT31   sht31;
rgb_lcd lcd;

// ============================================================
// Déclaration des variables globales
// ============================================================
bool etatLED1  = false;
bool etatLED2  = false;
bool etatRELAI = false;

// ============================================================
// Prototypes des fonctions
// ============================================================
void afficherOnOff(int posX, int posY, bool on = true);
void afficherTemperatureEtHumidite(int posX, int posY);
void afficherTempsEcoule();

// ============================================================
// afficherOnOff()
// Affiche ON (vert) ou OFF (rouge) a la position (posX, posY)
// ============================================================
void afficherOnOff(int posX, int posY, bool on) {
    ansi.gotoXY(posX, posY);
    if (on) {
        Serial << ANSI_VERT  << F("ON ") << ANSI_BLANC;
    } else {
        Serial << ANSI_ROUGE << F("OFF") << ANSI_BLANC;
    }
} // afficherOnOff()

// ============================================================
// afficherTemperatureEtHumidite()
// Lit le SHT31 et affiche temperature + humidite
// ============================================================
void afficherTemperatureEtHumidite(int posX, int posY) {
    float temperature = sht31.getTemperature();
    float humidite    = sht31.getHumidity();

    ansi.gotoXY(posX, posY);
    Serial << ANSI_VERT;
    Serial.print(temperature, 1);
    Serial << F(" C   ") << ANSI_BLANC;

    ansi.gotoXY(posX, posY + 1);
    Serial << ANSI_VERT;
    Serial.print(humidite, 1);
    Serial << F(" %   ") << ANSI_BLANC;
} // afficherTemperatureEtHumidite()

// ============================================================
// afficherTempsEcoule()
// Calcule et affiche le temps ecoule depuis le demarrage
// ============================================================
void afficherTempsEcoule() {
    unsigned long lesMillis = millis();
    unsigned long secondes  = lesMillis / 1000;

    unsigned long jours  = secondes / SECONDES_PAR_JOUR;
    secondes            %= SECONDES_PAR_JOUR;
    byte heures          = secondes / SECONDES_PAR_HEURE;
    secondes            %= SECONDES_PAR_HEURE;
    byte minutes         = secondes / SECONDES_PAR_MINUTE;
    secondes            %= SECONDES_PAR_MINUTE;

    // L'utilisation de trois buffer pour gérer l'affichage du temps
    // le nombre de jours en jaune, "jour(s)" en blanc et le reste du temps en jaune
    char bufferNbJours[10];
    char bufferMot[10];
    char bufferTemps[15];

    snprintf(bufferNbJours, sizeof(bufferNbJours), "%lu ", jours);
    snprintf(bufferMot,     sizeof(bufferMot),     "jour%s  ", (jours > 1 ? "s" : ""));
    snprintf(bufferTemps,   sizeof(bufferTemps),   "%02d:%02d:%02lu", heures, minutes, secondes);

    ansi.gotoXY(COL_TEMPS, LIGNE_TEMPS);
    Serial << ANSI_JAUNE << bufferNbJours << ANSI_BLANC << bufferMot << ANSI_JAUNE << bufferTemps << ANSI_BLANC << F("   ");

    // Affichage LCD ligne 2
    char lcdBuffer[17];
    snprintf(lcdBuffer, sizeof(lcdBuffer), "-> %02lu:%02d:%02d:%02lu",
             jours, heures, minutes, secondes);
    lcd.setCursor(LCD_PREMIERE_COL, LCD_LIGNE2);
    lcd.print(lcdBuffer);

} // afficherTempsEcoule()

// ============================================================
// setup()
// ============================================================
void setup() {
    Serial.begin(VITESSE_UART);

    // Initialisation des broches
    pinMode(PIN_LED1,  OUTPUT);
    pinMode(PIN_LED2,  OUTPUT);
    pinMode(PIN_RELAI, OUTPUT);

    // Initialisation I2C
    Wire.begin();
    sht31.begin();

    // Initialisation LCD
    lcd.begin(LCD_NB_COLONNE, LCD_NB_LIGNE);
    lcd.setRGB(0, 128, 255);
    lcd.setCursor(LCD_PREMIERE_COL, LCD_LIGNE1);
    lcd.print("Alarme : ON");

    // Affichage de l'interface dans le terminal serie
    ansi.clearScreen();
    Serial << CURSEUR_OFF << ANSI_BLANC;
    Serial << (F("╔═══════════════════════════════════════════════════════════════════╗\n"));
    Serial << (F("║              Station de contrôle 420-1C4 version 1.0              ║\n"));
    Serial << (F("╟───────────────────────────────────────────────────────────────────╢\n"));
    Serial << (F("║ 1 - LED1  sur ")); Serial << ANSI_BLEU << F("D2") << ANSI_BLANC; Serial << (F("                                                  ║\n"));
    Serial << (F("║ 2 - LED2  sur ")); Serial << ANSI_BLEU << F("D3") << ANSI_BLANC; Serial << (F("                                                  ║\n"));
    Serial << (F("║ 3 - Relai sur ")); Serial << ANSI_BLEU << F("D4") << ANSI_BLANC; Serial << (F("                                                  ║\n"));
    Serial << (F("║                                                                   ║\n"));
    Serial << (F("║                                                                   ║\n"));
    Serial << (F("║                                                                   ║\n"));
    Serial << (F("╟───────────────────────────────────────────────────────────────────╢\n"));
    Serial << (F("║                                                                   ║\n"));
    Serial << (F("║ Température            :                                          ║\n"));
    Serial << (F("║ Humidité               :                                          ║\n"));
    Serial << (F("║                                                                   ║\n"));
    Serial << (F("╟───────────────────────────────────────────────────────────────────╢\n"));
    Serial << (F("║ Temps écoulé:                                        Option:      ║\n"));
    Serial << (F("╟───────────────────────────────────────────────────────────────────╢\n"));
    Serial << (F("║ Projet réalisé par Yannick Kananin                  TP01-Partie 01║\n"));
    Serial << (F("╚═══════════════════════════════════════════════════════════════════╝\n"));

    // Affichage initial des etats ON/OFF
    afficherOnOff(COL_ONOFF, LIGNE_LED1,  etatLED1);
    afficherOnOff(COL_ONOFF, LIGNE_LED2,  etatLED2);
    afficherOnOff(COL_ONOFF, LIGNE_RELAI, etatRELAI);

} // setup()

// ============================================================
// loop()
// ============================================================
void loop() {

    // Lecture clavier
    if (Serial.available()) {
        char commande = Serial.read();

        if (commande == '1') {
            etatLED1 = !etatLED1;
            digitalWrite(PIN_LED1, etatLED1 ? HIGH : LOW);
            afficherOnOff(COL_ONOFF, LIGNE_LED1, etatLED1);
        }
        if (commande == '2') {
            etatLED2 = !etatLED2;
            digitalWrite(PIN_LED2, etatLED2 ? HIGH : LOW);
            afficherOnOff(COL_ONOFF, LIGNE_LED2, etatLED2);
        }
        if (commande == '3') {
            etatRELAI = !etatRELAI;
            digitalWrite(PIN_RELAI, etatRELAI ? HIGH : LOW);
            afficherOnOff(COL_ONOFF, LIGNE_RELAI, etatRELAI);
        }

        // Afficher la touche saisie
        ansi.gotoXY(COL_OPTION, LIGNE_OPTION);
        Serial << ANSI_BLEU << commande << ANSI_BLANC;
    }

    // Temperature et Humidite toutes les 2 secondes
    static unsigned long derniereLecture = 0;
    if (millis() - derniereLecture >= DELAI_LECTURE_SHT) {
        derniereLecture = millis();
        afficherTemperatureEtHumidite(COL_TEMP_VAL, LIGNE_TEMP);
    }

    // Temps ecoule
    afficherTempsEcoule();

} // loop()

// FIN DU FICHIER