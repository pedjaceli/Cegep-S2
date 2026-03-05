# - - - - - - - - - - - - - - - - - - - - - - - - - - -
/*

TP1 SQL 2026
ÉCRIVEZ VOTRE MATRICULE SUR LA LIGNE SUIVANTE:
2539709

*/
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 01
SELECT COUNT(*) AS NombreEtudiants FROM Sondage_Poudlard WHERE statut_sang = "Sang-Pur"
AND maison = "Gryffondor"
AND animal_compagnon = "Chat"
AND richesse = "Riche";
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 02
SELECT nom_complet, maison FROM Sondage_Poudlard WHERE date_naissance > "2000-01-01"
AND sport_prefere = "Quidditch"
AND(couleur_preferee = "Rouge" OR couleur_preferee = "Or");
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 03
SELECT sport_prefere FROM Sondage_Poudlard WHERE maison = "Serdaigle"
AND niveau_etude >= 5
GROUP BY sport_prefere
ORDER BY COUNT(*) DESC
LIMIT 1;
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 04
SELECT nom_complet, date_naissance FROM Sondage_Poudlard WHERE maison = "Poufsouffle"
AND animal_compagnon = "Boursoufet"
AND situation_familiale != "Célibataire" ORDER BY date_naissance DESC;
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 05
SELECT maison, COUNT(*) AS NombreEtudiants
FROM Sondage_Poudlard 
WHERE animal_compagnon = "Corbeau"
AND film_prefere = "Star Wars" 
AND richesse = "Moyen"
GROUP BY maison
HAVING COUNT(*) >= 8;
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 06
SELECT DISTINCT secteur_activite FROM Sondage_Poudlard WHERE animal_compagnon = "Crapaud"
AND statut_sang = "Sang-Mêlé"
AND continent = "Amérique du Nord"
AND secteur_activite IS NOT NULL;
	
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 07
SELECT COUNT(*) AS NombreEtudiants FROM Sondage_Poudlard WHERE situation_familiale = "C'est compliqué"
AND niveau_etude BETWEEN 3 AND 5
AND sport_prefere = "Plongeon dans le Lac Noir";
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 08
SELECT nom_complet, date_naissance FROM Sondage_Poudlard 
WHERE animal_compagnon = "Rat"
AND secteur_activite = "Botanique"
AND continent = "Amérique du Sud"
ORDER BY date_naissance ASC
LIMIT 1;
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 09
SELECT sexe, COUNT(*) AS NombreEtudiants FROM Sondage_Poudlard
WHERE film_prefere = "Indiana Jones"
AND sport_prefere = "Duel de sorciers"
AND richesse = "Pauvre"
AND pays IN("Royaume-Uni", "Irlande", "Pérou", "France", "Chine", "Ouganda")
GROUP BY sexe;
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 10
SELECT pays, COUNT(*) AS NombreEtudiants FROM Sondage_Poudlard
WHERE secteur_activite = "Potions"
AND maison = "Serpentard"
AND richesse = "Moyen"
AND sexe = "Femme"
GROUP BY pays;
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 11
SELECT nom_complet, maison, couleur_preferee FROM Sondage_Poudlard
WHERE secteur_activite = "Arithmancie"
AND statut_sang = "Sang-Mêlé"
AND richesse = "Riche"
AND sport_prefere = "Quidditch"
AND niveau_etude BETWEEN 5 AND 7
AND couleur_preferee != "Argent"
ORDER BY niveau_etude DESC;
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 12
SELECT chanson_preferee, COUNT(*) AS NombreEtudiants FROM Sondage_Poudlard
WHERE situation_familiale IN("Marié(e)", "Fiancé(e)")
AND continent = "Europe"
AND maison = "Serpentard"
AND film_prefere IN("Star Wars", "Indiana Jones")
GROUP BY chanson_preferee
HAVING NombreEtudiants >= 2;
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 13
SELECT continent, COUNT(*) AS NombreEtudiants, MIN(niveau_etude) AS NiveauMinEtude, 
MAX(niveau_etude) AS NiveauMaxEtude, AVG(niveau_etude) AS MoyenneNiveauEtude
FROM Sondage_Poudlard
WHERE sport_prefere = "Bavboules"
AND maison = "Gryffondor"
AND date_naissance BETWEEN "1980-01-01" AND "1989-12-31"
GROUP BY continent
HAVING COUNT(*) > 1;
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 14
SELECT * FROM Sondage_Poudlard
WHERE film_prefere = "Shrek"
AND couleur_preferee = "Vert"
AND animal_compagnon = "Crapaud"
AND richesse = "Pauvre"
AND (nom_complet LIKE "R%" OR nom_complet LIKE "O%");
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 15
SELECT CONCAT("L'étudiant(e) ", nom_complet, ", originaire de ", UPPER(SUBSTRING(pays, 1, 3)), 
", né(e) le jour ", DAY(date_naissance), " du mois, écoute ", chanson_preferee, " avec son ", animal_compagnon,".")
AS profil_magique FROM Sondage_Poudlard
WHERE animal_compagnon != "Aucun"
AND DAY(date_naissance) > 14
AND maison = "Serdaigle"
AND niveau_etude = 7;
# - - - - - - - - - - - - - - - - - - - - - - - - - - -