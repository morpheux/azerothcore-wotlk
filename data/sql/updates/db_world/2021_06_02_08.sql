-- DB update 2021_06_02_07 -> 2021_06_02_08
DROP PROCEDURE IF EXISTS `updateDb`;
DELIMITER //
CREATE PROCEDURE updateDb ()
proc:BEGIN DECLARE OK VARCHAR(100) DEFAULT 'FALSE';
SELECT COUNT(*) INTO @COLEXISTS
FROM information_schema.COLUMNS
WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'version_db_world' AND COLUMN_NAME = '2021_06_02_07';
IF @COLEXISTS = 0 THEN LEAVE proc; END IF;
START TRANSACTION;
ALTER TABLE version_db_world CHANGE COLUMN 2021_06_02_07 2021_06_02_08 bit;
SELECT sql_rev INTO OK FROM version_db_world WHERE sql_rev = '1622103568572292814'; IF OK <> 'FALSE' THEN LEAVE proc; END IF;
--
-- START UPDATING QUERIES
--

INSERT INTO `version_db_world` (`sql_rev`) VALUES ('1622103568572292814');

-- 118: Prowler
-- 3660: Athrikus Narassin
-- 8386: Horizon Scout Crewman
-- 10495: Diseased Ghoul
-- 11562: Drysnap Crawler
-- 11563: Drysnap Pincer
DELETE FROM `creature_loot_template` WHERE `reference` = 24060 AND `entry` IN (118, 3660, 8386, 10495, 11562, 11563);

--
-- END UPDATING QUERIES
--
UPDATE version_db_world SET date = '2021_06_02_08' WHERE sql_rev = '1622103568572292814';
COMMIT;
END //
DELIMITER ;
CALL updateDb();
DROP PROCEDURE IF EXISTS `updateDb`;
