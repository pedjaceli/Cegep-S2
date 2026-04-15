/* CONSIGNES
Le but est de créer la table dans laquelle vous pourrez faire le INSERT suivant.

Détails:
- Tentez d'ajouter le champ nommé "date_journal" avec le type de données "datetime".
- Faites en sorte que ce champ fonctionne avec le INSERT!
- N'oubliez pas de faire les clés.
*/
CREATE TABLE journaux(
	id_journaux INT PRIMARY KEY AUTO_INCREMENT,
    id_projet INT,
    titre_entree VARCHAR(50),
    date_journal DATETIME DEFAULT CURRENT_TIMESTAMP,
    description VARCHAR(255),
    heure_travaillees DECIMAL (3, 2),
 
    CONSTRAINT fk_id_projet FOREIGN KEY (id_projet) REFERENCES projets(id_projet)
);


INSERT INTO journaux (id_projet, titre_entree, description, heures_travaillees) 
VALUES 
(1, 'Assemblage de base', 'Soudure des composants principaux sur la plaque d''essai et vérification des continuités.', 2.50),
(3, 'Configuration du module WiFi', 'Programmation de la puce ESP8266 pour qu''elle se connecte automatiquement au réseau du laboratoire.', 1.25),
(5, 'Test de la pompe à eau', 'Vérification du débit de la mini pompe avec le module relais 5V. Fonctionne parfaitement.', 0.75),
(12, 'Calibrage des servomoteurs', 'Ajustement minutieux des angles minimum et maximum dans le code pour éviter de forcer les engrenages du bras robotique.', 3.00),
(1, 'Intégration du capteur BME280', 'Ajout du code de communication I2C pour lire la pression atmosphérique et l''humidité avec succès.', 1.50);

-- Après avoir créé la table et inséré les données, modifiez la page index.php
-- de l'exercice PHP du cours pour afficher avec un SELECT les données de votre table "journaux" :D!