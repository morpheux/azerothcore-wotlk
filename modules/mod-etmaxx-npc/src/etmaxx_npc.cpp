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

            if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 62500)
                player->ADD_GOSSIP_ITEM(NULL, "Celestial Steed", GOSSIP_SENDER_MAIN, 1);
            

            player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/INV_BannerPVP_01:50:50|tCelestial Steed", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tUNUSED2", GOSSIP_SENDER_MAIN, 3);
            //player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/INV_Inscription_Scroll:50:50|tUNUSED3", GOSSIP_SENDER_MAIN, 4);
            
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

        return true;
    }

    void OnGossipSelect(Player* player, Item* /*item*/, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case 1:
            player->AddItem(54811, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Please log out for race change.");
            break;
		}
	}
};

void AddNpcEtmaxxScripts()
{
    new etmaxx_npc();
}
