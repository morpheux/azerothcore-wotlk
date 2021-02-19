#include "loader.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "Language.h"

class instanceReset : public CreatureScript
{
public:
    instanceReset() : CreatureScript("instanceReset") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        uint32 resets;

        QueryResult result = CharacterDatabase.PQuery("SELECT resets FROM character_cromi WHERE guid = %u", player->GetSession()->GetGuidLow());

        if (result) {
            Field* fields = result->Fetch();
            resets = fields[0].GetUInt32();
        }else{
            CharacterDatabase.PExecute("INSERT INTO character_cromi(guid, resets) VALUES (%u, %u)", player->GetSession()->GetGuidLow(), 3);
            CloseGossipMenuFor(player);
        }

        ClearGossipMenuFor(player);
        
        if (resets == 0){
            ChatHandler(player->GetSession()).PSendSysMessage("Cromi: Você não possuí pontos suficientes para resetar as instâncias.");
            CloseGossipMenuFor(player);
        }else{
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Eu gostaria de resetar o cooldown das minhas instancias normais ao custo de 1 ponto de reset.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        }
        
        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        ClearGossipMenuFor(player);
        uint32 diff = 1;

        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            //RAID_DIFFICULTY_10MAN_NORMAL = 0,
            //RAID_DIFFICULTY_25MAN_NORMAL = 1,
            //RAID_DIFFICULTY_10MAN_HEROIC = 2,
            //RAID_DIFFICULTY_25MAN_HEROIC = 3,

            for (uint8 i = 0; i <= diff; ++i)
            {
                BoundInstancesMap const& m_boundInstances = sInstanceSaveMgr->PlayerGetBoundInstances(player->GetGUIDLow(), Difficulty(i));
                for (BoundInstancesMap::const_iterator itr = m_boundInstances.begin(); itr != m_boundInstances.end();)
                {
                    //InstanceSave* save = itr->second.save;
                    if (itr->first != player->GetMapId())
                    {
                        //uint32 resetTime = itr->second.extended ? save->GetExtendedResetTime() : save->GetResetTime();
                        //uint32 ttr = (resetTime >= time(nullptr) ? resetTime - time(nullptr) : 0);
                        sInstanceSaveMgr->PlayerUnbindInstance(player->GetGUIDLow(), itr->first, Difficulty(i), true, player);
                        itr = m_boundInstances.begin();
                    }
                    else
                        ++itr;
                }
            }
            CharacterDatabase.PExecute("UPDATE character_cromi SET resets=resets-1 WHERE guid=%u", player->GetSession()->GetGuidLow());
            creature->MonsterWhisper("Seus cooldowns foram resetados" , player);
            CloseGossipMenuFor(player);
        }
        return true;
    }
};

class instanceResetWorld : public WorldScript
{
public:
    instanceResetWorld() : WorldScript("instanceResetWorld") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload)
        {
            std::string conf_path = _CONF_DIR;
            std::string cfg_file = conf_path + "/instance-reset.conf";
			#ifdef WIN32
            cfg_file = "instance-reset.conf";
			#endif
            std::string cfg_def_file = cfg_file + ".dist";

            sConfigMgr->LoadMore(cfg_def_file.c_str());
            sConfigMgr->LoadMore(cfg_file.c_str());
        }
    }
};

void AddInstanceResetScripts() {
    new instanceReset();
    new instanceResetWorld(); 
}
