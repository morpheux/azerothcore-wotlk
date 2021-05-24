#include "loader.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "Language.h"
#include <Chat/Chat.h>

class instanceReset : public CreatureScript
{
public:
    instanceReset() : CreatureScript("instanceReset") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        uint32 resets = 0;

        QueryResult result = CharacterDatabase.PQuery("SELECT resets FROM character_cromi WHERE guid = %u", player->GetSession()->GetGuidLow());

        if (result) {
            Field* fields = result->Fetch();
            resets = fields[0].GetUInt32();
        }else{
            CharacterDatabase.PExecute("INSERT INTO character_cromi(guid, resets) VALUES (%u, %u)", player->GetSession()->GetGuidLow(), 10);
            CloseGossipMenuFor(player);
        }       
        
        if (resets == 0){
            ChatHandler(player->GetSession()).PSendSysMessage("Cromi: Você não possuí pontos suficientes para resetar as instâncias.");
            CloseGossipMenuFor(player);
        }else{
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Eu gostaria de resetar o cooldown de minhas instancias normais ao custo de 1 ponto de reset.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        }

        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Eu gostaria de resetar o cooldown das minhas instancias normais exceto ICC e Ruby sem custo.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "---------------------------------", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        //AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Comprar uma EtMaXx Instance Reset", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Resetar TODAS minhas instancias", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
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
            creature->MonsterWhisper("Todos os seus cooldowns foram resetados" , player);
            CloseGossipMenuFor(player);
        }

        if (action == GOSSIP_ACTION_INFO_DEF + 2)
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
                        if (itr->first != 631 || itr->first != 724) {
                            sInstanceSaveMgr->PlayerUnbindInstance(player->GetGUIDLow(), itr->first, Difficulty(i), true, player);
                            itr = m_boundInstances.begin();
                        }
                    }
                    else
                        ++itr;
                }
            }
            creature->MonsterWhisper("Seus cooldowns foram resetados exceto ICC e Ruby", player);
            CloseGossipMenuFor(player);
        }

        if (action == GOSSIP_ACTION_INFO_DEF + 3)
        {
            if(player->HasItemCount(60000,2000) && player->HasItemCount(60004,5)){
                player->DestroyItemCount(60000,2000,true);
                player->DestroyItemCount(60004,5,true);
                player->AddItem(800807,1);
                CloseGossipMenuFor(player);
            }else{
                creature->MonsterWhisper("Você precisa de 2000 EtMaXx Mark + 5 EtMaXx Mega Mark", player);
                CloseGossipMenuFor(player);
            }
        }

        if (action == GOSSIP_ACTION_INFO_DEF + 4)
        {
            if(player->HasItemCount(800807,1)){
                for (uint8 i = 0; i <= 3; ++i)
                {
                    BoundInstancesMap const& m_boundInstances = sInstanceSaveMgr->PlayerGetBoundInstances(player->GetGUIDLow(), Difficulty(i));
                    for (BoundInstancesMap::const_iterator itr = m_boundInstances.begin(); itr != m_boundInstances.end();)
                    {
                        if (itr->first != player->GetMapId())
                        {
                            sInstanceSaveMgr->PlayerUnbindInstance(player->GetGUIDLow(), itr->first, Difficulty(i), true, player);
                            itr = m_boundInstances.begin();
                        }
                        else
                            ++itr;
                    }
                }
                player->DestroyItemCount(800807,1,true);
                creature->MonsterWhisper("Todas suas instancias foram resetadas", player);
                CloseGossipMenuFor(player);
            }else{
                creature->MonsterWhisper("Você não tem uma EtMaXx Instance Reset", player);
                CloseGossipMenuFor(player);  
            }
            
        }

        return true;
    }
};

void AddInstanceResetScripts() {
    new instanceReset();
}
