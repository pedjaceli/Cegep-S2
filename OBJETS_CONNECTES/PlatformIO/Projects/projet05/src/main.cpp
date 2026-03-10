/*
    Solution du laboratoire 2.4
    Auteur:       Alain Boudreault
    Date:         2021.10.22
    Description:  Allumer une séquence de pixels rouge, vert, ...
*/

#include <Adafruit_NeoPixel.h>
#define PIN           2         // GPIO de connexion de la barre de pixels
#define NUMPIXELS     10        // NB de pixels sur la barre
#define DELAYVAL      250       // Intervalle entre les pixels
#define PIXEL_ROUGE   255,0,0   // r = 255, g = 0, b = 0
#define PIXEL_VERT    0,255,0   // r = 0, g = 255, b = 0
#define UNE_SECONDE   1000

// Création d'un objet de type Adafruit_NeoPixel pour le contrôle de la barre de pixels.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
} // setup

void loop() {
  pixels.clear(); // Effacer tous les pixels.
 
  for(int i=0; i<NUMPIXELS; i++) { 
    // Déterminer la couleur du pixel en fonction d'une division par 2.
    uint32_t couleur = (i % 2) ? pixels.Color(PIXEL_VERT):pixels.Color(PIXEL_ROUGE);
    pixels.setPixelColor(i, couleur);
    pixels.show();   // Actualiser l'affichage
    delay(DELAYVAL);
  } // for

  delay(UNE_SECONDE);

} // loop