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

// ============================================================
// Les macros – séquences ANSI
// ============================================================
#define ANSI_ROUGE          "\033[31m"
#define ANSI_VERT           "\033[32m"
#define ANSI_BLEU           "\033[34m"
#define ANSI_JAUNE          "\033[33m"
#define ANSI_BLANC          "\033[0m"
#define ANSI_FOND_BLEU      "\033[104m"
#define CURSEUR_ON          "\033[?25h"
#define CURSEUR_OFF         "\033[?25l"

// ============================================================
// Les macros – broches
// ============================================================
#define PIN_LED1            2
#define PIN_LED2            3
#define PIN_RELAI           4
#define PIN_PIR             5
#define PIN_BUZZER          6
#define PIN_BOUTON          7
#define PIN_POT             A0

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
#define COL_ONOFF               56
#define LIGNE_LED1               4
#define LIGNE_LED2               5
#define LIGNE_RELAI              6
#define LIGNE_CELCIUS_FAHRENHEIT 7
#define LIGNE_PIR                8
#define LIGNE_LCD_RETRO          9
#define COL_OPTION              64
#define COL_TEMP_VAL            56
#define LIGNE_ALARME            11
#define LIGNE_TEMP              12
#define LIGNE_HUM               13
#define LIGNE_POT               14
#define COL_TEMPS               17
#define LIGNE_TEMPS             16
#define LIGNE_OPTION            LIGNE_TEMPS
#define LIGNE_RTC               18

// ============================================================
// Les macros – calcul du temps
// ============================================================
#define SECONDES_PAR_JOUR       86400
#define SECONDES_PAR_HEURE      3600
#define SECONDES_PAR_MINUTE     60

// ============================================================
// Les macros – divers
// ============================================================
#define VITESSE_UART            4800
#define DELAI_LECTURE_SHT       2000
#define VALEUR_POT_MIN          0
#define VALEUR_POT_MAX          1023
#define CELSIUS_VERS_FAHRENHEIT(c) ((c) * 9.0 / 5.0 + 32.0)

#endif