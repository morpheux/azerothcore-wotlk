//by SymbolixDEV
//Reworked by Talamortis
#include "ScriptMgr.h"
#include "Config.h"
#include <Player.h>
#include "Group.h"
#include "GroupMgr.h"
#include "InstanceScript.h"
#include "Chat.h"

class Boss_Announcer : public PlayerScript
{
public:
	Boss_Announcer() : PlayerScript("Boss_Announcer") {}

    void OnCreatureKill(Player* player, Creature* boss)
    {
        std::string p_name;
        std::string g_name;
        std::string IsHeroicMode;
        std::string IsNormal;
        std::string tag_colour = "7bbef7";
        std::string plr_colour = "7bbef7";
        std::string guild_colour = "00ff00";
        std::string boss_colour = "ff0000";
        std::string alive_text = "00ff00";
        uint32 Alive_players = 0;
        uint32 Tanks = 0;
        uint32 Healers = 0;
        uint32 DPS = 0;
        std::ostringstream stream;

        if (player && boss)
        {
            Map* map = player->GetMap();
            std::string boss_name = boss->GetName();

            if (map)
            {
                if (boss->GetMap()->IsRaid() && boss->getLevel() > 80 && boss->IsDungeonBoss() && player->GetGroup())
                {
                    Map::PlayerList const & playerlist = map->GetPlayers();
                    
                    // Get Leader name
                    p_name = player->GetGroup()->GetLeaderName();

                    // 25 or 10 Men
                    if (player->GetMap()->Is25ManRaid())
                        IsNormal = "25";
                    else
                        IsNormal = "10";

                    // Heroic or Normal
                    if (player->GetMap()->IsHeroic())
                        IsHeroicMode = "|cffff0000Heroic|r";
                    else
                        IsHeroicMode = "|cff00ff00Normal|r";

                    for (Map::PlayerList::const_iterator itr = playerlist.begin(); itr != playerlist.end(); ++itr)
                    {
                        if (!itr->GetSource())
                            continue;

                        if (itr->GetSource()->IsAlive() && !itr->GetSource()->IsGameMaster())
                            Alive_players++;

                        if (itr->GetSource()->HasHealSpec() && !itr->GetSource()->IsGameMaster())
                            Healers++;
                        else if (itr->GetSource()->HasTankSpec() && !itr->GetSource()->IsGameMaster())
                            Tanks++;
                        else if (!itr->GetSource()->IsGameMaster())
                            DPS++;

                        uint32 buff = itr->GetSource()->GetTeamId() == TEAM_ALLIANCE ? 57723 : 57724;

                        if (itr->GetSource()->HasAura(buff))
                            itr->GetSource()->RemoveAura(buff);

                        // if we are in group lets get guild of the leader
                        if (player->GetGroup() && itr->GetSource()->GetGroup()->IsLeader(itr->GetSource()->GetGUID())) 
					    {
                            if (!itr->GetSource()->GetGuild())
                                g_name = "< Sem Guild >";
                            else 
                                g_name = itr->GetSource()->GetGuildName();

                        }
					}
                }

                stream << "|CFF" << tag_colour << "|r|cff" << plr_colour << " " << p_name << "|r's Guild |cff" << guild_colour << "" << g_name << "|r acabou de matar |CFF" << boss_colour << "[" << boss_name << "]|r com |cff" << alive_text << "" << Alive_players << " /" << IsNormal << "|r players vivos em " << IsHeroicMode << " mode, com o grupo de |cff" << tag_colour << "Tank: " << Tanks  <<"|r |cff" << guild_colour <<
                    " Healers: "<< Healers << "|r |cff" << boss_colour << " DPS: " << DPS << "|r";

				if (player->GetMap()->IsHeroic() || boss_name == "The Lich King")
                    sWorld->SendServerMessage(SERVER_MSG_STRING, stream.str().c_str());



                }
            }
        }
    }
};

void AddBoss_AnnouncerScripts()
{
	new Boss_Announcer;
}
