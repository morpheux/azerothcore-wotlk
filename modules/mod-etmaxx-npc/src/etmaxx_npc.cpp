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

///////////////////////////////////////////////////////////////////////////////////
/////////////	EtMaXx PvP Reward NPC								///////////////
///////////////////////////////////////////////////////////////////////////////////
class etmaxx_npc : public CreatureScript
{
public:
    etmaxx_npc() : CreatureScript("etmaxx_npc") { }

    bool OnGossipHello(Player* player, Creature* creature) 
    {
            player->PlayerTalkClass->ClearMenus();

            if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 62500 && !player->HasSpell(75614))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/Ability_mount_celestialhorse:50:50|tCelestial Steed", GOSSIP_SENDER_MAIN, 1);

            if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 50000 && !player->HasSpell(43688))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/Ability_druid_challangingroar:50:50|tAmani War Bear", GOSSIP_SENDER_MAIN, 2);

            if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 37500)
			{
				if (player->GetTeamId(true) == TEAM_ALLIANCE && !player->HasSpell(16081))
				player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/Ability_mount_whitetiger:50:50|tReins of the Ancient Frostsaber", GOSSIP_SENDER_MAIN, 3);
			
				if (player->GetTeamId(true) == TEAM_HORDE && !player->HasSpell(16081))
				player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/Ability_mount_whitedirewolf:50:50|tHorn of the Arctic Wolf", GOSSIP_SENDER_MAIN, 3);
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
            player->DestroyItemCount(54811, 1, true);
            player->AddItem(54811, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Team: Item Adicionado em sua Bag. Parabéns!");
            break;
        case 2:
            player->DestroyItemCount(33809, 1, true);
            player->AddItem(33809, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Team: Item Adicionado em sua Bag. Parabéns!");
            break;
        case 3:
		{
            if (player->GetTeamId(true) == TEAM_ALLIANCE)
			{
                player->DestroyItemCount(12302, 1, true);
                player->AddItem(12302, 1);
			}
				
			if (player->GetTeamId(true) == TEAM_HORDE)
			{
                player->DestroyItemCount(12351, 1, true);
                player->AddItem(12351, 1);
			}
        }
        
        ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Team: Item Adicionado em sua Bag. Parabéns!");

            break;
		}
		
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		
		return true;
	}
};

///////////////////////////////////////////////////////////////////////////////////
/////////////	        EtMaXx VIP Desintegradorious		     	///////////////
///////////////////////////////////////////////////////////////////////////////////

enum Actions
{
    ACTION_NONE = 0,
    ACTION_CLOSE = 1005
};

class etmaxx_vip : public CreatureScript
{
public:
    etmaxx_vip() : CreatureScript("etmaxx_vip") { }

