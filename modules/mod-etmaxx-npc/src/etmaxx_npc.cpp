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
/////////////               NPC Teste Battle Pass                   ///////////////
///////////////////////////////////////////////////////////////////////////////////

class etmaxx_battlepass : public CreatureScript
{
public:
    etmaxx_battlepass() : CreatureScript("etmaxx_battlepass") { }

    uint32 bpvip = 0;
    uint32 points = 0;
    bool queryok = false;
    


    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();
        QueryResult result = CharacterDatabase.PQuery("SELECT bpvip FROM battlepass WHERE guid = %u", player->GetSession()->GetGuidLow());
        if (result) {
            Field* fields = result->Fetch();
            bpvip = fields[0].GetUInt32();
        }




        if (result)
            player->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/inv_axe_61:25:25|tVIP Tank Axe", GOSSIP_SENDER_MAIN, 5000);

        /*if (queryok) {
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "JA TENHO BP VIP", GOSSIP_SENDER_MAIN, 5000);
        }
        else {
            player->ADD_GOSSIP_ITEM(GOSSIP_ACTION_AUCTION, "NAO TENHO BP VIP", GOSSIP_SENDER_MAIN, 3000);
        }*/

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case 3000:
            ChatHandler(player->GetSession()).PSendSysMessage("NAO TENHO BP VIP");
            break;
        case 5000:
            ChatHandler(player->GetSession()).PSendSysMessage("JA TENHO BP VIP");
            break;
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
}
