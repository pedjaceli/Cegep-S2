SELECT * FROM Medailles_JO_2022 WHERE pays = "France";
SELECT * FROM Medailles_JO_2022 WHERE epreuve LIKE '%Relais%';
SELECT medaille FROM Medailles_JO_2022 WHERE date_evenement >='2022-02-18';
SELECT * FROM Medailles_JO_2022 WHERE medaille = "Or" AND NOT pays = "Norvège";
SELECT * FROM Medailles_JO_2022 WHERE medaille BETWEEN '2022-02-05' AND '2022-02-08';
SELECT * FROM Medailles_JO_2022 WHERE pays IN ('Chine', 'Japon', 'Corée du Sud');
SELECT * FROM Medailles_JO_2022 WHERE athlete = "";
SELECT * FROM Medailles_JO_2022 WHERE pays = "Canada" ORDER BY date_evenement ASC;
SELECT * FROM Medailles_JO_2022 ORDER BY sport ASC, pays ASC, date_evenement DESC;
SELECT * FROM Medailles_JO_2022 WHERE sport IN ('Luge', 'Bobsleigh', 'Skeleton') AND pays IN ("Allemagne", "Autriche") AND  medaille != "Or" AND 
date_evenement >= '2022-02-10' ORDER BY date_evenement ASC, medaille ASC;
SELECT * FROM Medailles_JO_2022 WHERE (epreuve LIKE '%Femmes%' OR epreuve LIKE '%ski%')  And epreuve != "Ski Acrobatique" AND date_evenement BETWEEN '2022-02-05' AND '2022-02-20'
ORDER BY sport ASC, athlete ASC;
select * FROM Medailles_JO_2022 WHERE PAYS IN ('Canada', 'France', 'Belgique') AND (epreuve LIKE 'Relais' OR epreuve LIKE 'Équipe' OR epreuve LIKE '1000m') AND sport != 'Hockey' AND medaille IN ('argent', 'bronze') 
ORDER BY medaille ASC, pays ASC;