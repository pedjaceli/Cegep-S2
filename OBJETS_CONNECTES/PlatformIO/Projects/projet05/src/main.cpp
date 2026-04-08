/*
   Projet:  TP02 - Partie A
   Fichier: main.cpp
   Auteur:  Yannick Kananin
   Date:    2026-03-21
   -----------------------------------------------
   Description:
      Station de contrôle UNO 3.0
      - Contrôle LED1 (D2), LED2 (D3), Relai (D4)
      - Détecteur de mouvement PIR (D5)
      - Alarme (D6)
      - Bouton panique (D7) - Interruption matérielle
      - Potentiomètre (A0) - Durée alarme 1-10 sec
      - Affichage température et humidité (SHT31)
      - Affichage temps écoulé (jours/heures/minutes/secondes)
      - Affichage date et heure (RTC DS1307)
      - Affichage sur LCD RGB (Alarme + temps écoulé)
      - Transmission des données vers le MEGA (SoftwareSerial D8/D9)
   -----------------------------------------------
   M-A-J: Début du TP02
*/

// ============================================================
// Inclusion du fichier d'entête du projet
// ============================================================
#include "projet.h"

// ============================================================
// Déclaration des objets
// ============================================================
ANSI            ansi(&Serial);
SHT31           sht31;
rgb_lcd         lcd;
DS1307          horloge;
SoftwareSerial  lienAvecMEGA(PIN_SOFT_RX, PIN_SOFT_TX);

// ============================================================
// Déclaration des variables globales
// ============================================================
bool etatLED1          = false;
bool etatLED2          = false;
bool etatRELAI         = false;
bool etatPIR           = false;
bool etatBoutonPanique = false;
bool etatRetroLCD      = true;
bool affichageCelcius  = true;
int  dureeAlarme       = 5;

unsigned long compteurMEGA = 0;

Systeme unSysteme;

