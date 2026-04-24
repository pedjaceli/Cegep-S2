-- phpMyAdmin SQL Dump
-- version 5.2.2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : ven. 24 avr. 2026 à 18:41
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

-- --------------------------------------------------------

--
-- Structure de la table `Classes`
--

DROP TABLE IF EXISTS `Classes`;
CREATE TABLE IF NOT EXISTS `Classes` (
  `id_classe` int(11) NOT NULL AUTO_INCREMENT,
  `nom_classe` varchar(100) NOT NULL,
  `description` varchar(255) NOT NULL,
  PRIMARY KEY (`id_classe`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Structure de la table `Classes_Competences`
--

DROP TABLE IF EXISTS `Classes_Competences`;
CREATE TABLE IF NOT EXISTS `Classes_Competences` (
  `id_classe` int(11) NOT NULL,
  `id_competence` int(11) NOT NULL,
  PRIMARY KEY (`id_classe`,`id_competence`),
  KEY `fk_classescompetences_competences` (`id_competence`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Structure de la table `Competences`
--

DROP TABLE IF EXISTS `Competences`;
CREATE TABLE IF NOT EXISTS `Competences` (
  `id_competence` int(11) NOT NULL AUTO_INCREMENT,
  `nom_competence` varchar(100) NOT NULL,
  `cout_mana` int(11) NOT NULL,
  `degat_base` int(11) NOT NULL,
  `description_competence` varchar(255) NOT NULL,
  PRIMARY KEY (`id_competence`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Structure de la table `Configurations`
--

DROP TABLE IF EXISTS `Configurations`;
CREATE TABLE IF NOT EXISTS `Configurations` (
  `id_configuration` int(11) NOT NULL AUTO_INCREMENT,
  `matricule` varchar(20) NOT NULL,
  PRIMARY KEY (`id_configuration`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Structure de la table `Heros`
--

DROP TABLE IF EXISTS `Heros`;
CREATE TABLE IF NOT EXISTS `Heros` (
  `id_heros` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(100) NOT NULL,
  `niveau` tinyint(4) NOT NULL,
  `id_classe` int(11) NOT NULL,
  PRIMARY KEY (`id_heros`),
  KEY `fk_heros_classes` (`id_classe`)
) ;

-- --------------------------------------------------------

--
-- Structure de la table `ListeNoireTaverne`
--

DROP TABLE IF EXISTS `ListeNoireTaverne`;
CREATE TABLE IF NOT EXISTS `ListeNoireTaverne` (
  `id_liste` int(11) NOT NULL AUTO_INCREMENT,
  `duree_enJours` int(11) NOT NULL,
  `raison` varchar(255) NOT NULL,
  `date` datetime NOT NULL DEFAULT current_timestamp(),
  `id_heros` int(11) NOT NULL,
  PRIMARY KEY (`id_liste`),
  KEY `fk_listenoiretaverne_heros` (`id_heros`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Structure de la table `Loots`
--

DROP TABLE IF EXISTS `Loots`;
CREATE TABLE IF NOT EXISTS `Loots` (
  `id_loot` int(11) NOT NULL AUTO_INCREMENT,
  `nom_objet` varchar(150) NOT NULL,
  `rarete` enum('commun','rare','unique') NOT NULL,
  `valeur_or` int(11) NOT NULL,
  PRIMARY KEY (`id_loot`),
  UNIQUE KEY `unq_nom_objet` (`nom_objet`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Structure de la table `Monstres`
--

DROP TABLE IF EXISTS `Monstres`;
CREATE TABLE IF NOT EXISTS `Monstres` (
  `id_monstre` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(150) NOT NULL,
  `point_vie` int(11) NOT NULL,
  `niveau` tinyint(4) NOT NULL,
  PRIMARY KEY (`id_monstre`)
) ;

-- --------------------------------------------------------

--
-- Structure de la table `Monstres_Loots`
--

DROP TABLE IF EXISTS `Monstres_Loots`;
CREATE TABLE IF NOT EXISTS `Monstres_Loots` (
  `id_monstre` int(11) NOT NULL,
  `id_loot` int(11) NOT NULL,
  PRIMARY KEY (`id_monstre`,`id_loot`),
  KEY `fk_monstresloots_loots` (`id_loot`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Structure de la table `Quetes`
--

DROP TABLE IF EXISTS `Quetes`;
CREATE TABLE IF NOT EXISTS `Quetes` (
  `id_quete` int(11) NOT NULL AUTO_INCREMENT,
  `titre` varchar(150) NOT NULL,
  `recompense_or` int(11) NOT NULL,
  `niveau_requis` tinyint(4) NOT NULL,
  PRIMARY KEY (`id_quete`),
  UNIQUE KEY `unq_titre` (`titre`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Structure de la table `Quetes_Monstres`
--

DROP TABLE IF EXISTS `Quetes_Monstres`;
CREATE TABLE IF NOT EXISTS `Quetes_Monstres` (
  `id_quete` int(11) NOT NULL,
  `id_monstre` int(11) NOT NULL,
  PRIMARY KEY (`id_quete`,`id_monstre`),
  KEY `fk_quetesmonstres_monstres` (`id_monstre`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `Classes_Competences`
--
ALTER TABLE `Classes_Competences`
  ADD CONSTRAINT `fk_classescompetences_classes` FOREIGN KEY (`id_classe`) REFERENCES `Classes` (`id_classe`),
  ADD CONSTRAINT `fk_classescompetences_competences` FOREIGN KEY (`id_competence`) REFERENCES `Competences` (`id_competence`);

--
-- Contraintes pour la table `Heros`
--
ALTER TABLE `Heros`
  ADD CONSTRAINT `fk_heros_classes` FOREIGN KEY (`id_classe`) REFERENCES `Classes` (`id_classe`);

--
-- Contraintes pour la table `ListeNoireTaverne`
--
ALTER TABLE `ListeNoireTaverne`
  ADD CONSTRAINT `fk_listenoiretaverne_heros` FOREIGN KEY (`id_heros`) REFERENCES `Heros` (`id_heros`);

--
-- Contraintes pour la table `Monstres_Loots`
--
ALTER TABLE `Monstres_Loots`
  ADD CONSTRAINT `fk_monstresloots_loots` FOREIGN KEY (`id_loot`) REFERENCES `Loots` (`id_loot`),
  ADD CONSTRAINT `fk_monstresloots_monstres` FOREIGN KEY (`id_monstre`) REFERENCES `Monstres` (`id_monstre`);

--
-- Contraintes pour la table `Quetes_Monstres`
--
ALTER TABLE `Quetes_Monstres`
  ADD CONSTRAINT `fk_quetesmonstres_monstres` FOREIGN KEY (`id_monstre`) REFERENCES `Monstres` (`id_monstre`),
  ADD CONSTRAINT `fk_quetesmonstres_quetes` FOREIGN KEY (`id_quete`) REFERENCES `Quetes` (`id_quete`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
