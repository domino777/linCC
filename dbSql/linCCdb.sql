-- MySQL dump 10.14  Distrib 5.5.35-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: linCC
-- ------------------------------------------------------
-- Server version	5.5.35-MariaDB-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `PLCConnections`
--

DROP TABLE IF EXISTS `PLCConnections`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PLCConnections` (
  `id` tinyint(4) NOT NULL AUTO_INCREMENT,
  `PLCType` tinyint(4) NOT NULL,
  `PLCRack` tinyint(4) NOT NULL,
  `PLCSlot` tinyint(4) NOT NULL,
  `PLCIp` varchar(100) NOT NULL,
  `PLCConPort` smallint(6) NOT NULL,
  `PLCDesc` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `varList`
--

DROP TABLE IF EXISTS `varList`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `varList` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `tagName` varchar(50) DEFAULT NULL,
  `tagType` tinyint(4) NOT NULL,
  `tagPLCNo` tinyint(4) NOT NULL,
  `tagDB` smallint(6) NOT NULL,
  `tagBYTE` mediumint(9) NOT NULL,
  `tagBIT` tinyint(4) NOT NULL,
  `rValue` double DEFAULT NULL,
  `wValue` double DEFAULT NULL,
  `wFlag` tinyint(4) DEFAULT NULL,
  `tagComment` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=76 DEFAULT CHARSET=utf8
/*!50100 PARTITION BY RANGE (id)
(PARTITION idp0 VALUES LESS THAN (200) ENGINE = InnoDB,
 PARTITION idp1 VALUES LESS THAN (400) ENGINE = InnoDB,
 PARTITION idp2 VALUES LESS THAN (600) ENGINE = InnoDB,
 PARTITION idp3 VALUES LESS THAN (800) ENGINE = InnoDB,
 PARTITION idp4 VALUES LESS THAN (1000) ENGINE = InnoDB,
 PARTITION idp5 VALUES LESS THAN MAXVALUE ENGINE = InnoDB) */;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-03-01 11:55:02
