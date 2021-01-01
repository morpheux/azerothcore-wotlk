#include "loader.h"
#include "ScriptMgr.h"
#include "Configuration/Config.h"
#include "GossipDef.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Language.h"
#include <Chat/Chat.h>

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
    etmaxx_npc() : CreatureScript("etmaxx_npc_VIPChange") { }

    bool OnGossipHello(Player* player, Creature* creature) 
    {
            player->PlayerTalkClass->ClearMenus();

            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "!!! ATENÇÃO !!! - Este NPC irá DESTRUIR seu item VIP para te dar uma EtMaXx Upgrade Mark", GOSSIP_SENDER_MAIN, 5000);

            if (player->HasItemCount(40402,1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_axe_61:18:18|tVIP Tank Axe", GOSSIP_SENDER_MAIN, 1);

            if (player->HasItemCount(47898, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_axe_104:18:18|tVIP One Hand Axe", GOSSIP_SENDER_MAIN, 2);

            if (player->HasItemCount(34179, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_offhand_sunwell_d_02:18:18|tVIP Off-Hand Caster", GOSSIP_SENDER_MAIN, 3);

            if (player->HasItemCount(34206, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_offhand_sunwell_d_01:18:18|tVIP Off-Hand Healer", GOSSIP_SENDER_MAIN, 4);

            if (player->HasItemCount(49888, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_axe_113:18:18|tVIP Two-Hand Axe", GOSSIP_SENDER_MAIN, 5);

            if (player->HasItemCount(49981, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_crossbow_38:18:18|tVIP Crossbow", GOSSIP_SENDER_MAIN, 6);

            if (player->HasItemCount(51450, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_rifle_39:18:18|tVIP Gun", GOSSIP_SENDER_MAIN, 7);

            if (player->HasItemCount(51561, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_rifle_39:18:18|tVIP Tank Gun", GOSSIP_SENDER_MAIN, 8);

            if (player->HasItemCount(50303, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_mace_78:18:18|tVIP One-Hand Mace", GOSSIP_SENDER_MAIN, 9);

            if (player->HasItemCount(40395, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_mace_82:18:18|tVIP Main-Hand Mace Spell", GOSSIP_SENDER_MAIN, 10);

            if (player->HasItemCount(42322, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_hammer_31:18:18|tVIP Two-Hand Mace", GOSSIP_SENDER_MAIN, 11);

            if (player->HasItemCount(49301, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_spear_08:18:18|tVIP Polearm Hunter", GOSSIP_SENDER_MAIN, 12);

            if (player->HasItemCount(51791, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_shield_74:18:18|tVIP Shield Spell", GOSSIP_SENDER_MAIN, 13);

            if (player->HasItemCount(47079, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_shield_69:18:18|tVIP Shield Healer", GOSSIP_SENDER_MAIN, 14);

            if (player->HasItemCount(50794, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_shield_73:18:18|tVIP Shield Tank", GOSSIP_SENDER_MAIN, 15);

            if (player->HasItemCount(47517, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_sword_144:18:18|tVIP Main-Hand Sword Spell", GOSSIP_SENDER_MAIN, 16);

			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case 1:
            player->DestroyItemCount(40402, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 2:
            player->DestroyItemCount(47898, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 3:
            player->DestroyItemCount(34179, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 4:
            player->DestroyItemCount(34206, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 5:
            player->DestroyItemCount(49888, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.!");
            break;
        case 6:
            player->DestroyItemCount(49981, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 7:
            player->DestroyItemCount(51450, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 8:
            player->DestroyItemCount(51561, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 9:
            player->DestroyItemCount(50303, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 10:
            player->DestroyItemCount(40395, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 11:
            player->DestroyItemCount(42322, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 12:
            player->DestroyItemCount(49301, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 13:
            player->DestroyItemCount(51791, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 14:
            player->DestroyItemCount(47079, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 15:
            player->DestroyItemCount(50794, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 16:
            player->DestroyItemCount(47517, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            break;
        case 5000
            OnGossipHello(player, creature);
            break;
		}
		
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		
		return true;
	}
};

void AddNpcEtmaxxVIPChange()
{
    new etmaxx_npc_VIPChange();
}
