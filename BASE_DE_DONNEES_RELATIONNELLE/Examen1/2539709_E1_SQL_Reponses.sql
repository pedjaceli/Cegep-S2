# - - - - - - - - - - - - - - - - - - - - - - - - - - -
/*

Examen1 SQL 2026
ÉCRIVEZ VOTRE MATRICULE SUR LA LIGNE SUIVANTE:
2539709

*/
# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 01
SELECT DISTINCT pays_origine, COUNT(nom) AS nombre_Participants
FROM Participants
HAVING nombre_Participants > 3;

# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 02
SELECT nom, SUBSTRING(origine, 1, 5) AS code_piment FROM Piments
WHERE arome = "Fruité";

# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 03
SELECT CONCAT('Participant : ', prenom, ' ', nom) AS nom_complet
FROM Participants
WHERE regime_alimentaire != "Carnivore"
OFFSET 10;

# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 04
SELECT espece, origine,
	MIN(shu_min) AS SHU_Minimum,
    MAX(shu_max) AS SHU_Maximum
FROM Piments
GROUP BY origine
HAVING SHU_Minimum != 0
ORDER BY SHU_Maximum DESC;

# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 05
SELECT DATE(date_heure) AS date_heure, COUNT(alerte_medicale) AS nombre_alertes
FROM Consommation
GROUP BY date_heure
ORDER BY nombre_alertes DESC;

# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 06
SELECT id_piment, COUNT(quantite_piment) AS quantite_piment,
IF(quantite_piment >= 200, 'Populaire', 'Pas mangeable' ) AS Popularité
FROM Consommation
WHERE a_bu_du_lait != 0
GROUP BY id_piment
ORDER BY quantite_piment DESC;

# - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- Requête 07
SELECT  DISTINCT(nom), TIMESTAMPDIFF(year, date_naissance, NOW()) AS age
FROM Participants
GROUP BY date_naissance
HAVING age < 50
AND date_naissance IS NOT NULL
ORDER BY age ASC;

# - - - - - - - - - - - - - - - - - - - - - - - - - - -