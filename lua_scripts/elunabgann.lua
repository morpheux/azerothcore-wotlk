-------------------------------------------------------
-- Created By Rastrian.dev                           //
-- https://rastrian.dev                              //
-- Name: Eluna Script BG End Announcer               //
-- Content: Top Kill, Top Heal and Top Damage scores //
-------------------------------------------------------

local BGS = {}

local FactionIcon = {
    [1] =  "|TInterface\\icons\\Inv_Misc_Tournaments_banner_Human.png:17|t", -- Alliance 
    [0] =  "|TInterface\\icons\\Inv_Misc_Tournaments_banner_Orc.png:17|t", -- Horde
};

local Faction = {
    [1] =  "|cff00ccffAlliance", -- Alliance 
    [0] =  "|cffff6060Horde", -- Horde
};

function getBattleID(bgId, getWinnerTeam)
    local BattleID_final = 0;
    local BattleID = CharDBQuery("SELECT id FROM `pvpstats_battlegrounds` WHERE `type` = '"..bgId.."' AND `winner_faction` = '"..getWinnerTeam.."' ORDER BY `date` DESC LIMIT 1;")
    if (BattleID) then
        BattleID_final = BattleID:GetUInt32(0)
    return BattleID_final
    end
end

function getPlayer_Top_Damage(BattleID)
    local player_top_damage_final = "";
    local player_top_damage = CharDBQuery("SELECT `name` FROM characters WHERE guid = (SELECT `character_guid` FROM `pvpstats_players` WHERE `battleground_id` = '"..BattleID.."' ORDER BY `score_damage_done` DESC LIMIT 1);")
    if (player_top_damage) then
        player_top_damage_final = player_top_damage:GetString(0)
    return player_top_damage_final
    end
end 

function getPlayer_Top_Damage_Value(BattleID)
    local player_top_Damage_Value_final = 0;
    local player_top_Damage_Value = CharDBQuery("SELECT `score_damage_done` FROM `pvpstats_players` WHERE `battleground_id` = '"..BattleID.."' ORDER BY `score_damage_done` DESC LIMIT 1")
    if (player_top_Damage_Value) then
        player_top_Damage_Value_final = player_top_Damage_Value:GetUInt32(0)
    return player_top_Damage_Value_final
    end
end 

function getPlayer_Top_Heal(BattleID)
    local player_top_Heal_final = "";
    local player_top_Heal = CharDBQuery("SELECT `name` FROM characters WHERE guid = (SELECT `character_guid` FROM `pvpstats_players` WHERE `battleground_id` = '"..BattleID.."' ORDER BY `score_healing_done` DESC LIMIT 1);")
    if (player_top_Heal) then
        player_top_Heal_final = player_top_Heal:GetString(0)
    return player_top_Heal_final
    end
end 

function getPlayer_Top_Heal_Value(BattleID)
    local player_top_Heal_Value_final = 0;
    local player_top_Heal_Value = CharDBQuery("SELECT `score_healing_done` FROM `pvpstats_players` WHERE `battleground_id` = '"..BattleID.."' ORDER BY `score_healing_done` DESC LIMIT 1")
    if (player_top_Heal_Value) then
        player_top_Heal_Value_final = player_top_Heal_Value:GetUInt32(0)
    return player_top_Heal_Value_final
    end
end 

function getPlayer_Top_Kills(BattleID)
    local player_top_Kills_final = "";
    local player_top_Kills = CharDBQuery("SELECT `name` FROM characters WHERE guid = (SELECT `character_guid` FROM `pvpstats_players` WHERE `battleground_id` = '"..BattleID.."' ORDER BY `score_honorable_kills` DESC LIMIT 1);")
    if (player_top_Kills) then
        player_top_Kills_final = player_top_Kills:GetString(0)
    return player_top_Kills_final
    end
end 

