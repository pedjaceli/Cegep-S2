CREATE TABLE Clients (
    idClient INT PRIMARY KEY AUTO_INCREMENT,
    nom VARCHAR(25),
    telephone VARCHAR(10)
);

CREATE TABLE Produits (
    idProduits INT PRIMARY KEY AUTO_INCREMENT,
    nom VARCHAR(50),
    garantie TINYINT
);

CREATE TABLE Factures (
    idFacture INT PRIMARY KEY AUTO_INCREMENT,
    idClient INT,
    dateAchat DATE,
    FOREIGN KEY (idClient) REFERENCES Clients(idClient)
);

CREATE TABLE DetailsFactures (
    idFacture INT,
    idProduits INT,
    quantite INT,
    PRIMARY KEY (idFacture, idProduits),
    FOREIGN KEY (idFacture) REFERENCES Factures(idFacture),
    FOREIGN KEY (idProduits) REFERENCES Produits(idProduits)
);