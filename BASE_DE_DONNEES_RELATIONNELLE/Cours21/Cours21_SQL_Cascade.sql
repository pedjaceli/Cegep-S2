CREATE TABLE Utilisateurs (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nom VARCHAR(50) NOT NULL
);
CREATE TABLE Roles_Restrict (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nom_role VARCHAR(50),
    utilisateur_id INT,
    CONSTRAINT fk_roles_restrict
        FOREIGN KEY (utilisateur_id) 
        REFERENCES Utilisateurs(id) 
        ON DELETE RESTRICT
);
CREATE TABLE Articles_Cascade (
    id INT AUTO_INCREMENT PRIMARY KEY,
    titre VARCHAR(100),
    utilisateur_id INT,
    CONSTRAINT fk_articles_cascade
        FOREIGN KEY (utilisateur_id) 
        REFERENCES Utilisateurs(id) 
        ON DELETE CASCADE
);
CREATE TABLE Commentaires_SetNull (
    id INT AUTO_INCREMENT PRIMARY KEY,
    contenu TEXT,
    utilisateur_id INT NULL,
    CONSTRAINT fk_commentaires_setnull
        FOREIGN KEY (utilisateur_id) 
        REFERENCES Utilisateurs(id) 
        ON DELETE SET NULL
);
INSERT INTO Utilisateurs (nom) VALUES 
('Alice (Test Restrict)'), 
('Bob (Test Cascade)'), 
('Charlie (Test Set Null)');

INSERT INTO Roles_Restrict (nom_role, utilisateur_id) VALUES ('Administrateur', 1);

INSERT INTO Articles_Cascade (titre, utilisateur_id) VALUES 
('Premier article de Bob', 2),
('Deuxième article de Bob', 2);

INSERT INTO Commentaires_SetNull (contenu, utilisateur_id) VALUES 
('Super article !', 3),
('Je ne suis pas en accord.', 3);

-- RESTRICT
DELETE FROM Utilisateurs WHERE id = 1;

-- CASCADE
DELETE FROM Utilisateurs WHERE id = 2;

-- SET NULL
DELETE FROM Utilisateurs WHERE id = 3;