function getPlayer_Top_Kills_Value(BattleID)
    local player_top_Kills_Value_final = 0;
    local player_top_Kills_Value = CharDBQuery("SELECT `score_honorable_kills` FROM `pvpstats_players` WHERE `battleground_id` = '"..BattleID.."' ORDER BY `score_honorable_kills` DESC LIMIT 1")
    if (player_top_Kills_Value) then
        player_top_Kills_Value_final = player_top_Kills_Value:GetUInt32(0)
    return player_top_Kills_Value_final
    end
end 

function AnnBGEnd(bgId, bgName, teamName, getWinnerTeam, BattleID, instanceId)
    local player_top_kills = ""
    local amount_top_kills = 0
    local player_top_heal = ""
    local amount_top_heal = 0
    local player_top_damage = ""
    local amount_top_damage = 0    

    if BattleID == nil then
        BattleID = getBattleID(bgId, getWinnerTeam)
    end

    player_top_kills = getPlayer_Top_Kills(BattleID) or "Ninguem"
    amount_top_kills = getPlayer_Top_Kills_Value(BattleID) or 0
    
    player_top_damage = getPlayer_Top_Damage(BattleID) or "Ninguem"
    amount_top_damage = getPlayer_Top_Damage_Value(BattleID) or 0
    
    player_top_heal = getPlayer_Top_Heal(BattleID) or "Ninguem"
    amount_top_heal = getPlayer_Top_Heal_Value(BattleID) or 0

    if BGS[BattleID] ~= true then
        BGS[BattleID] = true

        for k,player in pairs(GetPlayersInWorld()) do
            player:SendBroadcastMessage("|cffFF4500"..FactionIcon[1].." "..bgName.." "..FactionIcon[0].." - Winner: "..teamName..".\n|cffff0000TOP Killer: "..player_top_kills.." ("..amount_top_kills.." kills).|r\nTOP Damage: "..player_top_damage.." ("..amount_top_damage..").|r\n|cff00FF7FTOP Heal: "..player_top_heal.." ("..amount_top_heal..").")
        end
    end
end

function OnBGEnd(event, bg, bgId, instanceId, winner)
    local bgName = bg:GetName()
    local getWinnerTeam = bg:GetWinner() or winner
    local teamName = Faction[getWinnerTeam] or Faction[bg:GetWinner()]
    local BattleID = 0
    local BattleID_result = CharDBQuery("SELECT id FROM `pvpstats_battlegrounds` WHERE `type` = '"..bgId.."' AND `winner_faction` = '"..getWinnerTeam.."' ORDER BY `date` DESC LIMIT 1;")
    if (BattleID_result) then
        BattleID = BattleID_result:GetUInt32(0) or getBattleID(bgId, getWinnerTeam)

        if (BattleID) then
            AnnBGEnd(bgId, bgName, teamName, getWinnerTeam, BattleID, instanceId)
        end
    end
end

function OnBGEndDestroy(event, bg, bgId, instanceId)
    local bgName = bg:GetName()
    local getWinnerTeam = bg:GetWinner() or winner
    local teamName = Faction[getWinnerTeam] or Faction[bg:GetWinner()]
    local BattleID = 0
    local BattleID_result = CharDBQuery("SELECT id FROM `pvpstats_battlegrounds` WHERE `type` = '"..bgId.."' AND `winner_faction` = '"..getWinnerTeam.."' ORDER BY `date` DESC LIMIT 1;")
    if (BattleID_result) then
        BattleID = BattleID_result:GetUInt32(0) or getBattleID(bgId, getWinnerTeam)

        if (BattleID) then
            AnnBGEnd(bgId, bgName, teamName, getWinnerTeam, BattleID, instanceId)
        end
    end
end

RegisterBGEvent(2, OnBGEnd)
RegisterBGEvent(4, OnBGEndDestroy)

-------------------------------------------------------
-- Created By Rastrian.dev                           //
-- https://rastrian.dev                              //
-- Name: Eluna Script BG End Announcer               //
-- Content: Top Kill, Top Heal and Top Damage scores //
-------------------------------------------------------