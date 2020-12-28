#include "loader.h"
#include "ScriptMgr.h"
#include "Configuration/Config.h"
#include "GossipDef.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Language.h"

class etmaxx_npc : public CreatureScript
{
public:
    etmaxx_npc() : CreatureScript("etmaxx_npc") { }

    // Step 1
    bool OnGossipHello(Player* player, Creature* creature) 
    {
            player->PlayerTalkClass->ClearMenus();

            if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 62500 && !player->HasSpell(75614))
                player->ADD_GOSSIP_ITEM(1, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed", GOSSIP_SENDER_MAIN, 1);

            player->ADD_GOSSIP_ITEM(1, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed1", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(2, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed2", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(3, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed3", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(4, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed4", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed5", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(6, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed6", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(7, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed7", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(8, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed8", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(9, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed9", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(10, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed10", GOSSIP_SENDER_MAIN, 1);
            
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case 1:
            player->AddItem(54811, -1);
            player->AddItem(54811, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Team: Item Adicionado em sua Bag. Parabéns!");
            break;
		}
		
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		
		return true;
	}
};

void AddNpcEtmaxxScripts()
{
    new etmaxx_npc();
}
