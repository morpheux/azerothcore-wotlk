#include "loader.h"
#include "ScriptMgr.h"
#include "Configuration/Config.h"
#include "GossipDef.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Language.h"
#include <Chat/Chat.h>
#include <Commands/cs_learn.cpp>

// 25 tabards
uint32 tabardHorda[] =
{
        60044,          //Tabard of Orgrimmar
        60045,          //Tabard of Orgrimmar
        60046,          //Tabard of Orgrimmar
        60047,          //Tabard of Orgrimmar
        60048,          //Tabard of Orgrimmar
        60049,          //Tabard of Thunder Bluff
        60050,          //Tabard of Thunder Bluff
        60051,          //Tabard of Thunder Bluff
        60052,          //Tabard of Thunder Bluff
        60053,          //Tabard of Thunder Bluff
        60054,          //Tabard of Sen'jin
        60055,          //Tabard of Sen'jin
        60056,          //Tabard of Sen'jin
        60057,          //Tabard of Sen'jin
        60058,          //Tabard of Sen'jin
        60059,          //Tabard of Silvermoon
        60060,          //Tabard of Silvermoon
        60061,          //Tabard of Silvermoon
        60062,          //Tabard of Silvermoon
        60063,          //Tabard of Silvermoon
        60064,          //Tabard of Undercity
        60065,          //Tabard of Undercity
        60066,          //Tabard of Undercity
        60067,          //Tabard of Undercity
        60068           //Tabard of Undercity
};

