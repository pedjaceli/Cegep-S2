1. SELECT NomPrenom FROM cours03_etudiants WHERE Ville = "SAINT-JÉRÔME" AND Sexe = "F" ;
2. SELECT * FROM  cours03_etudiants WHERE TitreProgramme = "Soins infirmiers" AND IndicateurFinissant = "Non";
3. SELECT * FROM  cours03_etudiants WHERE TitreProgramme = "Sciences de la nature" AND IndicateurFinissant = "Oui";
4. SELECT * FROM  cours03_etudiants WHERE Ville = "Prévost" OR Ville = "Sainte-Sophie";
5. SELECT * FROM  cours03_etudiants WHERE IndicateurFinissant = "Oui" OR Ville = "Mirabel";
6. SELECT * FROM  cours03_etudiants WHERE Ville = "Montréal" OR Ville = "Laval";
7. SELECT * FROM  cours03_etudiants WHERE NOT TitreProgramme = "Tremplin DEC";
8. SELECT * FROM  cours03_etudiants WHERE NOT DateNaissance LIKE '2002%';
9. SELECT * FROM  cours03_etudiants WHERE TelephoneCellulaire = " ";
10 SELECT * FROM  cours03_etudiants WHERE (TitreProgramme = "Soins infirmiers" OR TitreProgramme = "Sciences de la natur") AND IndicateurFinissant = "Non";
11 SELECT NomPrenom FROM  cours03_etudiants WHERE SEXE = "F" AND TitreProgramme = "Techniques juridiques" AND NOT (Ville = "Saint-Jérôme" OR Ville = "Prévost");
12 SELECT * FROM cours03_etudiants WHERE TelephoneCellulaire = "" AND (Ville = "Sainte-Thérèse" OR Ville = "Boisbriand");
13 SELECT NomPrenom FROM cours03_etudiants WHERE IndicateurFinissant = "Oui" AND NOT Ville = "Saint-Jérôme" AND 
((Sexe = "H" AND TitreProgramme = "Soins infirmiers"  OR  Sexe = "F" AND TitreProgramme = "Techniques d'intégration"));
14 SELECT NomPrenom FROM cours03_etudiants WHERE NOT Ville = "Laval" or Ville = "Mirabel" AND NOT ((TitreProgramme = "Tremplin DEC") AND 
(Sexe = "H" AND IndicateurFinissant = "Oui") OR (Sexe = "F" AND IndicateurFinissant = "Oui")); 