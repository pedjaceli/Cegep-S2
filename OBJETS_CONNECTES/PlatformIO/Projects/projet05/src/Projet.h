#ifndef projet_h
#define projet_h

// ============================================================
// Inclusion des librairies
// ============================================================
#include <Arduino.h>
#include "ansi.h"
#include <Streaming.h>
#include <Wire.h>
#include "SHT31.h"
#include "rgb_lcd.h"
#include "DS1307.h"
#include <SoftwareSerial.h>

// ============================================================
// Les macros – séquences ANSI
// ============================================================
#define ANSI_ROUGE          "\033[31m"
#define ANSI_VERT           "\033[32m"
#define ANSI_BLEU           "\033[34m"
#define ANSI_JAUNE          "\033[33m"
#define ANSI_BLANC          "\033[0m"
#define ANSI_FOND_ROUGE     "\033[41m"
#define ANSI_FOND_BLEU      "\033[44m"
#define CURSEUR_ON          "\033[?25h"
#define CURSEUR_OFF         "\033[?25l"

// ============================================================
// Les macros – broches
// ============================================================
#define PIN_LED1            2
#define PIN_LED2            3
#define PIN_RELAI           4
#define PIN_PIR             5
#define PIN_ALARME          6
#define PIN_BOUTON_PANIQUE  7
#define PIN_POT             A0
#define PIN_SOFT_RX         9
#define PIN_SOFT_TX         8

// ============================================================
// Les macros – LCD
// ============================================================
#define LCD_NB_COLONNE      16
#define LCD_NB_LIGNE        2
#define LCD_LIGNE1          0
#define LCD_LIGNE2          1
#define LCD_PREMIERE_COL    0

// ============================================================
// Les macros – positions curseur terminal (col, ligne) 1-based
// ============================================================
#define COL_ONOFF               60
#define LIGNE_LED1               4
#define LIGNE_LED2               5
#define LIGNE_RELAI              6
#define LIGNE_CELCIUS_FAHRENHEIT 7
#define LIGNE_PIR                8
#define LIGNE_LCD_RETRO          9
#define LIGNE_BOUTON_PANIQUE    10
#define COL_OPTION              64
#define COL_TEMP_VAL            60
#define LIGNE_ALARME            12
#define LIGNE_TEMP              13
#define LIGNE_HUM               14
#define LIGNE_DUREE             15
#define COL_TEMPS               28
#define LIGNE_TEMPS             17
#define LIGNE_OPTION            LIGNE_TEMPS
#define LIGNE_RTC               19
#define LIGNE_COMPTEUR          21

// ============================================================
// Les macros – calcul du temps
// ============================================================
#define SECONDES_PAR_JOUR       86400
#define SECONDES_PAR_HEURE      3600
#define SECONDES_PAR_MINUTE     60

// ============================================================
// Les macros – noms des jours et mois
// ============================================================
#define NB_JOURS_SEMAINE    8
#define NB_MOIS             13

// ============================================================
// Les macros – divers
// ============================================================
#define VITESSE_UART            4800
#define DELAI_LECTURE_SHT       2000
#define VITESSE_SOFT_SERIAL     57600
#define DELAI_TRANSMISSION      1000
#define MAX_CAR_NOM_SYSTEME     10
#define VALEUR_POT_MIN          0
#define VALEUR_POT_MAX          1023
#define DUREE_ALARME_MIN        1
#define DUREE_ALARME_MAX        10

// ============================================================
// Les énumérations
// ============================================================
enum EtatAppareils {
    APP_LED1             = 0b1 << 0,  // 0000 0001
    APP_LED2             = 0b1 << 1,  // 0000 0010
    APP_RELAI            = 0b1 << 2,  // 0000 0100
    APP_MOUVEMENT        = 0b1 << 3,  // 0000 1000
    APP_MOUVEMENT_ARME   = 0b1 << 4,  // 0001 0000
    APP_BOUTON_PANIQUE   = 0b1 << 5,  // 0010 0000
    APP_RETRO_LCD        = 0b1 << 6,  // 0100 0000
    APP_UNITE_TEMP       = 0b1 << 7   // 1000 0000
};

enum Evenements {
    evenement_statut_appareils,       // 0
    evenement_temperature_depassee,   // 1
    evenement_detection_mouvement,    // 2
    evenement_bouton_panique,         // 3
    evenement_systeme_enligne,        // 4
    evenement_changement_etat,        // 5
    evenement_UNO_non_connecte,       // 6
    evenement_nb_codes                // 7
};

// ============================================================
// Les structures de données
// ============================================================
struct Appareils {
    unsigned int  etatAppareils;  // Traitement sur les bits  // 2 octets
    float         temperature;                                // 4 octets
    float         humidite;                                   // 4 octets
    int           dureeAlarme;                                // 2 octets
};

struct Systeme {
    // ATTENTION de ne pas dépasser 9 caractères pour le nom du système!!!
    char        nomSysteme[MAX_CAR_NOM_SYSTEME];  // 10 octets
    Evenements  codeMessage;                      //  2 octets
    byte        heure;                            //  1 octet
    byte        minute;                           //  1 octet
    byte        seconde;                          //  1 octet
    Appareils   appareils;                        // 12 octets
};

#endif