// 24 Tabards
uint32 tabardAlly[] =
{
        60020,          //Tabard of Stormwind
        60021,          //Tabard of Stormwind
        60022,          //Tabard of Stormwind
        60023,          //Tabard of Stormwind
        60024,          //Tabard of Stormwind
        60025,          //Tabard of Darnassus
        60026,          //Tabard of Darnassus
        60027,          //Tabard of Darnassus
        60028,          //Tabard of Darnassus
        60029,          //Tabard of Darnassus
        60030,          //Tabard of Ironforge
        60031,          //Tabard of Ironforge
        60032,          //Tabard of Ironforge
        60033,          //Tabard of Ironforge
        60034,          //Tabard of Ironforge
        60035,          //Tabard of Exodar
        60036,          //Tabard of Exodar
        60037,          //Tabard of Exodar
        60038,          //Tabard of Exodar
        60039,          //Tabard of Exodar
        60040,          //Tabard of Gnomeregan
        60041,          //Tabard of Gnomeregan
        60042,          //Tabard of Gnomeregan
        60043           //Tabard of Gnomeregan
};

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

            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Este NPC irá --> DESTRUIR <-- seu item VIP", GOSSIP_SENDER_MAIN, 5000);

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
    uint32 tier1 = 0;
    uint32 tier2 = 0;
    uint32 tier3 = 0;
    uint32 tier4 = 0;
    uint32 tier5 = 0;
    uint32 tier6 = 0;
    uint32 tier7 = 0;
    uint32 tier8 = 0;
    uint32 tier9 = 0;
    uint32 tier10 = 0;
    uint32 viptier1 = 0;
    uint32 viptier2 = 0;
    uint32 viptier3 = 0;
    uint32 viptier4 = 0;;
    uint32 viptier5 = 0;
    uint32 viptier6 = 0;
    uint32 viptier7 = 0;
    uint32 viptier8 = 0;
    uint32 viptier9 = 0;
    uint32 viptier10 = 0;
    
    bool OnGossipHello(Player* player, Creature* creature)
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT bpvip,points FROM character_battlepass WHERE guid = %u", player->GetSession()->GetGuidLow());
        if (result) {
            Field* fields = result->Fetch();
            bpvip = fields[0].GetUInt32();
            points = fields[1].GetUInt32();
        }

        player->PlayerTalkClass->ClearMenus();

        if (result && bpvip == 0) {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero participar do EtMaXx VIP Battle Pass", 2, 0);

            if (player->HasItemCount(80001, 1, true)) {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Daily Mark", 4, 0);
            }
            if (player->HasItemCount(80002, 1, true)) {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Week Mark", 5, 0);
            }
            if (player->HasItemCount(80003, 1, true)) {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Unique Mark", 6, 0);
            }
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero ver meus Battle Points", 3, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "------------------------", 5000, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Me Mostre o Battle Pass", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Resgate sua Recompensa", 2000, 0);
        }
        else if(result && bpvip == 1) {
            if (player->HasItemCount(80001, 1, true)) {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Daily Mark", 4, 0);
            }
            if (player->HasItemCount(80002, 1, true)) {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Week Mark", 5, 0);
            }
            if (player->HasItemCount(80003, 1, true)) {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Unique Mark", 6, 0);
            }
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero ver meus Battle Points", 3, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "------------------------", 5000, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Me Mostre o Battle Pass", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Resgate sua Recompensa", 2000, 0);
        }
        else {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero Participar do EtMaXx Battle Pass", 1, 0);
        }

        SendGossipMenuFor(player, 800806, creature->GetGUID());
        //player->PlayerTalkClass->SendGossipMenu(800806, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
        case 1: {
            CharacterDatabase.PExecute("INSERT INTO character_battlepass(guid, bpvip, points, tier1, tier2, tier3, tier4, tier5, tier6, tier7, tier8, tier9, tier10, viptier1, viptier2, viptier3, viptier4, viptier5, viptier6, viptier7, viptier8, viptier9, viptier10) VALUES (%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, )", player->GetSession()->GetGuidLow(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            ChatHandler(player->GetSession()).PSendSysMessage("Parabens, agora você está com Battle Pass Ativo. Fale com o NPC novamente");
            CloseGossipMenuFor(player);
        }break;
            
        case 2: {
            if (player->HasItemCount(80000, 1)) {
                player->DestroyItemCount(80000, 1, true);
                CharacterDatabase.PExecute("UPDATE character_battlepass SET bpvip = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por adquirir o EtMaXx VIP Battle Pass");
                CloseGossipMenuFor(player);
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você precisa de um EtMaXx VIP Battle Pass Mark para participar do Battle Pass VIP. Você pode adquirir essa Mark no site: www.etmaxx.com.br");
                CloseGossipMenuFor(player);
            }
        }break;
            
        case 4: {
            if (player->HasItemCount(80001, 1)) {
                player->DestroyItemCount(80001, 1, true);
                points = points + 8;
                CharacterDatabase.PExecute("UPDATE character_battlepass points = %u WHERE guid = %u", points, player->GetSession()->GetGuidLow());
                ChatHandler(player->GetSession()).PSendSysMessage("Battle Points adicionados ao seu Passe");
                CloseGossipMenuFor(player);
            }
        }break;
            

        case 5: {
            if (player->HasItemCount(80002, 1)) {
                player->DestroyItemCount(80002, 1, true);
                points = points + 40;
                CharacterDatabase.PExecute("UPDATE character_battlepass SET points = %u WHERE guid = %u", points, player->GetSession()->GetGuidLow());
                ChatHandler(player->GetSession()).PSendSysMessage("Battle Points adicionados ao seu Passe");
                CloseGossipMenuFor(player);
            }
        }break;
            

        case 6: {
            if (player->HasItemCount(80003, 1)) {
                player->DestroyItemCount(80003, 1, true);
                points = points + 280;
                CharacterDatabase.PExecute("UPDATE character_battlepass SET points = %u WHERE guid = %u", points, player->GetSession()->GetGuidLow());
                ChatHandler(player->GetSession()).PSendSysMessage("Battle Points adicionados ao seu Passe");
                CloseGossipMenuFor(player);
            }
        }break;
           

        case 100: {
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Esta são as recompensas do Battle Pass deste mes:", 100, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Battle Pass Normal:", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t5 000 de Gold - 100 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t10 000 de Gold - 200 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_summonchampion:25:25|t30 Emblem of Triumph - 300 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01|t30 Emblem of Frost - 400 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t10 000 Honor Points - 500 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_03:25:25|tEtMaXx Transmog Mark - 700 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_petcarrier_01:25:25|tWorg Pup (PET) - 900 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_shirt_black_01:25:25|tMega Shirt Reset - 1000 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "------------------", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "Se possuir o Battle Pass VIP além das recompensas normais você receberá:", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t5 000 de Gold - 100 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t20 Emblem of Frost - 200 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t10 000 Honor Points  - 300 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t40 Emblem of Frost - 400 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:25:25|t200 Arena Points - 500 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:25:25|t400 Arena Points - 600 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|tEtMaXx Transmog Mark - 700 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:25:25|t600 Arena Points - 800 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_jewelry_amulet_01:25:25|tEtMaXx Mount Mark - 900 Pontos", 0, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|tVIP Container - 1000 Pontos", 0, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "------------------------", 0, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 5000, 0);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }break;

        case 3: {
            QueryResult result = CharacterDatabase.PQuery("SELECT points FROM character_battlepass WHERE guid = %u", player->GetSession()->GetGuidLow());
            Field* fields = result->Fetch();
            points = fields[0].GetUInt32();
            ChatHandler(player->GetSession()).PSendSysMessage("Você tem um total de %u Battle Points", points);
            CloseGossipMenuFor(player);
        }break;

        case 5000:  // Main menu
        {
            OnGossipHello(player, creature);
        } break;

        case 2000:  // Resgate de Recompensas
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT bpvip, points, tier1, tier2, tier3, tier4, tier5, tier6, tier7, tier8, tier9, tier10, viptier1, viptier2, viptier3, viptier4, viptier5, viptier6, viptier7, viptier8, viptier9, viptier10 FROM character_battlepass WHERE guid = %u", player->GetSession()->GetGuidLow());
            Field* fields = result->Fetch();
            bpvip = fields[0].GetUInt32();
            points = fields[1].GetUInt32();
            tier1 = fields[2].GetUInt32();
            tier2 = fields[3].GetUInt32();
            tier3 = fields[4].GetUInt32();
            tier4 = fields[5].GetUInt32();
            tier5 = fields[6].GetUInt32();
            tier6 = fields[7].GetUInt32();
            tier7 = fields[8].GetUInt32();
            tier8 = fields[9].GetUInt32();
            tier9 = fields[10].GetUInt32();
            tier10 = fields[11].GetUInt32();
            viptier1 = fields[12].GetUInt32();
            viptier2 = fields[13].GetUInt32();
            viptier3 = fields[14].GetUInt32();
            viptier4 = fields[15].GetUInt32();
            viptier5 = fields[16].GetUInt32();
            viptier6 = fields[17].GetUInt32();
            viptier7 = fields[18].GetUInt32();
            viptier8 = fields[19].GetUInt32();
            viptier9 = fields[20].GetUInt32();
            viptier10 = fields[21].GetUInt32();
            if (bpvip == 1) {
                if (points < 100) {
                    ChatHandler(player->GetSession()).PSendSysMessage("Você precisa de no minimo 100 Battle Points para resgater uma recompensa.");
                    CloseGossipMenuFor(player);
                }
                if (points >= 100 && viptier1 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t5 000 de Gold - 100 Pontos", 2100, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t5 000 de Gold - 100 Pontos", 3100, 0);
                }
                if (points >= 200 && viptier2 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t10 000 de Gold - 200 Pontos", 2200, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t20 Emblem of Frost - 200 Pontos", 3200, 0);
                }
                if (points >= 300 && viptier3 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_summonchampion:25:25|t30 Emblem of Triumph - 300 Pontos", 2300, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t10 000 Honor Points  - 300 Pontos", 3300, 0);
                }
                if (points >= 400 && viptier4 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t40 Emblem of Frost - 400 Pontos", 2400, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t40 Emblem of Frost - 400 Pontos", 3400, 0);
                }
                if (points >= 500 && viptier5 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t10 000 Honor Points - 500 Pontos", 2500, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:25:25|t200 Arena Points - 500 Pontos", 3500, 0);
                }
                if (points >= 600 && viptier6 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:25:25|t400 Arena Points - 500 Pontos", 3600, 0);
                }
                if (points >= 700 && viptier7 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|tEtMaXx Transmog Mark - 700 Pontos", 2700, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|tEtMaXx Transmog Mark - 700 Pontos", 3700, 0);
                }
                if (points >= 800 && viptier8 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:25:25|t600 Arena Points - 800 Pontos", 3800, 0);
                }
                if (points >= 900 && viptier9 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_petcarrier_01:25:25|tWorg Pup (PET) - 900 Pontos", 2900, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_jewelry_amulet_01:25:25|tEtMaXx Mount Mark - 900 Pontos", 3900, 0);
                }
                if (points >= 1000 && viptier10 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_shirt_black_01:25:25|tMega Shirt Reset - 1000 Pontos", 21000, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|tVIP Container - 1000 Pontos", 31000, 0);
                }
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

            }

            if (bpvip == 0) {
                if (points < 100) {
                    ChatHandler(player->GetSession()).PSendSysMessage("Você precisa de no minimo 100 Battle Points para resgater uma recompensa.");
                    CloseGossipMenuFor(player);
                }
                if (points >= 100 && tier1 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t5 000 de Gold - 100 Pontos", 2100, 0);
                }
                if (points >= 200 && tier2 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t10 000 de Gold - 200 Pontos", 2200, 0);
                }
                if (points >= 300 && tier3 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_summonchampion:25:25|t30 Emblem of Triumph - 300 Pontos", 2300, 0);
                }
                if (points >= 400 && tier4 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t40 Emblem of Frost - 400 Pontos", 2400, 0);
                }
                if (points >= 500 && tier5 == 0 ){
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t10 000 Honor Points - 500 Pontos", 2500, 0);
                }
                if (points >= 700 && tier7 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_03:25:25|tEtMaXx Transmog Mark - 700 Pontos", 2700, 0);
                }
                if (points >= 900 && tier9 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_petcarrier_01:25:25|tWorg Pup (PET) - 900 Pontos", 2900, 0);
                }
                if (points >= 1000 && tier10 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_shirt_black_01:25:25|tMega Shirt Reset - 1000 Pontos", 21000, 0);
                }
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
            
        } break;

        case 2100: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier1 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyMoney(50000000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 1 Resgatada (5000 de Gold)");
            CloseGossipMenuFor(player);
        } break;

        case 2200: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier2 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyMoney(100000000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 2 Resgatada (10000 de Gold)");
            CloseGossipMenuFor(player);
        } break;

        case 2300: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier3 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(47241, 30);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 3 Resgatada (30 Emblem of Triumph)");
            CloseGossipMenuFor(player);
        } break;

        case 2400: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier4 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(49426, 40);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 4 Resgatada (40 Emblem of Frost)");
            CloseGossipMenuFor(player);
        } break;

        case 2500: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier5 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyHonorPoints(10000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 5 Resgatada (10 000 Honor Points)");
            CloseGossipMenuFor(player);
        } break;   

        case 2700: {
            if (player->HasItemCount(80004, 1, true)) {
                ChatHandler(player->GetSession()).PSendSysMessage("Você já tem uma EtMaXx Transmog Mark, gaste a sua para pegar outra");
                CloseGossipMenuFor(player);
            }
            else {
                CharacterDatabase.PExecute("UPDATE character_battlepass SET tier7 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
                player->AddItem(80004, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 7 Resgatada (EtMaXx Transmog Mark)");
                CloseGossipMenuFor(player);
            }
            
        } break;

        case 2900: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier9 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(12264, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 9 Resgatada (Worg Pup (PET))");
            CloseGossipMenuFor(player);
        } break;

        case 21000: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier10 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(60000, 2000);
            player->AddItem(60004, 15);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 10 Resgatada (Mega Shirt Reset)");
            CloseGossipMenuFor(player);
        } break;
            
        }
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

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_bone_humanskull_01:30:30:-18:0|t1000 Enemy Head + 50.000 Honor", 10, 0,"Tem certeza ?",0,false);

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_frostemblem_01:30:30:-18:0|t200 Emblems of Frost", 20, 0);

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:30:30:-18:0|t1300 de Arena Rating + 200 Arena Points", 30, 0, "Tem certeza ?", 0, false);

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_sword_26:30:30:-18:0|tEscolha seu Transmog de Arma", 50, 0);
              
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
                player->GetSession()->SendListInventory(creature->GetGUID(), 90500);
            } break;

            //Machados 1Hand
            case 2000:
            {              
                player->GetSession()->SendListInventory(creature->GetGUID(), 90501);
            } break;

            //Adagas
            case 3000:
            {               
                player->GetSession()->SendListInventory(creature->GetGUID(), 90502);
            } break;

            //Armas de Punho
            case 4000:
            {               
                player->GetSession()->SendListInventory(creature->GetGUID(), 90503);
            } break;

            //Maças 1Hand
            case 5000:
            {               
                player->GetSession()->SendListInventory(creature->GetGUID(), 90504);
            } break;

            //Maças 2Hand
            case 6000:
            {               
                player->GetSession()->SendListInventory(creature->GetGUID(), 90505);
            } break;

            //Espada 2Hand
            case 8000:
            {               
                player->GetSession()->SendListInventory(creature->GetGUID(), 90506);
            } break;

            //Espada 1Hand
            case 7000:
            {               
                player->GetSession()->SendListInventory(creature->GetGUID(), 90507);
            } break;

            //polearm
            case 9000:
            {               
                player->GetSession()->SendListInventory(creature->GetGUID(), 90508);
            } break;

            //Staff
            case 10000:
            {               
                player->GetSession()->SendListInventory(creature->GetGUID(), 90509);
            } break;

            //Bow
            case 11000:
            {               
                player->GetSession()->SendListInventory(creature->GetGUID(), 90510);
            } break;

            //Shield
            case 12000:
            {              
                player->GetSession()->SendListInventory(creature->GetGUID(), 90511);
            } break;            

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
/////////////                 NPC EtMaXx Start                      ///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_start : public CreatureScript
{
public:
    etmaxx_start() : CreatureScript("etmaxx_start") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();

        if (!player->HasItemCount(37836, 1, true) && player->getLevel() <= 10) {

        
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
        }
        else {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Não posso mais lhe ajudar aventureiro, siga seu caminho...", 1000, 0);
            player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        if (sender == 1) {
            switch (player->getClass()) {
                case CLASS_WARRIOR:
                {
                    player->EquipNewItem(19, 10050, true);
                    player->EquipNewItem(20, 10050, true);
                    player->EquipNewItem(21, 10050, true);
                    player->EquipNewItem(22, 10050, true);
                    player->AddItem(29021, 1);
                    player->AddItem(29023, 1);
                    player->AddItem(29020, 1);
                    player->AddItem(29022, 1);
                    player->AddItem(29019, 1);
                    player->AddItem(51389, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Guerreiro");
                    CloseGossipMenuFor(player);
                }break;

                case CLASS_PALADIN:
                {
                    player->EquipNewItem(19, 10050, true);
                    player->EquipNewItem(20, 10050, true);
                    player->EquipNewItem(21, 10050, true);
                    player->EquipNewItem(22, 10050, true);
                    player->AddItem(29073, 1);
                    player->AddItem(29075, 1);
                    player->AddItem(29071, 1);
                    player->AddItem(29072, 1);
                    player->AddItem(29074, 1);
                    player->AddItem(19854, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Paladino");
                    CloseGossipMenuFor(player);
                }break;

                case CLASS_ROGUE:
                {
                    player->EquipNewItem(19, 10050, true);
                    player->EquipNewItem(20, 10050, true);
                    player->EquipNewItem(21, 10050, true);
                    player->EquipNewItem(22, 10050, true);
                    player->AddItem(29044, 1);
                    player->AddItem(29047, 1);
                    player->AddItem(29045, 1);
                    player->AddItem(29048, 1);
                    player->AddItem(29046, 1);
                    player->AddItem(32471, 1);
                    player->AddItem(32471, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Ladino");
                    CloseGossipMenuFor(player);
                }break;

                case CLASS_PRIEST:
                {
                    player->EquipNewItem(19, 10050, true);
                    player->EquipNewItem(20, 10050, true);
                    player->EquipNewItem(21, 10050, true);
                    player->EquipNewItem(22, 10050, true);
                    player->AddItem(29058, 1);
                    player->AddItem(29060, 1);
                    player->AddItem(29056, 1);
                    player->AddItem(29057, 1);
                    player->AddItem(29059, 1);
                    player->AddItem(50181, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Sacerdote");
                    CloseGossipMenuFor(player);
                }break;

                case CLASS_MAGE:
                {
                    player->EquipNewItem(19, 10050, true);
                    player->EquipNewItem(20, 10050, true);
                    player->EquipNewItem(21, 10050, true);
                    player->EquipNewItem(22, 10050, true);
                    player->AddItem(29076, 1);
                    player->AddItem(29079, 1);
                    player->AddItem(29077, 1);
                    player->AddItem(29080, 1);
                    player->AddItem(29078, 1);
                    player->AddItem(50181, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Mago");
                    CloseGossipMenuFor(player);
                }break;

                case CLASS_WARLOCK:
                {
                    player->EquipNewItem(19, 10050, true);
                    player->EquipNewItem(20, 10050, true);
                    player->EquipNewItem(21, 10050, true);
                    player->EquipNewItem(22, 10050, true);
                    player->AddItem(28963, 1);
                    player->AddItem(28967, 1);
                    player->AddItem(28964, 1);
                    player->AddItem(28968, 1);
                    player->AddItem(28966, 1);
                    player->AddItem(50181, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Bruxo");
                    CloseGossipMenuFor(player);

                }break;

                case CLASS_HUNTER:
                {
                    player->EquipNewItem(19, 10050, true);
                    player->EquipNewItem(20, 10050, true);
                    player->EquipNewItem(21, 10050, true);
                    player->EquipNewItem(22, 10050, true);
                    player->AddItem(29081, 1);
                    player->AddItem(29084, 1);
                    player->AddItem(29082, 1);
                    player->AddItem(29085, 1);
                    player->AddItem(29083, 1);
                    player->AddItem(51395, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Caçador");
                    CloseGossipMenuFor(player);
                }break;

                case CLASS_DEATH_KNIGHT:
                {
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Você já está bem avançado em sua jornada, não precisa da minha ajuda. Receba apenas minha benção");
                    CloseGossipMenuFor(player);
                }break;
            }
        }
        switch (sender) {

            //Druid Feral
            case 100: {
                player->EquipNewItem(19, 10050, true);
                player->EquipNewItem(20, 10050, true);
                player->EquipNewItem(21, 10050, true);
                player->EquipNewItem(22, 10050, true);
                player->AddAura(30567, player);
                player->AddAura(30557, player);
                player->AddAura(30562, player);
                player->AddItem(29098, 1);
                player->AddItem(29100, 1);
                player->AddItem(29096, 1);
                player->AddItem(29097, 1);
                player->AddItem(29099, 1);
                player->AddItem(40280, 1);
                player->AddItem(37836, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Druida");
                CloseGossipMenuFor(player);
            }break;

            //Druid Balance
            case 101: {
                player->EquipNewItem(19, 10050, true);
                player->EquipNewItem(20, 10050, true);
                player->EquipNewItem(21, 10050, true);
                player->EquipNewItem(22, 10050, true);
                player->AddAura(30567, player);
                player->AddAura(30557, player);
                player->AddAura(30562, player);
                player->AddItem(29093, 1);
                player->AddItem(29095, 1);
                player->AddItem(29091, 1);
                player->AddItem(29092, 1);
                player->AddItem(29094, 1);
                player->AddItem(50181, 1);
                player->AddItem(37836, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Druida");
                CloseGossipMenuFor(player);
            }break;

            //Shaman Elemental
            case 200: {
                player->EquipNewItem(19, 10050, true);
                player->EquipNewItem(20, 10050, true);
                player->EquipNewItem(21, 10050, true);
                player->EquipNewItem(22, 10050, true);
                player->AddAura(30567, player);
                player->AddAura(30557, player);
                player->AddAura(30562, player);
                player->AddItem(29035, 1);
                player->AddItem(29037, 1);
                player->AddItem(29033, 1);
                player->AddItem(29034, 1);
                player->AddItem(29036, 1);
                player->AddItem(40488, 1);
                player->AddItem(51452, 1);
                player->AddItem(37836, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Xamã");
                CloseGossipMenuFor(player);
            }break;

            //Shaman Enhancement
            case 201: {
                player->EquipNewItem(19, 10050, true);
                player->EquipNewItem(20, 10050, true);
                player->EquipNewItem(21, 10050, true);
                player->EquipNewItem(22, 10050, true);
                player->AddAura(30567, player);
                player->AddAura(30557, player);
                player->AddAura(30562, player);
                player->AddItem(29040, 1);
                player->AddItem(29043, 1);
                player->AddItem(29038, 1);
                player->AddItem(29039, 1);
                player->AddItem(29042, 1);
                player->AddItem(50760, 1);
                player->AddItem(50760, 1);
                player->AddItem(37836, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Xamã");
                CloseGossipMenuFor(player);
            }break;

            case 1000: {
                ChatHandler(player->GetSession()).PSendSysMessage("Só é possivel usar o EtMaXx Start uma unica vez");
                CloseGossipMenuFor(player);
            }break;
        }
        

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC de Troca de Tabard                ///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_tabard : public CreatureScript
{
public:
    etmaxx_tabard() : CreatureScript("etmaxx_tabard") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {

        ClearGossipMenuFor(player);
        bool acheitabardfaccaooposta = false;

        // Se o player for alliance, verificar se ele tem tabard horda na bag
        if (player->GetTeamId() == TEAM_ALLIANCE) {
            for (uint8 i = 0; i < 25; ++i) {
                if (player->HasItemCount(tabardHorda[i], 1, true))
                acheitabardfaccaooposta = true;
            }

        };

        // Se o player for horda, verificar se ele tem tabard alliancce na bag
        if (player->GetTeamId() == TEAM_HORDE) {
            for (uint8 i = 0; i < 24; ++i) {
                if (player->HasItemCount(tabardAlly[i], 1, true))
                acheitabardfaccaooposta = true;
            }

        };

        if (acheitabardfaccaooposta)
        {
            // Construir gossips baseados nas racas

            // 72415 = Tank
            // 72417 = DPS Spell
            // 72413 = DPS Meele / Ranged
            // 72419 = Healer
                if (player->getRace() == RACE_BLOODELF) {
                    if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_DEATH_KNIGHT)
                    {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60059, 0);
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60061, 0);

                    }

                    if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60060, 0);

                    }

                    if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_HUNTER) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60062, 0);

                    }


                    if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60063, 0);

                    }


                }
                else if (player->getRace() == RACE_ORC) {
                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60044, 0);

                    }


                    if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_WARLOCK) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60045, 0);

                    }


                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60046, 0);

                    }


                    if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_SHAMAN) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60047, 0);

                    }


                    if (player->getClass() == CLASS_SHAMAN) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60048, 0);

                    }


                }
                else if (player->getRace() == RACE_TROLL) {
                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60054, 0);

                    }


                    if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_MAGE) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60055, 0);

                    }


                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60056, 0);

                    }


                    if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_SHAMAN) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60057, 0);

                    }


                    if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_PRIEST) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60058, 0);

                    }

                }
                else if (player->getRace() == RACE_UNDEAD_PLAYER) {
                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60064, 0);

                    }


                    if (player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60065, 0);

                    }


                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60066, 0);

                    }


                    if (player->getClass() == CLASS_ROGUE) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60067, 0);

                    }


                    if (player->getClass() == CLASS_PRIEST) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60068, 0);

                    }


                }
                else if (player->getRace() == RACE_TAUREN) {
                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_DRUID) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60049, 0);

                    }


                    if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_DRUID) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60050, 0);

                    }


                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60051, 0);

                    }


                    if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_DRUID || player->getClass() == CLASS_HUNTER) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60052, 0);

                    }


                    if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_DRUID) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60053, 0);

                    }
                }

                if (player->getRace() == RACE_HUMAN) {
                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_PALADIN)
                    {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60020, 0);
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60022, 0);

                    }

                    if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60021, 0);

                    }


                    if (player->getClass() == CLASS_ROGUE) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60023, 0);

                    }


                    if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60024, 0);

                    }


                }
                else if (player->getRace() == RACE_DWARF) {
                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_PALADIN)
                    {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60030, 0);
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60032, 0);

                    }

                    if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST)
                    {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60031, 0);
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60034, 0);

                    }

                    if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_HUNTER) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60033, 0);

                    }




                }
                else if (player->getRace() == RACE_GNOME) {
                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT)
                    {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60040, 0);
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60042, 0);

                    }

                    if (player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60041, 0);

                    }


                    if (player->getClass() == CLASS_ROGUE) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60043, 0);

                    }

                }
                else if (player->getRace() == RACE_DRAENEI) {
                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_PALADIN)
                    {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60035, 0);
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60037, 0);

                    }

                    if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_SHAMAN) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60036, 0);

                    }



                    if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_HUNTER) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60038, 0);

                    }


                    if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_SHAMAN) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60039, 0);

                    }


                }
                else if (player->getRace() == RACE_NIGHTELF) {
                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_DRUID) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60025, 0);

                    }


                    if (player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_DRUID)
                    {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60026, 0);
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60029, 0);

                    }

                    if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60027, 0);

                    }


                    if (player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_DRUID) {
                        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60028, 0);

                    }

                }           
        }
        SendGossipMenuFor(player, 800804, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
        case 60044:          //Tabard of Orgrimmar
        case 60045:          //Tabard of Orgrimmar
        case 60046:          //Tabard of Orgrimmar
        case 60047:          //Tabard of Orgrimmar
        case 60048:          //Tabard of Orgrimmar
        case 60049:          //Tabard of Thunder Bluff
        case 60050:          //Tabard of Thunder Bluff
        case 60051:          //Tabard of Thunder Bluff
        case 60052:          //Tabard of Thunder Bluff
        case 60053:          //Tabard of Thunder Bluff
        case 60054:          //Tabard of Sen'jin
        case 60055:          //Tabard of Sen'jin
        case 60056:          //Tabard of Sen'jin
        case 60057:          //Tabard of Sen'jin
        case 60058:          //Tabard of Sen'jin
        case 60059:          //Tabard of Silvermoon
        case 60060:          //Tabard of Silvermoon
        case 60061:          //Tabard of Silvermoon
        case 60062:          //Tabard of Silvermoon
        case 60063:          //Tabard of Silvermoon
        case 60064:          //Tabard of Undercity
        case 60065:          //Tabard of Undercity
        case 60066:          //Tabard of Undercity
        case 60067:          //Tabard of Undercity
        case 60068:          //Tabard of Undercity
        case 60020:          //Tabard of Stormwind
        case 60021:          //Tabard of Stormwind
        case 60022:          //Tabard of Stormwind
        case 60023:          //Tabard of Stormwind
        case 60024:          //Tabard of Stormwind
        case 60025:          //Tabard of Darnassus
        case 60026:          //Tabard of Darnassus
        case 60027:          //Tabard of Darnassus
        case 60028:          //Tabard of Darnassus
        case 60029:          //Tabard of Darnassus
        case 60030:          //Tabard of Ironforge
        case 60031:          //Tabard of Ironforge
        case 60032:          //Tabard of Ironforge
        case 60033:          //Tabard of Ironforge
        case 60034:          //Tabard of Ironforge
        case 60035:          //Tabard of Exodar
        case 60036:          //Tabard of Exodar
        case 60037:          //Tabard of Exodar
        case 60038:          //Tabard of Exodar
        case 60039:          //Tabard of Exodar
        case 60040:          //Tabard of Gnomeregan
        case 60041:          //Tabard of Gnomeregan
        case 60042:          //Tabard of Gnomeregan
        case 60043:          //Tabard of Gnomeregan
            if (destroyTabard(player))
            {
                addTabard(sender, player);
                CloseGossipMenuFor(player);
            }
            break;
        }
        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }



    void addTabard(uint32 itemid, Player* player)
    {
        player->AddItem(itemid, 1);
    }

    bool destroyTabard(Player* player)
    {
        // Se o player for alliance, verificar se ele tem tabard horda na bag
        if (player->GetTeamId() == TEAM_ALLIANCE) {
            for (uint8 i = 0; i < 25; ++i) {
                if (player->HasItemCount(tabardHorda[i], 1, true))
                {
                    player->DestroyItemCount(tabardHorda[i], 1, true);
                    return true;
                }

            }

        };

        // Se o player for hprda, verificar se ele tem tabard alliancce na bag
        if (player->GetTeamId() == TEAM_HORDE) {
            for (uint8 i = 0; i < 24; ++i) {
                if (player->HasItemCount(tabardAlly[i], 1, true))
                {
                    player->DestroyItemCount(tabardAlly[i], 1, true);
                    return true;
                }
            }

        };

        return false;
    }

};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 EtMaXx Event Trocadorious             ///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_event : public CreatureScript
{
public:
    etmaxx_event() : CreatureScript("etmaxx_event") { }

    //secondary prof = 129, 185, 356

    int skillid[11] = {164, 755, 197, 333, 171, 773, 202, 165, 186, 182, 393};
    int craft = 0;

    bool MarkCheck(Player* player, int count) {
        if (player->HasItemCount(600600, count, true)) {
            player->DestroyItemCount(600600, count, true);
            return true;
        }
        else {
            ChatHandler(player->GetSession()).PSendSysMessage("Você não tem EtMaXx Event Mark suficientes.");
            return false;
        }
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/Spellschoolicon7:35:35:-30:0|tResgate sua Recompensa", 100, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:35:35:-30:0|tUpdate menu", 9999, 0);

        SendGossipMenuFor(player, 800805, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {

        case 9999:  // Main menu
        {
            OnGossipHello(player, creature);
        }break;

        case 100: {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_book_11:25:25:-20:0|tProfissão Full - 3 Event Mark", 1000, 0);                           // 03 Event Mark                                        // 03 Event Mark
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t10 000 Honor Points - 2 Event Mark", 2000, 0);              // 02 Event Mark
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:25:25|t200 Arena Points - 2 Event Mark", 3000, 0); // 02 Event Mark
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t20 Emblem of Frost - 2 Event Mark", 4000, 0);                // 02 Event Mark
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_championsgrace:25:25|tEtMaXx Transmog Mark - 4 Event Mark", 5000, 0);            // 04 Event Mark
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_shirt_guildtabard_01:25:25|tEtMaXx Tabard Mark - 5 Event Mark", 6000, 0);               // 05 Event Mark 
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_jewelry_amulet_01:25:25|tEtMaXx Mount Mark - 7 Event Mark", 7000, 0);                   // 07 Event Mark
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_gem_pearl_04:25:25|tEtMaXx Sanctified Mark - 8 Event Mark", 8000, 0);              // 08 Event Mark 
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_rune_09:25:25|tMEGA ARMA VIP - 999 Event Mark", 9000, 0);                          // 999
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "----------------------------------------", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Comprar Tabard", 1, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Comprar Sanctified Token Normal", 2, 0);                                                                                                                                                                      
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }break;

        case 1: {
            if (player->GetTeamId() == TEAM_HORDE) {
                player->GetSession()->SendListInventory(creature->GetGUID(), 91500);
            }
            else {
                player->GetSession()->SendListInventory(creature->GetGUID(), 92500);
            }
        }break;

        case 2: {
            player->GetSession()->SendListInventory(creature->GetGUID(), 93500);
        }break;
            
        case 1000: {

            craft = 0;
            for (int i = 0; i <= 10; i++) {
                if (player->HasSkill(skillid[i])) {
                    craft = craft + 1;
                }
            }
            if (craft >= 2) {
                ChatHandler(player->GetSession()).PSendSysMessage("Você só pode ter 2 Profissões, escolha outra recompensa");
                CloseGossipMenuFor(player);
            }
            else {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_blacksmithing:25:25|tBlacksmithing", 10000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_gem_02:25:25|tJewelcrafting", 20000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_tailoring:25:25|tTailoring", 30000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_engraving:25:25|tEncanting", 40000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_alchemy:25:25|tAlchemy", 50000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_inscription_tradeskill01:25:25|tInscription", 60000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_engineering:25:25|tEngineering", 70000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_armorkit_17:25:25|tLeatherworking", 80000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_mining:25:25|tMining", 90000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_pelt_wolf_01:25:25|tSkinning", 100000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_herbalism:25:25|tHerbalism", 110000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 9999, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
            
        }break;

        case 2000: {
            if (MarkCheck(player, 2)) {
                player->ModifyHonorPoints(10000);
                ChatHandler(player->GetSession()).PSendSysMessage("10.000 pontos de honra recebidos");
            }
        }break;

        case 3000: {
            if (MarkCheck(player,2)) {
                player->ModifyArenaPoints(200);
                ChatHandler(player->GetSession()).PSendSysMessage("200 pontos de Arena recebidos");
            }
        }break;

        case 4000: {
            if (MarkCheck(player, 2)) {
                player->AddItem(49426, 20);
                ChatHandler(player->GetSession()).PSendSysMessage("20 Emblem of Frost recebidos");
            }
        }break;

        case 5000: {
            if (MarkCheck(player, 4)) {
                player->AddItem(80004, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Transmog Mark");
            }
        }break;

        case 6000: {
            if (MarkCheck(player, 5)) {
                player->AddItem(80005, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Tabard Mark recebida");               
            }
        }break;

        case 7000: {
            if (MarkCheck(player, 7)) {
                player->AddItem(47395, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Mount Mark recebida");
            }
        }break;

        case 8000: {
            if (MarkCheck(player, 8)) {
                player->AddItem(80006, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Sanctified Mark recebida");
            }
        }break;

        case 9000: {
            if (MarkCheck(player, 999)) {
                player->AddItem(60002, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("MEGA ARMA VIP RECEBIDA !");
            }
        }break;

        //BS
        case 10000:
        {
            if (MarkCheck(player,3)) {
                learn_commandscript::HandleLearnSkillRecipesHelper(player, 164);
                player->SetSkill(164, player->GetSkillStep(164), 450, 450);
            }
        }break;

        //Jewel
        case 20000:
        {
            if (MarkCheck(player,3)) {
                learn_commandscript::HandleLearnSkillRecipesHelper(player, 755);
                player->SetSkill(755, player->GetSkillStep(755), 450, 450);
            }
        }break;

        //Tailor
        case 30000:
        {
            if (MarkCheck(player,3)) {
                learn_commandscript::HandleLearnSkillRecipesHelper(player, 197);
                player->SetSkill(197, player->GetSkillStep(197), 450, 450);
            }
        }break;

        //Enchanting
        case 40000:
        {
            if (MarkCheck(player,3)) {
                learn_commandscript::HandleLearnSkillRecipesHelper(player, 333);
                player->SetSkill(333, player->GetSkillStep(333), 450, 450);
            }
        }break;

        //Alchemy
        case 50000:
        {
            if (MarkCheck(player,3)) {
                learn_commandscript::HandleLearnSkillRecipesHelper(player, 171);
                player->SetSkill(171, player->GetSkillStep(171), 450, 450);
            }
        }break;

        //Inscription
        case 60000:
        {
            if (MarkCheck(player,3)) {
                learn_commandscript::HandleLearnSkillRecipesHelper(player, 773);
                player->SetSkill(773, player->GetSkillStep(773), 450, 450);
            }
        }break;

        //Engineering
        case 70000:
        {
            if (MarkCheck(player,3)) {
                learn_commandscript::HandleLearnSkillRecipesHelper(player, 202);
                player->SetSkill(202, player->GetSkillStep(202), 450, 450);
            }
        }break;

        //leatherworking
        case 80000:
        {
            if (MarkCheck(player,3)) {
                learn_commandscript::HandleLearnSkillRecipesHelper(player, 165);
                player->SetSkill(165, player->GetSkillStep(165), 450, 450);
            }
        }break;

        //Mining
        case 90000:
        {
            if (MarkCheck(player, 3)) {
                learn_commandscript::HandleLearnSkillRecipesHelper(player, 186);
                player->SetSkill(186, player->GetSkillStep(186), 450, 450);
            }
        }break;

        //Skinning
        case 100000:
        {
            if (MarkCheck(player, 3)) {
                learn_commandscript::HandleLearnSkillRecipesHelper(player, 393);
                player->SetSkill(393, player->GetSkillStep(393), 450, 450);
            }
        }break;

        //Herbalism
        case 110000:
        {
            if (MarkCheck(player, 3)) {
                learn_commandscript::HandleLearnSkillRecipesHelper(player, 182);
                player->SetSkill(182, player->GetSkillStep(182), 450, 450);
            }
        }break;

        }

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
	new etmaxx_tabard();
    new etmaxx_event();
}
