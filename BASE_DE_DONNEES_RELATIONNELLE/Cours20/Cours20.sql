-- -------------------------------------------------------------------------------------------------------------------------
-- COURS20
-- -------------------------------------------------------------------------------------------------------------------------
/*
CONTEXTE :
On va construire la base de données pour un site Web de type Blog

La liste des tables :
- Roles
- Utilisateurs
- Articles
*/
-- -------------------------------------------------------------------------------------------------------------------------
-- Partie 0 : Avoir une B.D. pour le cours20, nommez-la cours20_labo
-- -------------------------------------------------------------------------------------------------------------------------
-- Partie 1 : Configurez la BD
-- Pour bien faire, changez le CHARACTER SET et le COLLATE de votre BD au complet par défaut:
-- CHARACTER SET utf8mb4
-- COLLATE utf8mb4_unicode_ci
-- -------------------------------------------------------------------------------------------------------------------------
-- Partie 2 : Table Roles
CREATE TABLE Roles (
    id_role
    nom_role
    niveau_privilege

    -- Ajoutez ici les 2 contraintes suivantes:
    -- 1. Le nom des rôles (nom_role) doivent être uniques
    -- 2. Le niveau des privilèges doivent être entre 1 et 10
);
-- N'oubliez pas de créer la clé primaire!
-- -------------------------------------------------------------------------------------------------------------------------
-- Partie 2 : Table Utilisateurs

-- Détails:
-- 1. Le champ email doit être unique et avoir spécifiquement un CHARACTER SET "ascii" et un COLLATE "general_ci"
-- 2. Mot_de_passe ne peut pas être NULL.
-- 3. Reliez le champ role_id à la clé primaire de de la table "Roles".
-- 4. Ajoutez une vérification sur la mot de passe, ce dernier doit être d'au moins 8 caractères en longueur.
    -- Pour avoir la longueur, vous pouvez utiliser la commande LENGTH()
-- -------------------------------------------------------------------------------------------------------------------------
-- Partie 3 : Table Articles
CREATE TABLE Articles (
    id_article
    titre
    contenu
    statut
    auteur_id
    date_creation
);
-- Détails:
-- 1. Contenu est un type qui peut être très long. Trouvez un type de donnée approprié pour y mettre du texte.
-- 2. Statut par défaut devrait être à "Brouillon"
-- 3. auteur_id devrait être relié au id de l'utilisateur.
-- 4. La date devrait être automatique lors de l'ajout d'un article.
-- 5. Le champ "Statut" devrait avoir une contrainte qui accepte seulement les valeurs suivantes:
    -- "Brouillon", "Publie" et "Archive"
-- -------------------------------------------------------------------------------------------------------------------------