/*
   Projet:  TP01 - Partie 02
   Fichier: main.cpp
   Auteur:  Yannick Kananin
   Date:    2026-03-21
   -----------------------------------------------
   Description:
      Station de contrôle 420-1C4 version 2.0
      - Contrôle LED1 (D2), LED2 (D3), Relai (D4)
      - Détecteur de mouvement PIR (D5)
      - Buzzer alarme (D6)
      - Bouton activation/désactivation PIR (D7)
      - Potentiomètre délai affichage (A0)
      - Affichage température et humidité (SHT31)
      - Affichage temps écoulé (jours/heures/minutes/secondes)
      - Affichage date et heure (RTC DS1307)
      - Affichage sur LCD RGB (Alarme + temps écoulé)
   -----------------------------------------------
   M-A-J: Début de la partie 2
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
DS1307  horloge;

// ============================================================
// Déclaration des variables globales
// ============================================================
bool etatLED1         = false;
bool etatLED2         = false;
bool etatRELAI        = false;
bool affichageCelcius = true;
bool detecteurActif   = true;
bool etatRetroLCD     = true;

// Tableaux pour le RTC
const char* nomDesJours[] = {"", "Dimanche", "Lundi", "Mardi", "Mercredi",
                              "Jeudi", "Vendredi", "Samedi"};
const char* nomDesMois[]  = {"", "Janvier", "Fevrier", "Mars", "Avril", "Mai",
                              "Juin", "Juillet", "Aout", "Septembre",
                              "Octobre", "Novembre", "Decembre"};

// ============================================================
// Prototypes des fonctions
// ============================================================
void afficherOnOff(int posX, int posY, bool on = true);
void afficherTemperatureEtHumidite(int posX, int posY);
void afficherTempsEcoule();
void afficherActifDesactif(int posX, int posY, bool actif);
void afficherUniteTemperature();
void afficherRTC();
void lirePotentiometre();
void gererDetecteurMouvement();

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
// afficherActifDesactif()
// Affiche Activé (vert) ou Désactivé (rouge) a la position
// ============================================================
void afficherActifDesactif(int posX, int posY, bool actif) {
    ansi.gotoXY(posX, posY);
    if (actif) {
        Serial << ANSI_VERT  << F("Active    ") << ANSI_BLANC;
    } else {
        Serial << ANSI_ROUGE << F("Desactive ") << ANSI_BLANC;
    }
} // afficherActifDesactif()

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
// Gere l'affichage en Celsius ou Fahrenheit avec 2 decimales
// ============================================================
void afficherTemperatureEtHumidite(int posX, int posY) {
    float temperature = sht31.getTemperature();
    float humidite    = sht31.getHumidity();

    ansi.gotoXY(posX, posY);
    Serial << ANSI_VERT;
    if (affichageCelcius) {
        Serial.print(temperature, 2);
        Serial << F(" C   ");
    } else {
        Serial.print(CELSIUS_VERS_FAHRENHEIT(temperature), 2);
        Serial << F(" F   ");
    }
    Serial << ANSI_BLANC;

    ansi.gotoXY(posX, posY + 1);
    Serial << ANSI_VERT;
    Serial.print(humidite, 2);
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

    // Construire chaque partie separement pour eviter les debordements
    char bufferJour[12];
    char bufferMois[12];
    char bufferHeure[12];
    char bufferDate[5];
    char bufferAnnee[6];

    snprintf(bufferJour,  sizeof(bufferJour),  "%s", nomDesJours[horloge.dayOfWeek]);
    snprintf(bufferDate,  sizeof(bufferDate),   "%d", horloge.dayOfMonth);
    snprintf(bufferMois,  sizeof(bufferMois),  "%s", nomDesMois[horloge.month]);
    snprintf(bufferAnnee, sizeof(bufferAnnee), "%d", horloge.year + 2000);
    snprintf(bufferHeure, sizeof(bufferHeure), "%02d:%02d:%02d",
             horloge.hour, horloge.minute, horloge.second);

    ansi.gotoXY(2, LIGNE_RTC);
    Serial << ANSI_FOND_BLEU << ANSI_BLANC;
    Serial << F(" Nous sommes ") << bufferJour;
    Serial << F(", le ")         << bufferDate;
    Serial << F(" ")             << bufferMois;
    Serial << F(" ")             << bufferAnnee;
    Serial << F(" et il est ")   << bufferHeure;
    Serial << F("          ")    << ANSI_BLANC;

} // afficherRTC()

// ============================================================
// lirePotentiometre()
// Lit la valeur du potentiometre et l'utilise comme delai
// d'affichage de la boucle principale
// ============================================================
void lirePotentiometre() {
    int delaiMs = analogRead(PIN_POT);

    // Afficher la valeur du delai
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d ms  ", delaiMs);
    ansi.gotoXY(COL_TEMP_VAL, LIGNE_POT);
    Serial << ANSI_VERT << buffer << ANSI_BLANC;

} // lirePotentiometre()

// ============================================================
// gererDetecteurMouvement()
// Gere la detection de mouvement, le buzzer et le LCD rouge
// ============================================================
void gererDetecteurMouvement() {
    if (!detecteurActif) return;

    if (digitalRead(PIN_PIR) == HIGH) {
        // Mouvement détecté — alarme !
        afficherOnOff(COL_TEMP_VAL, LIGNE_ALARME, true);

        // LCD rouge + message alarme
        lcd.setRGB(255, 0, 0);
        lcd.setCursor(LCD_PREMIERE_COL, LCD_LIGNE1);
        lcd.print(F("** INTRUSION **"));

        // Sonner le buzzer
        digitalWrite(PIN_BUZZER, HIGH);

        // Attendre que le mouvement revienne a OFF
        while (digitalRead(PIN_PIR) == HIGH);

        // Retablir l'etat normal
        digitalWrite(PIN_BUZZER, LOW);

        // Retablir le LCD
        if (etatRetroLCD) {
            lcd.setRGB(0, 128, 255);
        } else {
            lcd.setRGB(0, 0, 0);
        }
        lcd.setCursor(LCD_PREMIERE_COL, LCD_LIGNE1);
        if (detecteurActif) {
            lcd.print(F("Alarme : ON     "));
        } else {
            lcd.print(F("Alarme : OFF    "));
        }

        afficherOnOff(COL_TEMP_VAL, LIGNE_ALARME, false);
    }

} // gererDetecteurMouvement()

// ============================================================
// setup()
// ============================================================
void setup() {
    Serial.begin(VITESSE_UART);

    // Initialisation des broches
    pinMode(PIN_LED1,   OUTPUT);
    pinMode(PIN_LED2,   OUTPUT);
    pinMode(PIN_RELAI,  OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_PIR,    INPUT);
    pinMode(PIN_BOUTON, INPUT);

    // Initialisation I2C
    Wire.begin();
    sht31.begin();

    // Initialisation RTC
    horloge.begin();

    // *** Décommenter #define SET_TIME pour régler l'heure ***
    // *** Puis remettre en commentaire et retéléverser      ***
    // #define SET_TIME
    #ifdef SET_TIME
        horloge.fillByYMD(2026, 3, 21);  // Année, Mois, Jour
        horloge.fillByHMS(14, 30, 0);    // Heure, Minute, Seconde
        horloge.fillDayOfWeek(SAT);      // SUN MON TUE WED THU FRI SAT
        horloge.setTime();
    #endif

    // Initialisation LCD
    lcd.begin(LCD_NB_COLONNE, LCD_NB_LIGNE);
    lcd.setRGB(0, 128, 255);
    lcd.setCursor(LCD_PREMIERE_COL, LCD_LIGNE1);
    lcd.print(F("Alarme : ON"));

    // Affichage de l'interface dans le terminal serie
    ansi.clearScreen();
    Serial << CURSEUR_OFF << ANSI_BLANC;
    Serial << F("╔═══════════════════════════════════════════════════════════════════╗\n");
    Serial << F("║"); Serial << ANSI_FOND_BLEU << ANSI_BLANC;
    Serial << F("           Station de contrôle 420-1C4 version 2.0                 ");
    Serial << ANSI_BLANC << F("║\n");
    Serial << F("╟───────────────────────────────────────────────────────────────────╢\n");
    Serial << F("║ 1 - LED1  sur "); Serial << ANSI_BLEU << F("D2") << ANSI_BLANC;
    Serial << F("                                                  ║\n");
    Serial << F("║ 2 - LED2  sur "); Serial << ANSI_BLEU << F("D3") << ANSI_BLANC;
    Serial << F("                                                  ║\n");
    Serial << F("║ 3 - Relai sur "); Serial << ANSI_BLEU << F("D4") << ANSI_BLANC;
    Serial << F("                                                  ║\n");
    Serial << F("║ 4 - Celcius/Fahrenheit sur "); Serial << ANSI_BLEU << F("I2C") << ANSI_BLANC;
    Serial << F("                                    ║\n");
    Serial << F("║ 5 - Detecteur de mouvement sur "); Serial << ANSI_BLEU << F("D5") << ANSI_BLANC;
    Serial << F(" (BTN "); Serial << ANSI_BLEU << F("D7") << ANSI_BLANC;
    Serial << F(": ON/OFF)                ║\n");
    Serial << F("║ 6 - LCD Retro-eclairage                                           ║\n");
    Serial << F("╟───────────────────────────────────────────────────────────────────╢\n");
    Serial << F("║ Detecteur de mouvement : Alarme sur "); Serial << ANSI_BLEU << F("D6") << ANSI_BLANC;
    Serial << F("                            ║\n");
    Serial << F("║ Temperature            :                                          ║\n");
    Serial << F("║ Humidite               :                                          ║\n");
    Serial << F("║ Potentiometre          : Delai d'affichage                        ║\n");
    Serial << F("╟───────────────────────────────────────────────────────────────────╢\n");
    Serial << F("║ Temps ecoule:                                        Option:      ║\n");
    Serial << F("╟───────────────────────────────────────────────────────────────────╢\n");
    Serial << F("║                                                                   ║\n");
    Serial << F("╟───────────────────────────────────────────────────────────────────╢\n");
    Serial << F("║ Projet realise par Yannick Kananin               TP01-Partie 02   ║\n");
    Serial << F("╚═══════════════════════════════════════════════════════════════════╝\n");

    // Affichage initial des etats
    afficherOnOff(COL_ONOFF, LIGNE_LED1,  etatLED1);
    afficherOnOff(COL_ONOFF, LIGNE_LED2,  etatLED2);
    afficherOnOff(COL_ONOFF, LIGNE_RELAI, etatRELAI);
    afficherUniteTemperature();
    afficherActifDesactif(COL_ONOFF, LIGNE_PIR,      detecteurActif);
    afficherOnOff(COL_ONOFF,         LIGNE_LCD_RETRO, etatRetroLCD);
    afficherOnOff(COL_TEMP_VAL,      LIGNE_ALARME,    false);

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
            detecteurActif = !detecteurActif;
            afficherActifDesactif(COL_ONOFF, LIGNE_PIR, detecteurActif);
            // Mettre a jour le LCD
            lcd.setCursor(LCD_PREMIERE_COL, LCD_LIGNE1);
            if (detecteurActif) {
                lcd.print(F("Alarme : ON     "));
            } else {
                lcd.print(F("Alarme : OFF    "));
            }
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

    // Lecture du bouton D7 — meme fonction que touche 5
    static bool dernierEtatBouton = LOW;
    bool etatBouton = digitalRead(PIN_BOUTON);
    if (etatBouton == HIGH && dernierEtatBouton == LOW) {
        detecteurActif = !detecteurActif;
        afficherActifDesactif(COL_ONOFF, LIGNE_PIR, detecteurActif);
        lcd.setCursor(LCD_PREMIERE_COL, LCD_LIGNE1);
        if (detecteurActif) {
            lcd.print(F("Alarme : ON     "));
        } else {
            lcd.print(F("Alarme : OFF    "));
        }
        delay(50); // anti-rebond
    }
    dernierEtatBouton = etatBouton;

    // Gestion du detecteur de mouvement PIR
    gererDetecteurMouvement();

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

    // Potentiometre toutes les 500ms
    static unsigned long dernierePot = 0;
    if (millis() - dernierePot >= 500) {
        dernierePot = millis();
        lirePotentiometre();
    }

    // Temps ecoule
    afficherTempsEcoule();

    // Delai de la boucle principale selon le potentiometre
    delay(analogRead(PIN_POT));

} // loop()

// FIN DU FICHIER