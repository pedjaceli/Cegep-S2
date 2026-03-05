DROP TABLE IF EXISTS Couleurs;
CREATE TABLE Couleurs (
    ID_Couleur INT PRIMARY KEY,
    Nom_Couleur VARCHAR(50)
);

DROP TABLE IF EXISTS Vetements;
CREATE TABLE Vetements (
    ID_Vetement INT PRIMARY KEY,
    Type_Vetement VARCHAR(50)
);

DROP TABLE IF EXISTS Tailles;
CREATE TABLE Tailles (
    ID_Taille INT PRIMARY KEY,
    Code_Taille VARCHAR(5)
);

INSERT INTO Couleurs (ID_Couleur, Nom_Couleur)
VALUES 
    (1, 'Rouge'),
    (2, 'Bleu'),
    (3, 'Vert'),
    (4, 'Noir'),
    (5, 'Blanc');

INSERT INTO Vetements (ID_Vetement, Type_Vetement)
VALUES 
    (1, 'T-shirt'),
    (2, 'Pantalon'),
    (3, 'Veste'),
    (4, 'Chemise');

INSERT INTO Tailles (ID_Taille, Code_Taille)
VALUES 
    (1, 'S'),
    (2, 'M'),
    (3, 'L');