    bool OnGossipHello(Player* player, Creature* creature) 
    {
            player->PlayerTalkClass->ClearMenus();

            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "-----!!! ATENÇÃO !!!-----", GOSSIP_SENDER_MAIN, 5000);

            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Este NPC irá --> DESTRUIR <-- seu item VIP para te dar uma EtMaXx Upgrade Mark", GOSSIP_SENDER_MAIN, 5000);

            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "--------------------------", GOSSIP_SENDER_MAIN, 5000);

            if (player->HasItemCount(40402, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_axe_61:25:25|tVIP Tank Axe", GOSSIP_SENDER_MAIN, 2);

            if (player->HasItemCount(47898, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_axe_104:25:25|tVIP One Hand Axe", GOSSIP_SENDER_MAIN, 3);

            if (player->HasItemCount(34179, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_offhand_sunwell_d_02:25:25|tVIP Off-Hand Caster", GOSSIP_SENDER_MAIN, 4);

            if (player->HasItemCount(34206, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_offhand_sunwell_d_01:25:25|tVIP Off-Hand Healer", GOSSIP_SENDER_MAIN, 5);

            if (player->HasItemCount(49888, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_axe_113:25:25|tVIP Two-Hand Axe", GOSSIP_SENDER_MAIN, 6);

            if (player->HasItemCount(49981, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_crossbow_38:25:25|tVIP Crossbow", GOSSIP_SENDER_MAIN, 7);

            if (player->HasItemCount(51450, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_rifle_39:25:25|tVIP Gun", GOSSIP_SENDER_MAIN, 8);

            if (player->HasItemCount(51561, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_rifle_39:25:25|tVIP Tank Gun", GOSSIP_SENDER_MAIN, 9);

            if (player->HasItemCount(50303, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_mace_78:25:25|tVIP One-Hand Mace", GOSSIP_SENDER_MAIN, 10);

            if (player->HasItemCount(40395, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_mace_82:25:25|tVIP Main-Hand Mace Spell", GOSSIP_SENDER_MAIN, 11);

            if (player->HasItemCount(42322, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_hammer_31:25:25|tVIP Two-Hand Mace", GOSSIP_SENDER_MAIN, 12);

            if (player->HasItemCount(49301, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_spear_08:25:25|tVIP Polearm Hunter", GOSSIP_SENDER_MAIN, 13);

            if (player->HasItemCount(51791, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_shield_74:25:25|tVIP Shield Spell", GOSSIP_SENDER_MAIN, 14);

            if (player->HasItemCount(47079, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_shield_69:25:25|tVIP Shield Healer", GOSSIP_SENDER_MAIN, 15);

            if (player->HasItemCount(50794, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_shield_73:25:25|tVIP Shield Tank", GOSSIP_SENDER_MAIN, 16);

            if (player->HasItemCount(47517, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_sword_144:25:25|tVIP Main-Hand Sword Spell", GOSSIP_SENDER_MAIN, 17);

            if (player->HasItemCount(51010, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_sword_154:25:25|tVIP One-Hand Sword", GOSSIP_SENDER_MAIN, 18);

            if (player->HasItemCount(18348, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_sword_01:25:25|tVIP One-Hand Sword Tank", GOSSIP_SENDER_MAIN, 19);

            if (player->HasItemCount(33478, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_sword_108:25:25|tVIP Two-Hand Sword", GOSSIP_SENDER_MAIN, 20);

            if (player->HasItemCount(47302, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_staff_97:25:25|tVIP Staff Druid", GOSSIP_SENDER_MAIN, 21);

            if (player->HasItemCount(47524, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_staff_98:25:25|tVIP Staff Critical", GOSSIP_SENDER_MAIN, 22);

            if (player->HasItemCount(40489, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_staff_83:25:25|tVIP Staff Haste", GOSSIP_SENDER_MAIN, 23);

            if (player->HasItemCount(32945, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_hand_14:25:25|tVIP Off-Hand Fist Weapon", GOSSIP_SENDER_MAIN, 24);

            if (player->HasItemCount(32946, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_hand_14:25:25|tVIP Main-Hand Fist Weapon", GOSSIP_SENDER_MAIN, 25);

            if (player->HasItemCount(47255, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_shortblade_94:25:25|tVIP One-Hand Dagger", GOSSIP_SENDER_MAIN, 26);

            if (player->HasItemCount(40408, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_shortblade_82:25:25|tVIP Main-Hand Dagger Spell", GOSSIP_SENDER_MAIN, 27);

            if (player->HasItemCount(45086, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_throwingknife_08:25:25|tVIP Throwm Weapon", GOSSIP_SENDER_MAIN, 28);

            if (player->HasItemCount(50638, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_bow_55:25:25|tVIP Bow", GOSSIP_SENDER_MAIN, 29);

            if (player->HasItemCount(45170, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_wand_29:25:25|tVIP Wand Spell", GOSSIP_SENDER_MAIN, 30);

            if (player->HasItemCount(34348, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_wand_24:25:25|tVIP Wand Healer", GOSSIP_SENDER_MAIN, 31);

            if (player->HasItemCount(40704, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_hand_06:25:25|tVIP Off-Hand Fist Weapon (Fast)", GOSSIP_SENDER_MAIN, 32);

            if (player->HasItemCount(51384, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_weapon_shortblade_102:25:25|tVIP Off-Hand Dagger (Fast)", GOSSIP_SENDER_MAIN, 33);

            if (player->HasItemCount(47528, 1))
                player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_mace_101:25:25|tVIP One-Hand Mace Tank", GOSSIP_SENDER_MAIN, 34);
            
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        if (action == ACTION_CLOSE)
        {
            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        switch (action)
        {

        case 2:
            player->DestroyItemCount(40402, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 3:
            player->DestroyItemCount(47898, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 4:
            player->DestroyItemCount(34179, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 5:
            player->DestroyItemCount(34206, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 6:
            player->DestroyItemCount(49888, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 7:
            player->DestroyItemCount(49981, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 8:
            player->DestroyItemCount(51450, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 9:
            player->DestroyItemCount(51561, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 10:
            player->DestroyItemCount(50303, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 11:
            player->DestroyItemCount(40395, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 12:
            player->DestroyItemCount(42322, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 13:
            player->DestroyItemCount(49301, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 14:
            player->DestroyItemCount(51791, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 15:
            player->DestroyItemCount(47079, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 16:
            player->DestroyItemCount(50794, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;
        case 17:
            player->DestroyItemCount(47517, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 18:
            player->DestroyItemCount(51010, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 19:
            player->DestroyItemCount(18348, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 20:
            player->DestroyItemCount(33478, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 21:
            player->DestroyItemCount(47302, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 22:
            player->DestroyItemCount(47524, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 23:
            player->DestroyItemCount(40489, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 24:
            player->DestroyItemCount(32945, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 25:
            player->DestroyItemCount(32946, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 26:
            player->DestroyItemCount(47255, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 27:
            player->DestroyItemCount(40408, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 28:
            player->DestroyItemCount(45086, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 29:
            player->DestroyItemCount(50638, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 30:
            player->DestroyItemCount(45170, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 31:
            player->DestroyItemCount(34348, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 32:
            player->DestroyItemCount(40704, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 33:
            player->DestroyItemCount(51384, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 34:
            player->DestroyItemCount(47528, 1, true);
            player->AddItem(60007, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Upgrade Mark Adicionado em sua Bag.");
            OnGossipHello(player, creature);
            break;

        case 5000:
            OnGossipHello(player, creature);
            break;

		}

		
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		
		return true;
	}
};

///////////////////////////////////////////////////////////////////////////////////
/////////////               NPC Battle Pass                         ///////////////
///////////////////////////////////////////////////////////////////////////////////

class etmaxx_battlepass : public CreatureScript
{
public:
    etmaxx_battlepass() : CreatureScript("etmaxx_battlepass") { }

    uint32 bpvip = 0;
    uint32 points = 0;
    


    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();
        QueryResult result = CharacterDatabase.PQuery("SELECT bpvip,points FROM battlepass WHERE guid = %u", player->GetSession()->GetGuidLow());
        if (result) {
            Field* fields = result->Fetch();
            bpvip = fields[0].GetUInt32();
            points = fields[1].GetUInt32();
        }

        if (result && bpvip == 0) {
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Quero participar do EtMaXx VIP Battle Pass", GOSSIP_SENDER_MAIN, 2);

            if (player->HasItemCount(80001, 1, true)) {
                player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Daily Mark", GOSSIP_SENDER_MAIN, 4);
            }
            if (player->HasItemCount(80002, 1, true)) {
                player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Week Mark", GOSSIP_SENDER_MAIN, 5);
            }
            if (player->HasItemCount(80003, 1, true)) {
                player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Unique Mark", GOSSIP_SENDER_MAIN, 6);
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Quero ver meus Battle Points", GOSSIP_SENDER_MAIN, 3);
        }
        else if(result && bpvip == 1) {
            if (player->HasItemCount(80001, 1, true)) {
                player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Daily Mark", GOSSIP_SENDER_MAIN, 4);
            }
            if (player->HasItemCount(80002, 1, true)) {
                player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Week Mark", GOSSIP_SENDER_MAIN, 5);
            }
            if (player->HasItemCount(80003, 1, true)) {
                player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Unique Mark", GOSSIP_SENDER_MAIN, 6);
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Quero ver meus Battle Points", GOSSIP_SENDER_MAIN, 3);
        }
        else {
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Quero Participar do EtMaXx Battle Pass", GOSSIP_SENDER_MAIN, 1);
        }

        player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "-------------", GOSSIP_SENDER_MAIN, 5000);
        player->ADD_GOSSIP_ITEM(NULL, "Me Mostre o Battle Pass", GOSSIP_SENDER_MAIN, 100);

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case 1:
            CharacterDatabase.PExecute("INSERT INTO battlepass(guid, bpvip, points) VALUES (%u, %u, %u)", player->GetSession()->GetGuidLow(), 0, 0);
            ChatHandler(player->GetSession()).PSendSysMessage("Parabens, agora você está com Battle Pass Ativo. Fale com o NPC novamente");
            break;

        case 2:
            if (player->HasItemCount(80000, 1)) {
                player->DestroyItemCount(80000, 1, true);
                CharacterDatabase.PExecute("UPDATE battlepass SET bpvip = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por adquirir o EtMaXx VIP Battle Pass");
                player->PlayerTalkClass->SendCloseGossip();
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você precisa de um EtMaXx VIP Battle Pass Mark para participar do Battle Pass VIP. Você pode adquirir essa Mark no site: www.etmaxx.com.br");
            }
            break;

        case 4:
            if (player->HasItemCount(80001, 1)) {
                player->DestroyItemCount(80001, 1, true);
                points = points + 8;
                CharacterDatabase.PExecute("UPDATE battlepass SET pointis = %u WHERE guid = %u", points, player->GetSession()->GetGuidLow());
            }
            break;

        case 5:
            if (player->HasItemCount(80002, 1)) {
                player->DestroyItemCount(80002, 1, true);
                points = points + 40;
                CharacterDatabase.PExecute("UPDATE battlepass SET pointis = %u WHERE guid = %u", points, player->GetSession()->GetGuidLow());
            }
            break;

        case 6:
            if (player->HasItemCount(80003, 1)) {
                player->DestroyItemCount(80003, 1, true);
                points = points + 280;
                CharacterDatabase.PExecute("UPDATE battlepass SET pointis = %u WHERE guid = %u", points, player->GetSession()->GetGuidLow());
            }
            break;

        case 100:
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Esta são as recompensas do Battle Pass deste mes:", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Battle Pass Normal:", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t5 000 de Gold - 100 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t10 000 de Gold - 200 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_summonchampion:25:25|t30 Emblem of Triumph - 300 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01|t30 Emblem of Frost - 400 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t10 000 Honor Points - 500 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_03:25:25|tEtMaXx Transmog Mark - 700 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_petcarrier_01:25:25|tWorg Pup (PET) - 900 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_shirt_black_01:25:25|tMega Shirt Reset - 1000 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "------------------", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Se possuir o Battle Pass VIP além das recompensas normais você receberá:", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t5 000 de Gold - 100 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t20 Emblem of Frost - 200 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t10 000 Honor Points  - 300 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t40 Emblem of Frost - 400 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:25:25|t200 Arena Points - 500 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:25:25|t400 Arena Points - 600 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|tEtMaXx Transmog Mark - 700 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:25:25|t600 Arena Points - 800 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_jewelry_amulet_01:25:25|tEtMaXx Mount Mark - 900 Pontos", GOSSIP_SENDER_MAIN, 34);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|tVIP Container - 1000 Pontos", GOSSIP_SENDER_MAIN, 34);
            break;

        case 3:
            QueryResult result = CharacterDatabase.PQuery("SELECT points FROM battlepass WHERE guid = %u", player->GetSession()->GetGuidLow());
            Field* fields = result->Fetch();
            points = fields[0].GetUInt32();
            ChatHandler(player->GetSession()).PSendSysMessage("Seus Pontos: %u",points);
            break;
        }


        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

        return true;
    }

};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC transmog vendor                   ///////////////
///////////////////////////////////////////////////////////////////////////////////;
class etmaxx_transmog_vendor : public CreatureScript
{
public:
    etmaxx_transmog_vendor() : CreatureScript("etmaxx_transmog_vendor") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_bone_humanskull_01:30:30:-18:0|t1000 Enemy Head + 50.000 Honor", 10, 0);

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_frostemblem_01:30:30:-18:0|t200 Emblems of Frost", 20, 0);

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:30:30:-18:0|t1300 de Arena Rating + 200 Arena Points", 30, 0);

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);

        if (player->HasItemCount(80004, 1, true)) {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_sword_26:30:30:-18:0|tComprar uma Arma", 50, 0);
        }
              
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-18:0|tUpdate menu", 100, 0);

        SendGossipMenuFor(player, 800800, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender) {
            case 100:  // Main menu
            {
                OnGossipHello(player, creature);
            } break;

            case 10:
            {
                if (player->HasItemCount(80004, 1)) {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVocê só pode ter 1 EtMaXx Transmog Mark, gaste a sua para pegar outra", 100, 0);
                    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                else if (player->HasItemCount(600500, 1000, true) && (player->GetHonorPoints() >= 50000)) {
                    player->DestroyItemCount(600500, 1000, true);
                    player->ModifyHonorPoints(-50000);
                    player->AddItem(80004, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por adquirir uma EtMaXx Transmog Mark");
                    CloseGossipMenuFor(player);
                }
                else {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVocê precisa de 1000 enemy Head + 50.000 de Honor", 100, 0);
                    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
            } break;

            case 20:
            {
                if (player->HasItemCount(80004, 1)) {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVocê só pode ter 1 EtMaXx Transmog Mark, gaste a sua para pegar outra", 100, 0);
                    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                else if (player->HasItemCount(49426, 200, true)) {
                    player->DestroyItemCount(49426, 200, true);
                    player->AddItem(80004, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por adquirir uma EtMaXx Transmog Mark");
                    CloseGossipMenuFor(player);
                }
                else {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVocê precisa de 200 Emblem of Frost", 100, 0);
                    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
            } break;

            case 30:
            {
                if (player->HasItemCount(80004, 1)) {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVocê só pode ter 1 EtMaXx Transmog Mark, gaste a sua para pegar outra", 100, 0);
                    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                else if (player->GetArenaPersonalRating(0) >= 1300 && player->GetArenaPoints() >= 200) {
                    player->ModifyArenaPoints(-200);
                    player->AddItem(80004, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por adquirir uma EtMaXx Transmog Mark");
                    CloseGossipMenuFor(player);
                }
                else {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVocê precisa de 1300 de Arena Rating + 200 Arena Points", 100, 0);
                    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
            } break;
            // Menu de Armas
            case 50:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_61:30:30:-18:0|tTwo-Hand Axe", 1000, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_03:30:30:-18:0|tOne-Hand Axe", 2000, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_shortblade_05:30:30:-18:0|tDagger", 3000, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_gauntlets_31:30:30:-18:0|tFirst Weapon", 4000, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_mace_07:30:30:-18:0|tOne-Hand Mace", 5000, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_17:30:30:-18:0|tTwo-Hand Mace", 6000, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_10:30:30:-18:0|tOne-Hand Sword", 7000, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_70:30:30:-18:0|tTwo-Hand Sword", 8000, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_spear_05:30:30:-18:0|tPolearm", 9000, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_94:30:30:-18:0|tStaff", 10000, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_05:30:30:-18:0|tBow", 11000, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_53:30:30:-18:0|tShield", 12000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 100, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;
            // Machados 2Hand
            case 1000:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_69:30:30:-18:0|tAxe of Shattered Dreams", 34794, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_120:30:30:-18:0|tBryntroll, the Bone Arbiter", 50709, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_40:30:30:-18:0|tCrystalforged War Axe", 31291, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_106:30:30:-18:0|tDual-blade Butcher", 47446, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_67:30:30:-18:0|tEthereum Nexus-Reaver", 30722, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_102:30:30:-18:0|tStormedge", 45458, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_95:30:30:-18:0|tTitansteel Defender", 44948, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 50, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;
            //Machados 1Hand
            case 2000:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_40:30:30:-18:0|tBladespire Broadaxe", 25208, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_62:30:30:-18:0|tBreeching Comet", 34616, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_108:30:30:-18:0|tAxe of the Sen'jin Protector", 45204, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_axe_65:30:30:-18:0|tFirebrand Battleaxe", 27490, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 50, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            //Adagas
            case 3000:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_shortblade_102:30:30:-18:0|tBloodsipper", 51846, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_shortblade_38:30:30:-18:0|tEmerald Ripper", 28524, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_shortblade_06:30:30:-18:0|tHoned Fang of the Mystics", 49494, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_shortblade_29:30:30:-18:0|tFang of Korialstrasz", 21523, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_shortblade_31:30:30:-18:0|tFang of Venoxis", 19903, 0);
                
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 50, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            //Armas de Punho
            case 4000:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_hand_09:30:30:-18:0|tArm Blade of Augelmir", 35573, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_hand_01:30:30:-18:0|tNexus-Claw", 29371, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_hand_20:30:30:-18:0|tCalamity's Grasp", 40383, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 50, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            //Maças 1Hand
            case 5000:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_mace_32:30:30:-18:0|tAmani Punisher", 33283, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_mace_71:30:30:-18:0|tArchon's Gavel", 34199, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_mace_44:30:30:-18:0|tBloodskull Destroyer", 28210, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_mace_27:30:30:-18:0|tHammer of the Astral Plane", 39423, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_mace_59:30:30:-18:0|tHammer of Wrenching Change", 44747, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 50, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            //Maças 2Hand
            case 6000:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_mace_52:30:30:-18:0|tGladiator's Bonegrinder", 28299, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_mace_25:30:30:-18:0|tDemise", 39245, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_28:30:30:-18:0|tHammer of the Naaru", 28800, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_mace_84:30:30:-18:0|tTitansteel Destroyer", 41257, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_mace_116:30:30:-18:0|tCryptmaker", 50603, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 50, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            //Espada 2Hand
            case 8000:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_2h_ashbringercorrupt:30:30:-18:0|tCorrupted Ashbringer", 22691, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_136:30:30:-18:0|tAesir's Edge", 45868, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_116:30:30:-18:0|tApolyon, the Soul-Render", 34247, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_59:30:30:-18:0|tSin'dorei Warblade", 22995, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_51:30:30:-18:0|tWarp-Storm Warblade", 28400, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 50, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            //Espada 1Hand
            case 7000:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_shortblade_102:30:30:-18:0|tBlade of the Archmage", 29153, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_76:30:30:-18:0|tBlinkstrike", 31332, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_11:30:30:-18:0|tContinuum Blade", 29185, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_119:30:30:-18:0|tGhoulslicer", 49827, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_73:30:30:-18:0|tFang of the Leviathan", 30095, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 50, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            //polearm
            case 9000:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_halberd13:30:30:-18:0|tHellreaver", 24044, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_101:30:30:-18:0|tFordragon Blades", 47979, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_spear_01:30:30:-18:0|tFlame Wrath", 11809, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_halberd_12:30:30:-18:0|tHalberd of Smiting", 19874, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_halberd_31:30:30:-18:0|tHellion Glaive", 47491, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 50, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            //Staff
            case 10000:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_draenei_a_03:30:30:-18:0|tExodar Life-Staff", 30732, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_12:30:30:-18:0|tMonster - Staff, Dalaran Red", 43619, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_83:30:30:-18:0|tStaff of Draconic Combat", 37360, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_61:30:30:-18:0|tStaff of Immaculate Recovery", 32344, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_100:30:30:-18:0|tParagon's Breadth", 48710, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 50, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            //Bow
            case 11000:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_55:30:30:-18:0|tNjorndar Bone Bow", 51927, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_51:30:30:-18:0|tGolemheart Longbow", 46342, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_31:30:30:-18:0|tFurious Gladiator's Longbow", 42491, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 50, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            //Shield
            case 12000:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_58:30:30:-18:0|tRoyal Crest of Lordaeron", 43085, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_34:30:30:-18:0|tZom's Crackling Bulwark", 44313, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_67:30:30:-18:0|tBulwark of Algalon", 45587, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tBulwark of Azzinoth", 32375, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_38:30:30:-18:0|tFelstone Bulwark", 32255, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_53:30:30:-18:0|tBrutal Gladiator's Shield Wall", 35094, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 50, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            //Entregando Axe 2Hand
            case 34794:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(34794, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 50709:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(50709, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 31291:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(31291, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 47446:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(47446, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 30722:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(30722, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 45458:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(45458, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 44948:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(44948, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            //Entregando Axe 1Hand
            case 25208:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(25208, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 34616:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(34616, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 45204:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(45204, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 27490:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(27490, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            //Entregando Daggers
            case 51846:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(51846, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 28524:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(28524, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 49494:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(49494, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 21523:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(21523, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 19903:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(19903, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            //Entregando Armas de Punho
            case 35573:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(35573, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 29371:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(29371, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 40383:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(40383, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            //Entregando Mace 1Hand
            case 33283:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(33283, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 34199:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(34199, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 28210:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(28210, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 39423:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(39423, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 44747:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(44747, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            //Entregando Mace 2Hand
            case 28299:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(28299, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 39245:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(39245, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 28800:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(28800, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break; 

            case 41257:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(41257, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 50603:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(50603, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            //Entregando Espada 2Hand
            case 22691:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(22691, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 45868:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(45868, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 34247:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(34247, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 22995:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(22995, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 28400:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(28400, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            //Entrega de Espada 1Hand
            case 29153:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(29153, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 31332:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(31332, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 29185:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(29185, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 49827:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(49827, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 30095:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(30095, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            //Entrega de Polearm
            case 24044:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(24044, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 47979:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(47979, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 11809:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(11809, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 19874:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(19874, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 47491:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(47491, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            //Entrega de Staff
            case 30732:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(30732, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 43619:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(43619, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 37360:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(37360, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 32344:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(32344, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 48710:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(48710, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            //Entrega de Bow
            case 51927:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(51927, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 46342:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(46342, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 42491:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(42491, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            //Entrega de Shield
            case 43085:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(43085, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 44313:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(44313, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 45587:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(45587, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 32375:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(32375, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 32255:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(32255, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 35094:
            {
                player->DestroyItemCount(80004, 1, true);
                player->AddItem(35094, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por usar sua EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }break;

            case 100000:
            {
                if (action == 1) // Isso nunca deveria acontecer
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("Error");
                }
            }break;
        }
        return true;
    }
};


///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC EtMaXx Start                   ///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_start : public CreatureScript
{
public:
    etmaxx_start() : CreatureScript("etmaxx_start") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();
        
        if (player->getClass() == CLASS_DRUID) {
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/ability_druid_catform:30:30:-18:0|tWOW INCRIVEL, QUERO UPAR DE FERAL !", 100, 0);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_forceofnature:30:30:-18:0|tWOW INCRIVEL, QUERO UPAR DE BALANCE !", 101, 0);
            player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
        }
        else if (player->getClass() == CLASS_SHAMAN) {
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_shaman_lavaburst:30:30:-18:0|tWOW INCRIVEL, QUERO UPAR DE ELEMENTAL !", 200, 0);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/ability_shaman_stormstrike:30:30:-18:0|tWOW INCRIVEL, QUERO UPAR DE ENHANCEMENT !", 201, 0);
            player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
        }
        else {
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_box_02:30:30:-18:0|tWOW INCRIVEL, ME DA LOGO ESSES ITEMS !", 1, 0);
            player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
        }        
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        if (sender == 1) {
            player->AddItem(10050, 4);
            switch (player->getClass()) {
                case CLASS_WARRIOR:
                {
                    player->AddItem(29021, 1);
                    player->AddItem(29023, 1);
                    player->AddItem(29020, 1);
                    player->AddItem(29022, 1);
                    player->AddItem(29019, 1);
                    player->AddItem(51389, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Guerreiro");
                    CloseGossipMenuFor(player);
                }break;

                case CLASS_PALADIN:
                {
                    player->AddItem(29073, 1);
                    player->AddItem(29075, 1);
                    player->AddItem(29071, 1);
                    player->AddItem(29072, 1);
                    player->AddItem(29074, 1);
                    player->AddItem(51389, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Paladino");
                    CloseGossipMenuFor(player);
                }break;

                case CLASS_ROGUE:
                {
                    player->AddItem(29044, 1);
                    player->AddItem(29047, 1);
                    player->AddItem(29045, 1);
                    player->AddItem(29048, 1);
                    player->AddItem(29046, 1);
                    player->AddItem(32471, 1);
                    player->AddItem(32471, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Ladino");
                    CloseGossipMenuFor(player);
                }break;

                case CLASS_PRIEST:
                {
                    player->AddItem(29058, 1);
                    player->AddItem(29060, 1);
                    player->AddItem(29056, 1);
                    player->AddItem(29057, 1);
                    player->AddItem(29059, 1);
                    player->AddItem(50181, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Sacerdote");
                    CloseGossipMenuFor(player);
                }break;

                case CLASS_MAGE:
                {
                    player->AddItem(29076, 1);
                    player->AddItem(29079, 1);
                    player->AddItem(29077, 1);
                    player->AddItem(29080, 1);
                    player->AddItem(29078, 1);
                    player->AddItem(50181, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Mago");
                    CloseGossipMenuFor(player);
                }break;

                case CLASS_WARLOCK:
                {
                    player->AddItem(28963, 1);
                    player->AddItem(28967, 1);
                    player->AddItem(28964, 1);
                    player->AddItem(28968, 1);
                    player->AddItem(28966, 1);
                    player->AddItem(50181, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Bruxo");
                    CloseGossipMenuFor(player);

                }break;

                case CLASS_HUNTER:
                {
                    player->AddItem(29081, 1);
                    player->AddItem(29084, 1);
                    player->AddItem(29082, 1);
                    player->AddItem(29085, 1);
                    player->AddItem(29083, 1);
                    player->AddItem(51395, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Caçador");
                    CloseGossipMenuFor(player);
                }break;
            }
        }
        switch (sender) {

            //Druid Feral
            case 100: {
                player->AddItem(29098, 1);
                player->AddItem(29100, 1);
                player->AddItem(29096, 1);
                player->AddItem(29097, 1);
                player->AddItem(29099, 1);
                player->AddItem(40280, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Druida");
                CloseGossipMenuFor(player);
            }break;

            //Druid Balance
            case 101: {
                player->AddItem(29093, 1);
                player->AddItem(29095, 1);
                player->AddItem(29091, 1);
                player->AddItem(29092, 1);
                player->AddItem(29094, 1);
                player->AddItem(50181, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Druida");
                CloseGossipMenuFor(player);
            }break;

            //Shaman Elemental
            case 200: {
                player->AddItem(29035, 1);
                player->AddItem(29037, 1);
                player->AddItem(29033, 1);
                player->AddItem(29034, 1);
                player->AddItem(29036, 1);
                player->AddItem(40488, 1);
                player->AddItem(51452, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Xamã");
                CloseGossipMenuFor(player);
            }break;

            //Shaman Enhancement
            case 201: {
                player->AddItem(29040, 1);
                player->AddItem(29043, 1);
                player->AddItem(29038, 1);
                player->AddItem(29039, 1);
                player->AddItem(29042, 1);
                player->AddItem(51452, 1);
                player->AddItem(51452, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Xamã");
                CloseGossipMenuFor(player);
            }break;

        }
        

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 Instanciando o NPC                    ///////////////
///////////////////////////////////////////////////////////////////////////////////;

void AddNpcEtmaxxScripts()
{
    new etmaxx_npc();
	new etmaxx_vip();
    new etmaxx_battlepass();
    new etmaxx_transmog_vendor();
    new etmaxx_start();
}
