#include "loader.h"
#include "ScriptMgr.h"
#include "Configuration/Config.h"
#include "GossipDef.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Language.h"

/*
    // Gossip defines
    GOSSIP_ACTION_TRADE                 = 1, BAGZINHA
    GOSSIP_ACTION_TRAIN                 = 2, ASINHA
    GOSSIP_ACTION_TAXI                  = 3, LIVRINHO
    GOSSIP_ACTION_GUILD                 = 4, ENGRENAGEM
    GOSSIP_ACTION_BATTLE                = 5, ENGRENAGEM
    GOSSIP_ACTION_BANK                  = 6, BAG COM DINDIN
    GOSSIP_ACTION_INN                   = 7, 3 PONTINHOS
    GOSSIP_ACTION_HEAL                  = 8, TABARD
    GOSSIP_ACTION_TABARD                = 9, ESPADAS
    GOSSIP_ACTION_AUCTION               = 10, PONTINHO
    GOSSIP_ACTION_INN_INFO              = 11, BALAO
    GOSSIP_ACTION_UNLEARN               = 12, BALAO
    GOSSIP_ACTION_INFO_DEF              = 1000, NAO USAR
*/


class etmaxx_npc : public CreatureScript
{
public:
    etmaxx_npc() : CreatureScript("etmaxx_npc") { }

    bool OnGossipHello(Player* player, Creature* creature) 
    {
            player->PlayerTalkClass->ClearMenus();

            if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 62500 && !player->HasSpell(75614))
                player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed", GOSSIP_SENDER_MAIN, 1);

            if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 50000 && !player->HasSpell(43688))
                player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/Ability_druid_challangingroar:50:50|tAmani War Bear", GOSSIP_SENDER_MAIN, 2);

            if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 37500 && (!player->HasSpell(16056) || !player->HasSpell(16081)))
			{
				if (player->GetTeamId(true) == TEAM_ALLIANCE) {
				player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/Ability_mount_whitetiger:50:50|tReins of the Ancient Frostsaber", GOSSIP_SENDER_MAIN, 3);
				}else{
				player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/Ability_mount_whitedirewolf:50:50|tHorn of the Arctic Wolf", GOSSIP_SENDER_MAIN, 3);
				}
			}

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
        case 2:
            player->AddItem(55293, -1);
            player->AddItem(55293, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Team: Item Adicionado em sua Bag. Parabéns!");
            break;
        case 3:
            if (player->GetTeamId(true) == TEAM_ALLIANCE) {
                player->AddItem(12302, -1);
                player->AddItem(12302, 1);
            }
            else {
                player->AddItem(12351, -1);
                player->AddItem(12351, 1);
            }
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
