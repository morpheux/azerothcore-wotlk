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
        if (!sConfigMgr->GetBoolDefault("instanceReset.Enable", true))
            return true;
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Eu gostaria de resetar o cooldown das minhas instancias normais.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        ClearGossipMenuFor(player);
        uint32 diff = 2;
        bool reseteiicc;
        bool reseeteioutras;

        reseteiicc == false;
        reseeteioutras == false;

        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            if (!sConfigMgr->GetBoolDefault("instanceReset.NormalModeOnly", true))
                diff = MAX_DIFFICULTY;
            for (uint8 i = 0; i < diff; ++i)
            {
                BoundInstancesMap const& m_boundInstances = sInstanceSaveMgr->PlayerGetBoundInstances(player->GetGUIDLow(), Difficulty(i));
                for (BoundInstancesMap::const_iterator itr = m_boundInstances.begin(); itr != m_boundInstances.end();)
                {
                    //InstanceSave* save = itr->second.save;
                    if (itr->first != player->GetMapId())
                    {
                        //uint32 resetTime = itr->second.extended ? save->GetExtendedResetTime() : save->GetResetTime();
                        //uint32 ttr = (resetTime >= time(nullptr) ? resetTime - time(nullptr) : 0);

                        if (itr->first == 631) {
                            if (player->HasItemCount(60000, 1, true)) {
                                player->DestroyItemCount(60000, 1, true);
                                sInstanceSaveMgr->PlayerUnbindInstance(player->GetGUIDLow(), itr->first, Difficulty(i), true, player);
                                reseteiicc == true;
                            }
                        }
                        else {
                            sInstanceSaveMgr->PlayerUnbindInstance(player->GetGUIDLow(), itr->first, Difficulty(i), true, player);
                            reseeteioutras == true;
                        }

                        itr = m_boundInstances.begin();
                    }
                    else
                        ++itr;
                }
            }

            if (reseteiicc && reseeteioutras) {
                creature->MonsterWhisper("Todos os cooldowns das suas instances e dungeons foram resetados.", player);
            }
            else if(reseteiicc && !reseeteioutras){
                creature->MonsterWhisper("Todas as suas Icecrown Citadel normais foram resetadas.", player);
            }
            else if (!reseteiicc && reseeteioutras) {
                creature->MonsterWhisper("Todas as suas Dungeons e Instancias excluindo Icecrown Citadel normais foram resetadas.", player);
            }
            else {
                creature->MonsterWhisper("Não encontrei instances para resetar.", player);
            }


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

