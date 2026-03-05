DROP TABLE IF EXISTS Etudiants;
CREATE TABLE Etudiants (
    ID_Etudiant INT PRIMARY KEY,
    Prenom VARCHAR(50)
);

DROP TABLE IF EXISTS Sujets;
CREATE TABLE Sujets (
    ID_Sujet INT PRIMARY KEY,
    Nom_Sujet VARCHAR(150)
);

DROP TABLE IF EXISTS Affectations;
CREATE TABLE Affectations (
    ID_Affectation INT PRIMARY KEY,
    ID_Etudiant INT,
    ID_Sujet INT
);

INSERT INTO Etudiants (ID_Etudiant, Prenom) VALUES
(1, 'Alex'), (2, 'Béa'), (3, 'Charles'), (4, 'Diane'), (5, 'Éric'), (6, 'Fanny'), (7, 'Gabriel'), (8, 'Hélène'), (9, 'Igor'), (10, 'Julie'),
(11, 'Kevin'), (12, 'Laura'), (13, 'Marc'), (14, 'Nina'), (15, 'Oscar'), (16, 'Pauline'), (17, 'Quentin'), (18, 'Rose'), (19, 'Simon'), (20, 'Thomas'),
(21, 'Ulysse'), (22, 'Victor'), (23, 'William'), (24, 'Xavier'), (25, 'Yann'), (26, 'Zoé'), (27, 'Antoine'), (28, 'Brigitte'), (29, 'Cédric'), (30, 'Delphine'),
(31, 'Étienne'), (32, 'Florence'), (33, 'Gilles'), (34, 'Hugo'), (35, 'Inès'), (36, 'Jean'), (37, 'Karine'), (38, 'Luc'), (39, 'Marie'), (40, 'Nicolas'),
(41, 'Olivier'), (42, 'Pascal'), (43, 'Rémi'), (44, 'Sophie'), (45, 'Thierry'), (46, 'Ursule'), (47, 'Valérie'), (48, 'Yves'), (49, 'Alice'), (50, 'Benoît'),
(51, 'Camille'), (52, 'Denis'), (53, 'Élise'), (54, 'Fabien'), (55, 'Géraldine'), (56, 'Hervé'), (57, 'Isabelle'), (58, 'Jérôme'), (59, 'Léa'), (60, 'Mathieu'),
(61, 'Nadia'), (62, 'Ophélie'), (63, 'Pierre'), (64, 'Romain'), (65, 'Sylvie'), (66, 'Tanguy'), (67, 'Vincent'), (68, 'Agathe'), (69, 'Bastien'), (70, 'Chloé'),
(71, 'Damien'), (72, 'Élodie'), (73, 'François'), (74, 'Guillaume'), (75, 'Hakim'), (76, 'Iris'), (77, 'Julien'), (78, 'Katia'), (79, 'Laurent'), (80, 'Manon'),
(81, 'Noémie'), (82, 'Odile'), (83, 'Philippe'), (84, 'Raphaël'), (85, 'Sarah'), (86, 'Théo'), (87, 'Valentin'), (88, 'Yanis'), (89, 'Amélie'), (90, 'Bruno'),
(91, 'Céline'), (92, 'David'), (93, 'Émilie'), (94, 'Florian'), (95, 'Gaspard'), (96, 'Héloïse'), (97, 'Ibrahim'), (98, 'Justine'), (99, 'Lucas'), (100, 'Mélanie');

INSERT INTO Affectations (ID_Affectation, ID_Etudiant, ID_Sujet) VALUES 
(1, 1, 5), (2, 1, 12), (3, 1, 42),
(4, 2, 1), (5, 2, 5),
(6, 3, 15), (7, 3, 30), (8, 3, 88), (9, 3, 99),
(10, 4, 38), (11, 4, 12),
(12, 5, 3), (13, 5, 18), (14, 5, 22),
(15, 6, 45), (16, 6, 50),
(17, 7, 9), (18, 7, 12), (19, 7, 15),
(20, 8, 2), (21, 8, 4), (22, 8, 6), (23, 8, 8),
(24, 9, 50), (25, 9, 51),
(26, 10, 55), (27, 10, 12), (28, 10, 99),
(29, 11, 60), (30, 11, 61), (31, 11, 62),
(32, 12, 5), (33, 12, 6),
(34, 13, 65), (35, 13, 15),
(36, 14, 70), (37, 14, 71), (38, 14, 72),
(39, 15, 75), (40, 15, 80), (41, 15, 85),
(42, 16, 80), (43, 16, 12),
(44, 17, 85), (45, 17, 86),
(46, 18, 90), (47, 18, 15), (48, 18, 5),
(49, 19, 11), (50, 19, 22), (51, 19, 33), (52, 19, 44),
(53, 20, 95), (54, 20, 96),
(55, 21, 100), (56, 21, 1),
(57, 22, 2), (58, 22, 12), (59, 22, 50),
(60, 23, 4), (61, 23, 5),
(62, 24, 6), (63, 24, 15),
(64, 25, 8), (65, 25, 18), (66, 25, 28),
(67, 26, 10), (68, 26, 20),
(69, 27, 12), (70, 27, 32), (71, 27, 42),
(72, 28, 14), (73, 28, 24),
(74, 29, 16), (75, 29, 26), (76, 29, 36),
(77, 30, 18), (78, 30, 12), (79, 30, 5),
(80, 42, 10), (81, 42, 8), (82, 42, 99),
(83, 88, 12), (84, 88, 45), (85, 88, 50),
(86, 99, 4), (87, 99, 14), (88, 99, 24), (89, 99, 34);

