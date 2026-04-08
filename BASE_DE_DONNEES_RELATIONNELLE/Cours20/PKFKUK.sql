roleCREATE TABLE Departements (
    id_dept INT PRIMARY KEY AUTO_INCREMENT,
    nom_dept VARCHAR(50)
);

CREATE TABLE Employes_Test (
    id_emp INT NOT NULL AUTO_INCREMENT,
    email VARCHAR(100),
    departement_id INT,
    
    CONSTRAINT PRIMARY KEY (id_emp),
    CONSTRAINT unq_email UNIQUE (email),
    CONSTRAINT fk_employe_dept FOREIGN KEY (departement_id) REFERENCES Departements(id_dept)
);

-- PRIMARY KEY
ALTER TABLE Employes_Test 
DROP PRIMARY KEY;

ALTER TABLE Employes_Test 
MODIFY COLUMN id_emp INT NOT NULL;

ALTER TABLE Employes_Test 
DROP PRIMARY KEY;

-- FOREIGN KEY
ALTER TABLE Employes_Test 
DROP FOREIGN KEY fk_employe_dept;

ALTER TABLE Employes_Test 
DROP INDEX fk_employe_dept;

-- UNIQUE KEY
ALTER TABLE Employes_Test 
DROP INDEX unq_email;