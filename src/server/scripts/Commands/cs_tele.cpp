/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

/* ScriptData
Name: tele_commandscript
%Complete: 100
Comment: All tele related commands
Category: commandscripts
EndScriptData */

#include "Chat.h"
#include "Group.h"
#include "Language.h"
#include "MapManager.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include <time.h>

class tele_commandscript : public CommandScript
{
public:
    tele_commandscript() : CommandScript("tele_commandscript") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> teleCommandTable =
        {
            { "add",            SEC_ADMINISTRATOR,   false, &HandleTeleAddCommand,             "" },
            { "del",            SEC_ADMINISTRATOR,   true,  &HandleTeleDelCommand,             "" },
            { "name",           SEC_GAMEMASTER,      true,  &HandleTeleNameCommand,            "" },
            { "group",          SEC_GAMEMASTER,      false, &HandleTeleGroupCommand,           "" },
            { "",               SEC_MODERATOR,       false, &HandleTeleCommand,                "" }
        };
        static std::vector<ChatCommand> commandTable =
        {
            { "teleport",           SEC_MODERATOR,      false, nullptr,      "", teleCommandTable }
        };
        return commandTable;
    }

    static bool HandleTeleAddCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        Player* player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        std::string name = args;

        if (sObjectMgr->GetGameTele(name))
        {
            handler->SendSysMessage(LANG_COMMAND_TP_ALREADYEXIST);
            handler->SetSentErrorMessage(true);
            return false;
        }

        GameTele tele;
        tele.position_x  = player->GetPositionX();
        tele.position_y  = player->GetPositionY();
        tele.position_z  = player->GetPositionZ();
        tele.orientation = player->GetOrientation();
        tele.mapId       = player->GetMapId();
        tele.name        = name;

        if (sObjectMgr->AddGameTele(tele))
        {
            handler->SendSysMessage(LANG_COMMAND_TP_ADDED);
        }
        else
        {
            handler->SendSysMessage(LANG_COMMAND_TP_ADDEDERR);
            handler->SetSentErrorMessage(true);
            return false;
        }

        return true;
    }

    static bool HandleTeleDelCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        // id, or string, or [name] Shift-click form |color|Htele:id|h[name]|h|r
        GameTele const* tele = handler->extractGameTeleFromLink((char*)args);
        if (!tele)
        {
            handler->SendSysMessage(LANG_COMMAND_TELE_NOTFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }
        std::string name = tele->name;
        sObjectMgr->DeleteGameTele(name);
        handler->SendSysMessage(LANG_COMMAND_TP_DELETED);
        return true;
    }

    // teleport player to given game_tele.entry
    static bool HandleTeleNameCommand(ChatHandler* handler, const char* args)
    {
        char* nameStr;
        char* teleStr;
        handler->extractOptFirstArg((char*)args, &nameStr, &teleStr);
        if (!teleStr)
            return false;

        Player* target;
        uint64 target_guid;
        std::string target_name;
        if (!handler->extractPlayerTarget(nameStr, &target, &target_guid, &target_name))
            return false;

        if (strcmp(teleStr, "$home") == 0)    // References target's homebind
        {
            if (target)
                target->TeleportTo(target->m_homebindMapId, target->m_homebindX, target->m_homebindY, target->m_homebindZ, target->GetOrientation());
            else
            {
                PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_HOMEBIND);
                stmt->setUInt32(0, target_guid);
                PreparedQueryResult resultDB = CharacterDatabase.Query(stmt);

                if (resultDB)
                {
                    Field* fieldsDB = resultDB->Fetch();
                    uint32 mapId = fieldsDB[0].GetUInt16();
                    uint32 zoneId = fieldsDB[1].GetUInt16();
                    float posX = fieldsDB[2].GetFloat();
                    float posY = fieldsDB[3].GetFloat();
                    float posZ = fieldsDB[4].GetFloat();

                    Player::SavePositionInDB(mapId, posX, posY, posZ, 0, zoneId, target_guid);
                }
            }

            return true;
        }

        // id, or string, or [name] Shift-click form |color|Htele:id|h[name]|h|r
        GameTele const* tele = handler->extractGameTeleFromLink(teleStr);
        if (!tele)
        {
            handler->SendSysMessage(LANG_COMMAND_TELE_NOTFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (target)
        {
            // check online security
            if (handler->HasLowerSecurity(target, 0))
                return false;

            std::string chrNameLink = handler->playerLink(target_name);

            if (target->IsBeingTeleported() == true)
            {
                handler->PSendSysMessage(LANG_IS_TELEPORTED, chrNameLink.c_str());
                handler->SetSentErrorMessage(true);
                return false;
            }

            handler->PSendSysMessage(LANG_TELEPORTING_TO, chrNameLink.c_str(), "", tele->name.c_str());
            if (handler->needReportToTarget(target))
                (ChatHandler(target->GetSession())).PSendSysMessage(LANG_TELEPORTED_TO_BY, handler->GetNameLink().c_str());

            // stop flight if need
            if (target->IsInFlight())
            {
                target->GetMotionMaster()->MovementExpired();
                target->CleanupAfterTaxiFlight();
            }
            // save only in non-flight case
            else
                target->SaveRecallPosition();

            target->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
        }
        else
        {
            // check offline security
            if (handler->HasLowerSecurity(nullptr, target_guid))
                return false;

            std::string nameLink = handler->playerLink(target_name);

            handler->PSendSysMessage(LANG_TELEPORTING_TO, nameLink.c_str(), handler->GetAcoreString(LANG_OFFLINE), tele->name.c_str());
            Player::SavePositionInDB(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation,
                                     sMapMgr->GetZoneId(tele->mapId, tele->position_x, tele->position_y, tele->position_z), target_guid);
        }

        return true;
    }

    //Teleport group to given game_tele.entry
    static bool HandleTeleGroupCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        // id, or string, or [name] Shift-click form |color|Htele:id|h[name]|h|r
        GameTele const* tele = handler->extractGameTeleFromLink((char*)args);
        if (!tele)
        {
            handler->SendSysMessage(LANG_COMMAND_TELE_NOTFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        MapEntry const* map = sMapStore.LookupEntry(tele->mapId);
        if (!map || map->IsBattlegroundOrArena())
        {
            handler->SendSysMessage(LANG_CANNOT_TELE_TO_BG);
            handler->SetSentErrorMessage(true);
            return false;
        }

        std::string nameLink = handler->GetNameLink(target);

        Group* grp = target->GetGroup();
        if (!grp)
        {
            handler->PSendSysMessage(LANG_NOT_IN_GROUP, nameLink.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        for (GroupReference* itr = grp->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            Player* player = itr->GetSource();

            if (!player || !player->GetSession())
                continue;

            // check online security
            if (handler->HasLowerSecurity(player, 0))
                return false;

            std::string plNameLink = handler->GetNameLink(player);

            if (player->IsBeingTeleported())
            {
                handler->PSendSysMessage(LANG_IS_TELEPORTED, plNameLink.c_str());
                continue;
            }

            handler->PSendSysMessage(LANG_TELEPORTING_TO, plNameLink.c_str(), "", tele->name.c_str());
            if (handler->needReportToTarget(player))
                (ChatHandler(player->GetSession())).PSendSysMessage(LANG_TELEPORTED_TO_BY, nameLink.c_str());

            // stop flight if need
            if (player->IsInFlight())
            {
                player->GetMotionMaster()->MovementExpired();
                player->CleanupAfterTaxiFlight();
            }
            // save only in non-flight case
            else
                player->SaveRecallPosition();

            player->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
        }

        return true;
    }

    static bool HandleTeleCommand(ChatHandler* handler, const char* args)
    {   
        if (!*args)
            return false;

        Player* me = handler->GetSession()->GetPlayer();

        uint32 spellsEscape[] =
        {
                642,          // Paladin: Divine Shield
                66,           // Mage: Invisibility
                5384,         // Hunter: Feign Death
                18461,        // Rogue: Vanish Server Side
                11958,        // Mage: Cold Snap
                58984,        // Night Elf: Shadowmeld
                14185,        // Rogue: Preparation
                1856,         // Rogue: Vanish Rank 1
                1857,         // Rogue: Vanish Rank 2
                26889,        // Rogue: Vanish Rank 3
                45438         // Mage: Ice Block
        };

        for (uint8 i = 0; i < 11; ++i)
        {
            uint32 remainingCooldown = me->GetSpellCooldownDelay(spellsEscape[i]);

            if (remainingCooldown > 0)
            {
                handler->SendSysMessage(60002);
                handler->SetSentErrorMessage(true);
                return false;
            }
        }

        // Verifica se o usuário possui pontos de donate
        QueryResult result1 = CharacterDatabase.PQuery("SELECT dp FROM etmaxxweb.users WHERE id = '%u' AND (dp > '0');", me->GetSession()->GetAccountId());
        // Verifica se o usuário já teve seus pontos descontados hoje.
        QueryResult result2 = CharacterDatabase.PQuery("SELECT vipdiscounted FROM etmaxxweb.users WHERE id = '%u' and vipdiscounted = '0';", me->GetSession()->GetAccountId());
        // Verifica se estamos habilitados a rodar comandos por 24H
        QueryResult result3 = CharacterDatabase.PQuery("SELECT vipdiscounted FROM etmaxxweb.users WHERE id = '%u' AND (vipdiscounted = '1');", me->GetSession()->GetAccountId());

        if (!result1 && !result3) {
            handler->SendSysMessage(60000);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // id, or string, or [name] Shift-click form |color|Htele:id|h[name]|h|r
        GameTele const* tele = handler->extractGameTeleFromLink((char*)args);

        if (!tele)
        {
            handler->SendSysMessage(LANG_COMMAND_TELE_NOTFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (me->IsInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }

        MapEntry const* map = sMapStore.LookupEntry(tele->mapId);
        if (!map || map->IsBattlegroundOrArena())
        {
            handler->SendSysMessage(LANG_CANNOT_TELE_TO_BG);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // stop flight if need
        if (me->IsInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            me->SaveRecallPosition();
        // Destino
        uint32 zoneDestino = sMapMgr->GetZoneId(tele->mapId, tele->position_x, tele->position_y, tele->position_z);
        // Destino
        uint32 zoneOrigem = sMapMgr->GetZoneId(me->GetMapId(), me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());

        // Cidades Horde
        uint32 orgrimmar = 1637;
        uint32 thunderbluff = 1638;
        uint32 undercity = 1497;
        uint32 silvermoon = 3487;

        // Mapas da Horda
        uint32 mulgore = 215;
        uint32 durotar = 14;
        uint32 tirisfal = 85;
        uint32 eversong = 3430;

        //Cidades Ally
        uint32 stormwind = 1519;
        uint32 ironforge = 1537;
        uint32 darnassus = 1657;
        uint32 theexodar = 3557;

        // Mapas da Ally
        uint32 elwynnforst = 12;
        uint32 dunmorogh = 1;
        uint32 teldrassil = 141;
        uint32 azuremystisle = 3524;

        if (!me->IsGameMaster())
        {
            if (me->getRace() == RACE_HUMAN || me->getRace() == RACE_NIGHTELF || me->getRace() == RACE_DWARF || me->getRace() == RACE_DRAENEI || me->getRace() == RACE_GNOME)
            {
                if (zoneOrigem == orgrimmar || zoneOrigem == thunderbluff || zoneOrigem == undercity || zoneOrigem == silvermoon ||
                    zoneDestino == orgrimmar || zoneDestino == thunderbluff || zoneDestino == undercity || zoneDestino == silvermoon ||
                    zoneDestino == mulgore || zoneDestino == durotar || zoneDestino == tirisfal || zoneDestino == eversong)
                {
                    handler->SendSysMessage(60003);
                    handler->SetSentErrorMessage(true);
                    return false;
                }
             
            }
            if (me->getRace() == RACE_ORC || me->getRace() == RACE_UNDEAD_PLAYER || me->getRace() == RACE_TAUREN || me->getRace() == RACE_TROLL || me->getRace() == RACE_BLOODELF)
            {
                if (zoneOrigem == stormwind || zoneOrigem == ironforge || zoneOrigem == darnassus || zoneOrigem == theexodar ||
                    zoneDestino == stormwind || zoneDestino == ironforge || zoneDestino == darnassus || zoneDestino == theexodar ||
                    zoneDestino == elwynnforst || zoneDestino == dunmorogh || zoneDestino == teldrassil || zoneDestino == azuremystisle)
                {
                    handler->SendSysMessage(60003);
                    handler->SetSentErrorMessage(true);
                    return false;
                }
            }
        }

        me->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);

        if (result2) {

            CharacterDatabase.PQuery("UPDATE etmaxxweb.users SET dp=dp-1, vipdiscounted=1 WHERE id='%u';", me->GetSession()->GetAccountId());
            CharacterDatabase.PQuery("UPDATE etmaxxweb.users SET usedate=UNIX_TIMESTAMP(NOW()) WHERE id='%u';", me->GetSession()->GetAccountId());
            CharacterDatabase.PQuery("UPDATE etmaxxweb.users SET expiredate=UNIX_TIMESTAMP(NOW() + INTERVAL 48 HOUR) WHERE id='%u';", me->GetSession()->GetAccountId());

            handler->SendSysMessage(60001);
            handler->SetSentErrorMessage(true);
        }

        QueryResult resultexpire = CharacterDatabase.PQuery("SELECT FROM_UNIXTIME(expiredate, '%%d-%%m-%%Y..%%H:%%I:%%s') as expiredate FROM etmaxxweb.users WHERE id = '%u';", me->GetSession()->GetAccountId());

        if (resultexpire) {
            Field* fields = resultexpire->Fetch();

            handler->PSendSysMessage("Seus benefícios VIP ficarão ativos até %s", fields[0].GetCString());
        }
            
        return true;
    }
};

void AddSC_tele_commandscript()
{
    new tele_commandscript();
}
