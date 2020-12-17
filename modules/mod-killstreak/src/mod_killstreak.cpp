/**
    This plugin can be used for common player customizations
 */

#include "ScriptPCH.h"
#include "Config.h"
#include <unordered_map>


uint32 conf_minAmmount = 0;
uint32 conf_PVPToken = 0;
bool conf_AnnounceType = 0;

/* CLASS COLORS */
std::string kill_streak_ClassColor[11] =
{
    "|cffC79C6E", // WARRIOR
    "|cffF58CBA", // PALADIN
    "|cffABD473", // HUNTER
    "|cffFFF569", // ROGUE
    "|cffFFFFFF", // PRIEST
    "|cffC41F3B", // DEATHKNIGHT
    "|cff0070DE", // SHAMAN
    "|cff40C7EB", // MAGE
    "|cff8787ED", // WARLOCK
    "", // ADDED IN MOP FOR MONK - NOT USED
    "|cffFF7D0A", // DRUID
};

struct SystemInfo
{
    uint32 KillStreak = 0;
    uint32 LastGUIDKill = 0;
    uint32 LastKillTime = 0;
};

static std::unordered_map<uint32, SystemInfo> KillingStreak;

class MODKillStreak_Config : public WorldScript
{
public: MODKillStreak_Config() : WorldScript("MODKillStreak_Config") { };
    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            std::string conf_path = _CONF_DIR;
            std::string cfg_file = conf_path + "/mod_killstreak.conf";
            std::string cfg_file_2 = cfg_file + ".dist";

            sConfigMgr->LoadMore(cfg_file_2.c_str());
            sConfigMgr->LoadMore(cfg_file.c_str());
            conf_minAmmount = sConfigMgr->GetIntDefault("KillStreak.MinAmount", 10);
            conf_PVPToken = sConfigMgr->GetIntDefault("KillStreak.PVPToken", 29434);
            conf_AnnounceType = sConfigMgr->GetBoolDefault("KillStreak.AnnounceGlobal", true);
        }
    }
};

class MODKillStreak : public PlayerScript{
public:

    MODKillStreak() : PlayerScript("MODKillStreak") { }

    void SendKillStreakMessage(Player* pKiller, char* msg) {
        if(conf_AnnounceType)
            sWorld->SendGlobalText(msg, NULL);
        else
            sWorld->SendZoneText(pKiller->GetZoneId(), msg, NULL, TEAM_NEUTRAL);
    }

    void OnPVPKill(Player *pKiller, Player *pVictim)
    {
        uint32 killerGUID;
        uint32 victimGUID;
        killerGUID = pKiller->GetGUID();
        victimGUID = pVictim->GetGUID();

        uint32 currentTime = sWorld->GetGameTime();
        if(killerGUID == victimGUID)
        {
            return;
        }
        if(KillingStreak[killerGUID].LastKillTime == 0){
            KillingStreak[killerGUID].LastKillTime = sWorld->GetGameTime();
        }
        else if  (sWorld->GetGameTime() - KillingStreak[killerGUID].LastKillTime >= 2 * 60) { // hold the kill streak only for 2 minutes
            KillingStreak[killerGUID].KillStreak = 0;
            KillingStreak[killerGUID].LastKillTime = sWorld->GetGameTime();
            KillingStreak[killerGUID].LastGUIDKill = 0;
        }
        if(KillingStreak[killerGUID].LastGUIDKill == victimGUID) {
            //return;
        }
        KillingStreak[killerGUID].KillStreak++;
        KillingStreak[victimGUID].KillStreak = 0;
        KillingStreak[killerGUID].LastGUIDKill = victimGUID;
        KillingStreak[victimGUID].LastGUIDKill = 0;
        KillingStreak[victimGUID].LastKillTime = 0;

        char msg[1000];

        if (KillingStreak[killerGUID].KillStreak % conf_minAmmount == 0) {
            pKiller->AddItem(conf_PVPToken, KillingStreak[killerGUID].KillStreak);
            switch (KillingStreak[killerGUID].KillStreak / conf_minAmmount) {
            case 1:
                sprintf(msg, "|cffFF0000[PVP System]|r %s%s|r killed %s%s|r and is on a |cff00FF96Killing Spree|r!", kill_streak_ClassColor[pKiller->getClass() - 1].c_str(), pKiller->GetName().c_str(), pVictim->GetName().c_str(), kill_streak_ClassColor[pVictim->getClass() - 1].c_str());
                SendKillStreakMessage(pKiller, msg);
                break;
            case 2:
                sprintf(msg, "|cffFF0000[PVP System]|r %s%s|r killed %s%s|r and is |cffA330C9Dominating|r!", kill_streak_ClassColor[pKiller->getClass() - 1].c_str(), pKiller->GetName().c_str(), pVictim->GetName().c_str(), kill_streak_ClassColor[pVictim->getClass() - 1].c_str());
                SendKillStreakMessage(pKiller, msg);
                break;
            case 3:
                sprintf(msg, "|cffFF0000[PVP System]|r %s%s|r killed %s%s|r and is |cffFF7D0AUnstoppable|r.", kill_streak_ClassColor[pKiller->getClass() - 1].c_str(), pKiller->GetName().c_str(), pVictim->GetName().c_str(), kill_streak_ClassColor[pVictim->getClass() - 1].c_str());
                SendKillStreakMessage(pKiller, msg);
                break;
            case 4:
                sprintf(msg, "|cffFF0000[PVP System]|r %s%s|r killed %s%s|r. |cff40C7EBGODLIKE MODE ENABLED|r!", kill_streak_ClassColor[pKiller->getClass() - 1].c_str(), pKiller->GetName().c_str(), pVictim->GetName().c_str(), kill_streak_ClassColor[pVictim->getClass() - 1].c_str());
                SendKillStreakMessage(pKiller, msg);
                break;
            case 5:
                sprintf(msg, "|cffFF0000[PVP System]|r %s%s|r killed %s%s|r. |cffCC0000SOMEBODY STOP HIM|r!.", kill_streak_ClassColor[pKiller->getClass() - 1].c_str(), pKiller->GetName().c_str(), pVictim->GetName().c_str(), kill_streak_ClassColor[pVictim->getClass() - 1].c_str());
                SendKillStreakMessage(pKiller, msg);
                break;
            }
        }
    }
};

void AddKillStreakScripts() {
    new MODKillStreak_Config();
    new MODKillStreak();
}
