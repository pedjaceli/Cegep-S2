-- phpMyAdmin SQL Dump
-- version 5.2.2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : ven. 24 avr. 2026 à 18:44
-- Version du serveur : 10.6.25-MariaDB
-- Version de PHP : 8.4.20

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `e2539709_TP2SQL`
--

--
-- Déchargement des données de la table `Classes`
--

INSERT INTO `Classes` (`id_classe`, `nom_classe`, `description`) VALUES
(1, 'Guerrier', 'Spécialiste du combat au corps à corps, très résistant.'),
(2, 'Mage', 'Maître de la magie arcanique, utilise des sorts puissants.'),
(3, 'Archer', 'Expert du tir à l\'arc, très précis à longue distance.'),
(4, 'Voleur', 'Qui se spécialise dans le vol d\'objet. Est très agile et ne fait pas de bruit.'),
(5, 'Barde', 'Musicien itinérant aux pouvoirs magiques, inspire ses alliés.');

--
-- Déchargement des données de la table `Classes_Competences`
--

INSERT INTO `Classes_Competences` (`id_classe`, `id_competence`) VALUES
(1, 3),
(1, 5),
(2, 1),
(2, 2),
(3, 4),
(4, 5),
(5, 2);

--
-- Déchargement des données de la table `Competences`
--

INSERT INTO `Competences` (`id_competence`, `nom_competence`, `cout_mana`, `degat_base`, `description_competence`) VALUES
(1, 'Boule de feu', 4, 10, 'Il suffit de crier boule de feu et une boule de flamme sort de vos mains.'),
(2, 'Téléportation', 10, 0, 'Permet de se téléporter à environ 30 mètres plus loin.'),
(3, 'Coup puissant', 2, 25, 'Un coup d\'épée dévastateur qui fait reculer l\'ennemi.'),
(4, 'Tir de précision', 3, 15, 'Un tir ciblé sur un point faible de l\'ennemi.'),
(5, 'Pickpocket', 1, 0, 'Vole discrètement un objet dans l\'inventaire de la cible.');

--
-- Déchargement des données de la table `Configurations`
--

INSERT INTO `Configurations` (`id_configuration`, `matricule`) VALUES
(1, '0123456'),
(2, '1234567'),
(3, '6742069'),
(4, '9876543'),
(5, '1111111');

--
-- Déchargement des données de la table `Heros`
--

INSERT INTO `Heros` (`id_heros`, `nom`, `niveau`, `id_classe`) VALUES
(1, 'Aragorn', 15, 1),
(2, 'Gandalf', 99, 2),
(3, 'Legolas', 45, 3),
(4, 'Bilbon', 12, 4),
(5, 'Gimli', 30, 1);

--
-- Déchargement des données de la table `ListeNoireTaverne`
--

INSERT INTO `ListeNoireTaverne` (`id_liste`, `duree_enJours`, `raison`, `date`, `id_heros`) VALUES
(1, 67, 'A échoué de voler 13 fois le pauvre mixologue.', '2026-04-24 18:23:06', 4),
(2, 666, 'A cassé tous les petits pots en céramique dans l\'espoir de trouver des rubis verts.', '2026-04-24 18:23:06', 2),
(3, 30, 'A provoqué une bagarre avec 3 gardes en même temps.', '2026-04-24 18:23:06', 1),
(4, 14, 'A tiré des flèches sur les lustres en cristal de la taverne.', '2026-04-24 18:23:06', 3),
(5, 7, 'A renversé intentionnellement tous les tonneaux de bière.', '2026-04-24 18:23:06', 5);

--
-- Déchargement des données de la table `Loots`
--

INSERT INTO `Loots` (`id_loot`, `nom_objet`, `rarete`, `valeur_or`) VALUES
(1, 'Épée maître', 'unique', 69420),
(2, 'Pioche en diamant', 'rare', 9001),
(3, 'Pokéball', 'commun', 200),
(4, 'Potion de soin', 'commun', 50),
(5, 'Arc elfique', 'rare', 1500);

--
-- Déchargement des données de la table `Monstres`
--

INSERT INTO `Monstres` (`id_monstre`, `nom`, `point_vie`, `niveau`) VALUES
(1, 'Dragon blanc aux yeux bleus', 2500, 80),
(2, 'Baie de Tom', 67, 13),
(3, 'Le Monarque des Tortues de Plomberie', 888, 50),
(4, 'Gobelin', 45, 3),
(5, 'Troll des cavernes', 350, 25);

--
-- Déchargement des données de la table `Monstres_Loots`
--

INSERT INTO `Monstres_Loots` (`id_monstre`, `id_loot`) VALUES
(1, 1),
(1, 2),
(2, 4),
(3, 3),
(4, 4),
(5, 5);

--
-- Déchargement des données de la table `Quetes`
--

INSERT INTO `Quetes` (`id_quete`, `titre`, `recompense_or`, `niveau_requis`) VALUES
(1, 'Mais où est Charlie?', 22, 2),
(2, 'Colis perdu de Pirolateur', 110, 5),
(3, 'La grotte du dragon', 500, 30),
(4, 'Sauver la princesse', 300, 20),
(5, 'Cueillette d\'herbes magiques', 50, 8);

--
-- Déchargement des données de la table `Quetes_Monstres`
--

INSERT INTO `Quetes_Monstres` (`id_quete`, `id_monstre`) VALUES
(1, 2),
(2, 4),
(3, 1),
(3, 3),
(4, 5),
(5, 2);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