// Tableaux pour le RTC
const char* nomDesJours[] = {"", "Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
const char* nomDesMois[]  = {"", "Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin",
                              "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};

// ============================================================
// Prototypes des fonctions
// ============================================================
void afficherOnOff(int posX, int posY, bool on = true);
void afficherUniteTemperature();
void afficherTemperatureEtHumidite(int posX, int posY);
void afficherTempsEcoule();
void afficherRTC();
void afficherCompteur();
void lirePotentiometre();
void preparerEtEnvoyerSysteme();

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
// afficherUniteTemperature()
// Affiche C (vert) ou F (jaune) pour l'unite de temperature
// ============================================================
void afficherUniteTemperature() {
    ansi.gotoXY(COL_ONOFF, LIGNE_CELCIUS_FAHRENHEIT);
    if (affichageCelcius) {
        Serial << ANSI_VERT  << F("C  ") << ANSI_BLANC;
    } else {
        Serial << ANSI_JAUNE << F("F  ") << ANSI_BLANC;
    }
} // afficherUniteTemperature()

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
// sur la meme ligne que "Systeme demarre depuis :"
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

    // snprintf() - jours en jaune, "jour(s)" en blanc, temps en jaune
    char bufferNbJours[10];
    char bufferMot[10];
    char bufferTemps[15];

    snprintf(bufferNbJours, sizeof(bufferNbJours), "%lu ", jours);
    snprintf(bufferMot,     sizeof(bufferMot),     "jour%s  ", (jours == 1 ? "" : "s"));
    snprintf(bufferTemps,   sizeof(bufferTemps),   "%02d:%02d:%02lu", heures, minutes, secondes);

    ansi.gotoXY(COL_TEMPS, LIGNE_TEMPS);
    Serial << ANSI_JAUNE << bufferNbJours << ANSI_BLANC << bufferMot
           << ANSI_JAUNE << bufferTemps   << ANSI_BLANC << F("   ");

    // Affichage LCD ligne 2
    char lcdBuffer[17];
    snprintf(lcdBuffer, sizeof(lcdBuffer), "-> %02lu:%02d:%02d:%02lu",
             jours, heures, minutes, secondes);
    lcd.setCursor(LCD_PREMIERE_COL, LCD_LIGNE2);
    lcd.print(lcdBuffer);

} // afficherTempsEcoule()

// ============================================================
// afficherRTC()
// Lit le RTC DS1307 et affiche la date et l'heure sur
// la ligne avec fond bleu du terminal
// ============================================================
void afficherRTC() {
    horloge.getTime();

    char buffer[70];
    snprintf(buffer, sizeof(buffer), " Nous sommes %s, le %d %s %d et il est %02d:%02d:%02d",
             nomDesJours[horloge.dayOfWeek],
             horloge.dayOfMonth,
             nomDesMois[horloge.month],
             horloge.year + 2000,
             horloge.hour,
             horloge.minute,
             horloge.second);

    ansi.gotoXY(2, LIGNE_RTC);
    Serial << ANSI_FOND_BLEU << ANSI_BLANC << buffer;
    // Remplir le reste avec des espaces pour rester dans la boite (67 caracteres max)
    int longueurTexte = strlen(buffer);
    for (int i = longueurTexte; i < 67; i++) {
        Serial.print(' ');
    }
    Serial << ANSI_BLANC;

} // afficherRTC()

// ============================================================
// afficherCompteur()
// Affiche le compteur de messages et l'etat des appareils
// en binaire sur la ligne avec fond rouge du terminal
// ============================================================
void afficherCompteur() {
    char bufferCompteur[35];
    char bufferBits[10];
    char bufferAppareils[30];

    snprintf(bufferCompteur, sizeof(bufferCompteur), " Compteur msg vers MEGA-> %lu", compteurMEGA);

    // Construire la représentation binaire de etatAppareils
    unsigned int etats = unSysteme.appareils.etatAppareils;
    for (int i = 7; i >= 0; i--) {
        bufferBits[7 - i] = ((etats >> i) & 1) ? '1' : '0';
    }
    bufferBits[8] = '\0';

    snprintf(bufferAppareils, sizeof(bufferAppareils), "    Appareils (bits): %s", bufferBits);

    ansi.gotoXY(2, LIGNE_COMPTEUR);
    Serial << ANSI_FOND_ROUGE << ANSI_BLANC;
    Serial << bufferCompteur;
    Serial << bufferAppareils;
    // Remplir le reste avec des espaces pour rester dans la boite (67 caracteres max)
    int longueurTotale = strlen(bufferCompteur) + strlen(bufferAppareils);
    for (int i = longueurTotale; i < 67; i++) {
        Serial.print(' ');
    }
    Serial << ANSI_BLANC;

} // afficherCompteur()

// ============================================================
// lirePotentiometre()
// Lit la valeur du potentiometre et la convertit en 1-10
// ============================================================
void lirePotentiometre() {
    int valeurBrute = analogRead(PIN_POT);
    dureeAlarme     = map(valeurBrute, VALEUR_POT_MIN, VALEUR_POT_MAX, DUREE_ALARME_MIN, DUREE_ALARME_MAX);

    // Afficher la duree d'alarme
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d sec  ", dureeAlarme);
    ansi.gotoXY(COL_TEMP_VAL, LIGNE_DUREE);
    Serial << ANSI_VERT << buffer << ANSI_BLANC;

} // lirePotentiometre()

// ============================================================
// preparerEtEnvoyerSysteme()
// Prepare la structure Systeme et la transmet au MEGA
// ============================================================
void preparerEtEnvoyerSysteme() {
    // Renseigner le nom du systeme
    strncpy(unSysteme.nomSysteme, "E00000000", MAX_CAR_NOM_SYSTEME);

    // Renseigner le code message
    unSysteme.codeMessage = evenement_statut_appareils;

    // Renseigner l'heure du RTC
    horloge.getTime();
    unSysteme.heure   = horloge.hour;
    unSysteme.minute  = horloge.minute;
    unSysteme.seconde = horloge.second;

    // Renseigner l'etat des appareils sur les bits
    unsigned int etats = 0;
    etats |= digitalRead(PIN_LED1)   ? APP_LED1           : 0;
    etats |= digitalRead(PIN_LED2)   ? APP_LED2           : 0;
    etats |= digitalRead(PIN_RELAI)  ? APP_RELAI          : 0;
    etats |= etatPIR                 ? APP_MOUVEMENT      : 0;
    etats |= etatPIR                 ? APP_MOUVEMENT_ARME : 0;
    etats |= etatBoutonPanique       ? APP_BOUTON_PANIQUE : 0;
    etats |= etatRetroLCD            ? APP_RETRO_LCD      : 0;
    etats |= affichageCelcius        ? APP_UNITE_TEMP     : 0;

    unSysteme.appareils.etatAppareils = etats;
    unSysteme.appareils.temperature   = sht31.getTemperature();
    unSysteme.appareils.humidite      = sht31.getHumidity();
    unSysteme.appareils.dureeAlarme   = dureeAlarme;

    // Transmettre la structure au MEGA
    lienAvecMEGA.write((byte*)&unSysteme, sizeof(unSysteme));
    compteurMEGA++;

} // preparerEtEnvoyerSysteme()

// ============================================================
// setup()
// ============================================================
void setup() {
    Serial.begin(VITESSE_UART);

    // Initialisation des broches
    pinMode(PIN_LED1,          OUTPUT);
    pinMode(PIN_LED2,          OUTPUT);
    pinMode(PIN_RELAI,         OUTPUT);
    pinMode(PIN_ALARME,        OUTPUT);
    pinMode(PIN_PIR,           INPUT);
    pinMode(PIN_BOUTON_PANIQUE,INPUT);

    // Initialisation SoftwareSerial vers le MEGA
    lienAvecMEGA.begin(VITESSE_SOFT_SERIAL);

    // Initialisation I2C
    Wire.begin();
    sht31.begin();

    // Initialisation RTC
    horloge.begin();

    // Initialisation LCD
    lcd.begin(LCD_NB_COLONNE, LCD_NB_LIGNE);
    lcd.setRGB(0, 128, 255);
    lcd.setCursor(LCD_PREMIERE_COL, LCD_LIGNE1);
    lcd.print(F("Alarme : ON"));

    // Affichage de l'interface dans le terminal serie
    ansi.clearScreen();
    Serial << CURSEUR_OFF << ANSI_BLANC;
    Serial << F("╔═══════════════════════════════════════════════════════════════════╗\n");
    Serial << F("║                  Station de contrôle UNO 3.0                      ║\n");
    Serial << F("╟───────────────────────────────────────────────────────────────────╢\n");
    Serial << F("║ 1 - LED1  sur "); Serial << ANSI_BLEU << F("D2") << ANSI_BLANC; Serial << F("                                                  ║\n");
    Serial << F("║ 2 - LED2  sur "); Serial << ANSI_BLEU << F("D3") << ANSI_BLANC; Serial << F("                                                  ║\n");
    Serial << F("║ 3 - Relai sur "); Serial << ANSI_BLEU << F("D4") << ANSI_BLANC; Serial << F("                                                  ║\n");
    Serial << F("║ 4 - Celcius/Fahrenheit sur "); Serial << ANSI_BLEU << F("I2C") << ANSI_BLANC; Serial << F("                                    ║\n");
    Serial << F("║ 5 - Détecteur de mouvement sur "); Serial << ANSI_BLEU << F("D5") << ANSI_BLANC; Serial << F("                                 ║\n");
    Serial << F("║ 6 - LCD Rétro-éclairage                                           ║\n");
    Serial << F("║ 7 - Bouton panique "); Serial << ANSI_BLEU << F("D7") << ANSI_BLANC; Serial << F(" - Interruption matérielle                   ║\n");
    Serial << F("╟───────────────────────────────────────────────────────────────────╢\n");
    Serial << F("║ Détecteur de mouvement : Alarme sur "); Serial << ANSI_BLEU << F("D6") << ANSI_BLANC; Serial << F("                            ║\n");
    Serial << F("║ Température            :                                          ║\n");
    Serial << F("║ Humidité               :                                          ║\n");
    Serial << F("║ Durée d'alarme/panique :                                          ║\n");
    Serial << F("╟───────────────────────────────────────────────────────────────────╢\n");
    Serial << F("║ Système démarré depuis :                             Option:      ║\n");
    Serial << F("╟───────────────────────────────────────────────────────────────────╢\n");
    Serial << F("║                                                                   ║\n");
    Serial << F("╟───────────────────────────────────────────────────────────────────╢\n");
    Serial << F("║                                                                   ║\n");
    Serial << F("╟───────────────────────────────────────────────────────────────────╢\n");
    Serial << F("║ Projet réalisé par Yannick Kananin                   TP02--> UNO  ║\n");
    Serial << F("╚═══════════════════════════════════════════════════════════════════╝\n");

    // Affichage initial des etats
    afficherOnOff(COL_ONOFF, LIGNE_LED1,           etatLED1);
    afficherOnOff(COL_ONOFF, LIGNE_LED2,           etatLED2);
    afficherOnOff(COL_ONOFF, LIGNE_RELAI,          etatRELAI);
    afficherUniteTemperature();
    afficherOnOff(COL_ONOFF, LIGNE_PIR,            etatPIR);
    afficherOnOff(COL_ONOFF, LIGNE_LCD_RETRO,      etatRetroLCD);
    afficherOnOff(COL_ONOFF, LIGNE_BOUTON_PANIQUE, etatBoutonPanique);

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
        if (commande == '4') {
            affichageCelcius = !affichageCelcius;
            afficherUniteTemperature();
        }
        if (commande == '5') {
            etatPIR = !etatPIR;
            afficherOnOff(COL_ONOFF, LIGNE_PIR, etatPIR);
        }
        if (commande == '6') {
            etatRetroLCD = !etatRetroLCD;
            if (etatRetroLCD) {
                lcd.setRGB(0, 128, 255);
            } else {
                lcd.setRGB(0, 0, 0);
            }
            afficherOnOff(COL_ONOFF, LIGNE_LCD_RETRO, etatRetroLCD);
        }

        // Afficher la touche saisie
        ansi.gotoXY(COL_OPTION, LIGNE_OPTION);
        Serial << ANSI_JAUNE << commande << ANSI_BLANC;
    }

    // Lecture du bouton panique
    if (digitalRead(PIN_BOUTON_PANIQUE) == HIGH) {
        etatBoutonPanique = true;
        afficherOnOff(COL_ONOFF, LIGNE_BOUTON_PANIQUE, etatBoutonPanique);
    } else {
        if (etatBoutonPanique) {
            etatBoutonPanique = false;
            afficherOnOff(COL_ONOFF, LIGNE_BOUTON_PANIQUE, etatBoutonPanique);
        }
    }

    // Lecture du detecteur de mouvement PIR
    bool mouvementDetecte = digitalRead(PIN_PIR);
    if (mouvementDetecte != etatPIR) {
        etatPIR = mouvementDetecte;
        digitalWrite(PIN_ALARME, etatPIR ? HIGH : LOW);
        afficherOnOff(COL_ONOFF, LIGNE_ALARME, etatPIR);
    }

    // Lecture potentiometre toutes les 500ms
    static unsigned long dernierePot = 0;
    if (millis() - dernierePot >= 500) {
        dernierePot = millis();
        lirePotentiometre();
    }

    // Temperature et Humidite toutes les 2 secondes
    static unsigned long derniereLecture = 0;
    if (millis() - derniereLecture >= DELAI_LECTURE_SHT) {
        derniereLecture = millis();
        afficherTemperatureEtHumidite(COL_TEMP_VAL, LIGNE_TEMP);
    }

    // RTC toutes les secondes
    static unsigned long derniereRTC = 0;
    if (millis() - derniereRTC >= 1000) {
        derniereRTC = millis();
        afficherRTC();
    }

    // Transmission vers le MEGA toutes les secondes
    static unsigned long derniereTransmission = 0;
    if (millis() - derniereTransmission >= DELAI_TRANSMISSION) {
        derniereTransmission = millis();
        preparerEtEnvoyerSysteme();
        afficherCompteur();
    }

    // Temps ecoule
    afficherTempsEcoule();

} // loop()

// FIN DU FICHIER