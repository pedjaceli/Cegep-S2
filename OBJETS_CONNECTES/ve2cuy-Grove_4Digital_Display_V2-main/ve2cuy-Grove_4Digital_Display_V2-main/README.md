Grove_4Digital_Display V2 by VE2CUY
--------------------------------

![Grove_4Digital_Display](https://statics3.seeedstudio.com/images/product/4-Digital%20Display.jpg)

[Grove - 4-Digit Display](https://www.seeedstudio.com/Grove-4-Digit-Display-p-1198.html)

### Ajout des méthodes suivantes:

info()

begin()

Ajout des macros:

#define ECRAN_FAIBLE 0

#define ECRAN_MOYEN 2

#define ECRAN_FORT 7

---

### Propose les méthodes suivantes:

displayStr(str, delay_ms = 0);

displayNum(PI, 2);
    
----

### Exemple d'utilisation

```
#include <Arduino.h>
#include "TM1637V2.h"

// Définition des broches pour la TM1637
const int CLK = A10, DIO = A11;
TM1637V2 tm1637(CLK, DIO);

void afunction(){
    tm1637.init();
    Serial.begin(9600);
    Serial.println(tm1637.info());              // Obtenir de l'info sur la librairie
    tm1637.set(ECRAN_FORT);                     // Luminosité au maximum
    tm1637.displayNum(PI, 2);
    tm1637.displayStr("Bonjour 420-1C4", 300);  // Afficher une message avec 'scroll' au besoin
}
```

Version originale de Frankie.Chu for [Seeed Technology Inc.](http://www.seeed.cc) and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt/LICENSE for the details of MIT license. The TimerOne library is refered from the arduino community and its copyright follows the original.