INSERT INTO Sujets (ID_Sujet, Nom_Sujet) VALUES 
(1, 'Algorithmique de base'), (2, 'Structures de données'), (3, 'Architecture des réseaux'), (4, 'Introduction à la cybersécurité'), (5, 'Développement Web Front-end'),
(6, 'Développement Web Back-end'), (7, 'Conception de bases de données relationnelles'), (8, 'Introduction à l''Intelligence Artificielle'), (9, 'Fondements du Machine Learning'), (10, 'Administration de serveurs Linux'),
(11, 'Programmation Orientée Objet en Java'), (12, 'Analyse de données avec Python'), (13, 'Développement d''applications mobiles (Android)'), (14, 'Développement d''applications mobiles (iOS)'), (15, 'Gestion de projet Agile (Scrum)'),
(16, 'Principes du Cloud Computing'), (17, 'Introduction à DevOps et CI/CD'), (18, 'Programmation système en C'), (19, 'Développement de jeux vidéo'), (20, 'Création d''interfaces utilisateur (UI/UX)'),
(21, 'Mathématiques discrètes'), (22, 'Algèbre linéaire'), (23, 'Calcul différentiel et intégral'), (24, 'Probabilités et statistiques'), (25, 'Physique classique : Mécanique'),
(26, 'Physique quantique (Introduction)'), (27, 'Chimie organique'), (28, 'Biologie cellulaire'), (29, 'Génétique fondamentale'), (30, 'Anatomie et physiologie humaine'),
(31, 'Histoire de l''art de la Renaissance'), (32, 'Littérature française du 19ème siècle'), (33, 'Philosophie des sciences'), (34, 'Introduction à la sociologie'), (35, 'Psychologie cognitive'),
(36, 'Microéconomie'), (37, 'Macroéconomie'), (38, 'Principes de comptabilité'), (39, 'Stratégies de marketing digital'), (40, 'Droit des contrats internationaux'),
(41, 'Sciences politiques et relations internationales'), (42, 'Histoire contemporaine'), (43, 'Géographie urbaine'), (44, 'Techniques de photographie numérique'), (45, 'Théorie musicale et composition'),
(46, 'Histoire du cinéma mondial'), (47, 'Design graphique et typographie'), (48, 'Animation 3D et modélisation'), (49, 'Introduction à la robotique'), (50, 'Internet des Objets (IoT)'),
(51, 'Technologies Blockchain et cryptomonnaies'), (52, 'Réalité virtuelle et augmentée'), (53, 'Bio-informatique'), (54, 'Traitement du langage naturel (NLP)'), (55, 'Vision par ordinateur'),
(56, 'Gestion des Big Data'), (57, 'Éthique de l''Intelligence Artificielle'), (58, 'Programmation fonctionnelle'), (59, 'Sécurité des applications web'), (60, 'Cryptographie moderne'),
(61, 'Astronomie et astrophysique'), (62, 'Géologie et sciences de la Terre'), (63, 'Météorologie et climatologie'), (64, 'Écologie et développement durable'), (65, 'Botanique et biologie végétale'),
(66, 'Zoologie et comportement animal'), (67, 'Microbiologie et virologie'), (68, 'Pharmacologie générale'), (69, 'Nutrition et diététique'), (70, 'Médecine préventive et santé publique'),
(71, 'Apprentissage des langues étrangères (Linguistique)'), (72, 'Techniques de traduction et d''interprétation'), (73, 'Journalisme d''investigation'), (74, 'Communication d''entreprise'), (75, 'Gestion des ressources humaines'),
(76, 'Logistique et Supply Chain Management'), (77, 'Entrepreneuriat et création de start-up'), (78, 'Gestion de l''innovation'), (79, 'Accessibilité numérique (a11y)'), (80, 'Optimisation pour les moteurs de recherche (SEO)'),
(81, 'Commerce électronique et stratégies de vente'), (82, 'Automatisation et robotique industrielle'), (83, 'Aéronautique et ingénierie spatiale'), (84, 'Génie civil et construction'), (85, 'Génie électrique et électronique'),
(86, 'Thermodynamique appliquée'), (87, 'Sciences des matériaux'), (88, 'Énergies renouvelables et transition énergétique'), (89, 'Traitement du signal'), (90, 'Systèmes embarqués'),
(91, 'Analyse financière et marchés boursiers'), (92, 'Droit du travail et relations sociales'), (93, 'Psychologie du travail et des organisations'), (94, 'Histoire des civilisations anciennes'), (95, 'Philosophie morale et éthique'),
(96, 'Arts plastiques et techniques de peinture'), (97, 'Cinématographie et réalisation'), (98, 'Acoustique et ingénierie du son'), (99, 'Design industriel et ergonomie'), (100, 'Projet de recherche multidisciplinaire');