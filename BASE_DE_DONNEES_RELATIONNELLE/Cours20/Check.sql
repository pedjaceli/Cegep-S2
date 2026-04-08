-- Création de la table pour tester
CREATE TABLE Membres_Club (
    id_membre INT PRIMARY KEY,
    nom VARCHAR(100) NOT NULL,
    age INT,
    cotisation DECIMAL(10, 2),
    niveau VARCHAR(20)
);

-- Ajout des "Check"
-- 1. Au moins 18 ans
ALTER TABLE Membres_Club 
ADD CONSTRAINT chk_age_majeur CHECK (age >= 18);

-- 2. Protection montant négatif
ALTER TABLE Membres_Club 
ADD CONSTRAINT chk_cotisation_positive CHECK (cotisation >= 0);

-- 3. Restreindre les endroits via une liste précise
ALTER TABLE Membres_Club 
ADD CONSTRAINT chk_niveau_valide CHECK (niveau IN ('Debutant', 'Intermediaire', 'Expert'));


-- Vérifier les CHECKS
SHOW CREATE TABLE Membres_Club;
-- OU
SELECT CONSTRAINT_NAME, CHECK_CLAUSE 
FROM information_schema.check_constraints 
WHERE CONSTRAINT_SCHEMA = 'nom_de_ta_base_de_donnees';

-- Retirer celle qui ne fait pas vraiment de sens
DROP CONSTRAINT chk_niveau_valide;