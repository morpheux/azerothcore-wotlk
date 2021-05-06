#include "loader.h"
#include "ScriptMgr.h"
#include "Configuration/Config.h"
#include "GossipDef.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Language.h"
#include <Chat/Chat.h>
#include <Commands/cs_learn.cpp>
#include "ScriptedCreature.h"
#include "ObjectMgr.h"
#include "UnitAI.h"
#include "GameObjectAI.h"
#include "Map.h"
#include "Group.h"
#include "InstanceScript.h"

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
        ClearGossipMenuFor(player);

        if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 37500)
        {
            if (player->GetTeamId(true) == TEAM_ALLIANCE && !player->HasSpell(16056))
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/Ability_mount_whitetiger:35:35:-25:0|tResgate seu Reins of the Ancient Frostsaber", 3, 0);

            if (player->GetTeamId(true) == TEAM_HORDE && !player->HasSpell(16081))
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/Ability_mount_whitedirewolf:35:35:-25:0|tResgate seu Horn of the Arctic Wolf", 3, 0);
        }

        if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 50000 && !player->HasSpell(43688)) {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/Ability_druid_challangingroar:35:35:-25:0|tResgate seu Amani War Bear", 2, 0);
        }

        if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 62500 && !player->HasSpell(75614)) {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/Ability_mount_celestialhorse:35:35:-25:0|tResgate Seu Celestial Steed",1,0);
        }

        if (player->HasItemCount(60018, 15)) {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_jewelry_necklace_27:35:35:-25:0|tResgate Sua Mount Mark", 5, 0);
        }

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bag_10:35:35:-25:0|tQuero dar uma olhada", 4, 0);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "------------------------------------------", 999, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-18:0|tUpdate menu", 999, 0);
        //AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-18:0|tToca Musica", 9999, 0);

        SendGossipMenuFor(player, 800807, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
        case 999: {
            OnGossipHello(player, creature);
        }break;

        /*case 9999: {
            player->SetPhaseMask(2, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("Mudando de Fase");
            CloseGossipMenuFor(player);
        }break;*/

        case 1: {
            player->DestroyItemCount(54811, 1, true);
            player->AddItem(54811, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Team: Item Adicionado em sua Bag. Parabéns!");
            CloseGossipMenuFor(player);
        }break;
            
        case 2: {
            player->DestroyItemCount(33809, 1, true);
            player->AddItem(33809, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Team: Item Adicionado em sua Bag. Parabéns!");
            CloseGossipMenuFor(player);
        }break;
            
        case 3:
		{
            if (player->GetTeamId(true) == TEAM_ALLIANCE)
			{
                player->DestroyItemCount(12302, 1, true);
                player->AddItem(12302, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Team: Item Adicionado em sua Bag. Parabéns!");
                CloseGossipMenuFor(player);
			}
				
			if (player->GetTeamId(true) == TEAM_HORDE)
			{
                player->DestroyItemCount(12351, 1, true);
                player->AddItem(12351, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Team: Item Adicionado em sua Bag. Parabéns!");
                CloseGossipMenuFor(player);
			}
        }break;

        case 4: {
            player->GetSession()->SendListInventory(creature->GetGUID(), 65000);
        }break;

        case 5: {
            player->DestroyItemCount(60018, 15, true);
            player->AddItem(47395, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("Parabéns, você é um vitorioso!");
            CloseGossipMenuFor(player);
        }break;

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
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero participar do EtMaXx VIP Battle Pass", 2, 0,"Tem certeza ?",0,false);

            if (player->HasItemCount(80001, 1, true)) {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Daily Mark", 4, 0, "Tem certeza ?", 0, false);
            }
            if (player->HasItemCount(80002, 1, true)) {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Week Mark", 5, 0, "Tem certeza ?", 0, false);
            }
            if (player->HasItemCount(80003, 1, true)) {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Unique Mark", 6, 0, "Tem certeza ?", 0, false);
            }
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero ver meus Battle Points", 3, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "------------------------", 5000, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Me Mostre o Battle Pass", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Resgate sua Recompensa", 2000, 0);
        }
        else if(result && bpvip == 1) {
            if (player->HasItemCount(80001, 1, true)) {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Daily Mark", 4, 0, "Tem certeza ?", 0, false);
            }
            if (player->HasItemCount(80002, 1, true)) {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Week Mark", 5, 0, "Tem certeza ?", 0, false);
            }
            if (player->HasItemCount(80003, 1, true)) {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero entregar um EtMaXx BP Unique Mark", 6, 0, "Tem certeza ?", 0, false);
            }
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero ver meus Battle Points", 3, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "------------------------", 5000, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Me Mostre o Battle Pass", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Resgate sua Recompensa", 2000, 0);
        }
        else {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Quero Participar do EtMaXx Battle Pass", 1, 0);
        }

        SendGossipMenuFor(player, 800808, creature->GetGUID());
        //player->PlayerTalkClass->SendGossipMenu(800806, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
        case 1: {
            CharacterDatabase.PExecute("INSERT INTO character_battlepass(guid, bpvip, points, tier1, tier2, tier3, tier4, tier5, tier6, tier7, tier8, tier9, tier10, viptier1, viptier2, viptier3, viptier4, viptier5, viptier6, viptier7, viptier8, viptier9, viptier10) VALUES (%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u)", player->GetSession()->GetGuidLow(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
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
                CharacterDatabase.PExecute("UPDATE character_battlepass SET points = %u WHERE guid = %u", points, player->GetSession()->GetGuidLow());
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
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Esta são as recompensas do Battle Pass deste mes:", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Battle Pass Normal:", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t15 000 de Gold - 100 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_rune_08:25:25|t2000 EtMaXx Mark - 200 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_jewelry_talisman_08:25:25|t15 EtMaXx Mega Mark - 300 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t60 Emblem of Frost - 400 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t80 000 Honor Points - 500 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_championsgrace:25:25|t3 EtMaXx Transmog Mark - 700 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_04:25:25|t40 Caixa Misteriosa PvP - 800 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_scroll_16:25:25|tEtMaXx Profession Mark - 900 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_bijou_gold:25:25|t4 EtMaXx Event Mark- 1000 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "------------------", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Se possuir o Battle Pass VIP além das recompensas normais você receberá:", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t30 000 de Gold - 100 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_04:25:25|t20 Caixa Misteriosa PvP - 200 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t90 000 Honor Points  - 300 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t60 Emblem of Frost - 400 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:25:25|t400 Arena Points - 500 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_scroll_16:25:25|tEtMaXx Profession Mark - 600 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_championsgrace:25:25|t3 EtMaXx Transmog Mark - 700 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_bijou_gold:25:25|t4 EtMaXx Event Mark - 800 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bag_enchantedrunecloth:25:25|t2 BAG VIP - 900 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_01:25:25|tEtMaXx Mount Mark + 40 Caixinhas Misteriosa - 1000 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "------------------------", 100, 0);
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
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t15 000 de Gold - 100 Pontos", 2100, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t30 000 de Gold - 100 Pontos", 3100, 0);
                }
                if (points >= 200 && viptier2 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_rune_08:25:25|t2 000 EtMaXx Mark - 200 Pontos", 2200, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_04:25:25|t20 Caixa Misteriosa PvP - 200 Pontos", 3200, 0);
                }
                if (points >= 300 && viptier3 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_jewelry_talisman_08:25:25|t15 EtMaXx Mega Mark - 300 Pontos", 2300, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t90 000 Honor Points  - 300 Pontos", 3300, 0);
                }
                if (points >= 400 && viptier4 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t60 Emblem of Frost - 400 Pontos", 2400, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t60 Emblem of Frost - 400 Pontos", 3400, 0);
                }
                if (points >= 500 && viptier5 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t80 000 Honor Points - 500 Pontos", 2500, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:25:25|t400 Arena Points - 500 Pontos", 3500, 0);
                }
                if (points >= 600 && viptier6 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_scroll_16:25:25|tEtMaXx Profession Mark - 600 Pontos", 3600, 0);
                }
                if (points >= 700 && viptier7 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_championsgrace:25:25|t3 EtMaXx Transmog Mark - 700 Pontos", 2700, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_championsgrace:25:25|t3 EtMaXx Transmog Mark - 700 Pontos", 3700, 0);
                }
                if (points >= 800 && viptier8 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_04:25:25|t40 Caixa Misteriosa PvP - 800 Pontos", 2800, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_bijou_gold:25:25|t4 EtMaXx Event Mark - 800 Pontos", 3800, 0);
                }
                if (points >= 900 && viptier9 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_scroll_16:25:25|tEtMaXx Profession Mark - 900 Pontos", 2900, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bag_enchantedrunecloth:25:25|t2 BAG VIP - 900 Pontos", 3900, 0);
                }
                if (points >= 1000 && viptier10 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_bijou_gold:25:25|t4 EtMaXx Event Mark- 1000 Pontos", 21000, 0);
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_01:25:25|tEtMaXx Mount Mark + 40 Caixinhas Misteriosa - 1000 Pontos", 31000, 0);
                }
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

            }

            if (bpvip == 0) {
                if (points < 100) {
                    ChatHandler(player->GetSession()).PSendSysMessage("Você precisa de no minimo 100 Battle Points para resgater uma recompensa.");
                    CloseGossipMenuFor(player);
                }
                if (points >= 100 && tier1 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:25:25|t15 000 de Gold - 100 Pontos", 2100, 0);
                }
                if (points >= 200 && tier2 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_rune_08:25:25|t2 000 EtMaXx Mark - 200 Pontos", 2200, 0);
                }
                if (points >= 300 && tier3 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_jewelry_talisman_08:25:25|t15 EtMaXx Mega Mark - 300 Pontos", 2300, 0);
                }
                if (points >= 400 && tier4 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:25:25|t60 Emblem of Frost - 400 Pontos", 2400, 0);
                }
                if (points >= 500 && tier5 == 0 ){
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:25:25|t80 000 Honor Points - 500 Pontos", 2500, 0);
                }
                if (points >= 700 && tier7 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_championsgrace:25:25|t3 EtMaXx Transmog Mark - 700 Pontos", 2700, 0);
                }
                if (points >= 800 && tier8 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_04:25:25|t40 Caixa Misteriosa PvP - 800 Pontos", 2800, 0);
                }
                if (points >= 900 && tier9 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_scroll_16:25:25|tEtMaXx Profession Mark - 900 Pontos", 2900, 0);
                }
                if (points >= 1000 && tier10 == 0) {
                    AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_bijou_gold:25:25|t4 EtMaXx Event Mark- 1000 Pontos", 21000, 0);
                }
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
            
        } break;

        case 2100: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier1 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyMoney(150000000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 1 Resgatada (15 000 de Gold)");
            CloseGossipMenuFor(player);
        } break;

        case 2200: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier2 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(60000, 2000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 2 Resgatada (2000 EtMaXx mark)");
            CloseGossipMenuFor(player);
        } break;

        case 2300: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier3 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(60004, 15);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 3 Resgatada (15 EtMaXx Mega Mark)");
            CloseGossipMenuFor(player);
        } break;

        case 2400: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier4 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(49426, 60);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 4 Resgatada (60 Emblem of Frost)");
            CloseGossipMenuFor(player);
        } break;

        case 2500: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier5 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyHonorPoints(80000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 5 Resgatada (80 000 Honor Points)");
            CloseGossipMenuFor(player);
        } break;   

        case 2700: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier7 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(80004, 3);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 7 Resgatada (3 EtMaXx Transmog Mark)");
            CloseGossipMenuFor(player);
        } break;

        case 2800: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier8 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(50162, 40);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 8 Resgatada (40 Caixa Misteriosa PvP)");
            CloseGossipMenuFor(player);
        }

        case 2900: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier9 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(80009, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 9 Resgatada (EtMaXx Profession Mark)");
            CloseGossipMenuFor(player);
        } break;

        case 21000: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier10 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(600600, 4);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 10 Resgatada (4 EtMaXx Event Mark)");
            CloseGossipMenuFor(player);
        } break;

        case 3100: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier1 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyMoney(300000000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 1 Resgatada (30 000 de Gold)");
            CloseGossipMenuFor(player);
        }break;

        case 3200: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier2 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(50162, 20);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do VIP Tier 2 Resgatada (20 Caixa Misteriosa PvP)");
            CloseGossipMenuFor(player);
        }break;

        case 3300: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier3 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyHonorPoints(90000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 3 Resgatada (90 000 Honor Points)");
            CloseGossipMenuFor(player);
        }break;

        case 3400: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier4 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(49426, 60);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 4 Resgatada (60 Emblem of Frost)");
            CloseGossipMenuFor(player);
        }break;

        case 3500: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier5 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyArenaPoints(400);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 5 Resgatada (400 Arena Points)");
            CloseGossipMenuFor(player);
        }break;

        case 3600: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier6 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(80009, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do VIP Tier 6 Resgatada (EtMaXx Profession Mark)");
            CloseGossipMenuFor(player);
        }break;

        case 3700: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier7 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(80004, 3);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 7 Resgatada (3 EtMaXx Transmog Mark)");
            CloseGossipMenuFor(player);    
        }break;

        case 3800: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier8 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(600600, 4);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 8 Resgatada (4 EtMaXx Event Mark)");
            CloseGossipMenuFor(player);
        }break;

        case 3900: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier9 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(34845, 2);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 9 Resgatada (2 Bag VIP)");
            CloseGossipMenuFor(player);
        }break;

        case 31000: {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier10 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(47395, 1);
            player->AddItem(50161, 40);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 10 Resgatada (1 EtMaXx Mount Mark + 40 Caixa Misteriosa)");
            CloseGossipMenuFor(player);
        }break;

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

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_bone_humanskull_01:30:30:-18:0|t50 Enemy Head + 30.000 Honor", 10, 0,"Tem certeza ?",0,false);

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_frostemblem_01:30:30:-18:0|t30 Emblems of Frost", 20, 0, "Tem certeza ?", 0, false);

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:30:30:-18:0|t1200 de Arena Rating + 100 Arena Points", 30, 0, "Tem certeza ?", 0, false);

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_sword_26:30:30:-18:0|tEscolha seu Transmog", 50, 0);

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_sword_26:30:30:-18:0|tPegue um item invisivel (Para Transmog)", 60, 0);
              
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
                else if (player->HasItemCount(600500, 50, true) && (player->GetHonorPoints() >= 30000)) {
                    player->DestroyItemCount(600500, 50, true);
                    player->ModifyHonorPoints(-30000);
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
                else if (player->HasItemCount(49426, 30, true)) {
                    player->DestroyItemCount(49426, 30, true);
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
                else if (player->GetArenaPersonalRating(0) >= 1200 && player->GetArenaPoints() >= 100) {
                    player->ModifyArenaPoints(-100);
                    player->AddItem(80004, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por adquirir uma EtMaXx Transmog Mark");
                    CloseGossipMenuFor(player);
                }
                else {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVocê precisa de 1300 de Arena Rating + 200 Arena Points", 100, 0);
                    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
            } break;

            //Menu Geral
            case 50:
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_27:30:30:-18:0|tArmas", 70, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shirt_guildtabard_01:30:30:-18:0|tTabards", 13000, 0);

                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 100, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            // Menu de Armas
            case 70:
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

            case 60:
            { 
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shoulder_24:30:30:-18:0|tOmbreira", 600, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_chest_plate04:30:30:-18:0|tPeitoral", 601, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shirt_white_01:30:30:-18:0|tCamisa", 602, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shirt_guildtabard_01:30:30:-18:0|tTabard", 603, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_bracer_03:30:30:-18:0|tBracelete", 604, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_gauntlets_16:30:30:-18:0|tLuva", 605, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_belt_03:30:30:-18:0|tCinto", 606, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_pants_01:30:30:-18:0|tCalça", 607, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_boots_09:30:30:-18:0|tBota", 608, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_04:30:30:-18:0|tShield", 609, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_orb_01:30:30:-18:0|tOff-hand", 610, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 100, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            } break;

            case 600:
            {
                player->AddItem(100100, 1);
                CloseGossipMenuFor(player);
            } break;

            case 601:
            {
                player->AddItem(100103, 1);
                CloseGossipMenuFor(player);
            } break;

            case 602:
            {
                player->AddItem(100110, 1);
                CloseGossipMenuFor(player);
            } break;

            case 603:
            {
                player->AddItem(100101, 1);
                CloseGossipMenuFor(player);
            } break;

            case 604:
            {
                player->AddItem(100108, 1);
                CloseGossipMenuFor(player);
            } break;

            case 605:
            {
                player->AddItem(100105, 1);
                CloseGossipMenuFor(player);
            } break;

            case 606:
            {
                player->AddItem(100109, 1);
                CloseGossipMenuFor(player);
            } break;

            case 607:
            {
                player->AddItem(100104, 1);
                CloseGossipMenuFor(player);
            } break;

            case 608:
            {
                player->AddItem(100106, 1);
                CloseGossipMenuFor(player);
            } break;

            case 609:
            {
                player->AddItem(100111, 1);
                CloseGossipMenuFor(player);
            } break;

            case 610:
            {
                player->AddItem(100112, 1);
                CloseGossipMenuFor(player);
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

            //Tabards
            case 13000:
            {
                player->GetSession()->SendListInventory(creature->GetGUID(), 90512);
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

        if (player->getClass() == CLASS_DEATH_KNIGHT && !player->HasItemCount(37836, 1, true) && player->GetAreaId() == 4342)
        {
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_deathknight_unholypresence:30:30:-18:0|tQuero fazer todas as Quests de DK", 300, 0, "Tem certeza ?", 0, false);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_deathknight_frostpresence:30:30:-18:0|tWOW INCRIVEL, JÁ CONHECO A LORE QUERO PULAR AS QUESTS DE DK !", 301, 0, "Tem certeza ?", 0, false);
            player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
            return true;
        }

        if (!player->HasItemCount(37836, 1, true) && player->getLevel() <= 60) {

            if (player->getClass() == CLASS_DRUID) {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/ability_druid_catform:30:30:-18:0|tWOW INCRIVEL, QUERO UPAR DE FERAL !", 100, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_forceofnature:30:30:-18:0|tWOW INCRIVEL, QUERO UPAR DE BALANCE !", 101, 0, "Tem certeza ?", 0, false);
                player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
            } else if (player->getClass() == CLASS_SHAMAN) {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_shaman_lavaburst:30:30:-18:0|tWOW INCRIVEL, QUERO UPAR DE ELEMENTAL !", 200, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/ability_shaman_stormstrike:30:30:-18:0|tWOW INCRIVEL, QUERO UPAR DE ENHANCEMENT !", 201, 0, "Tem certeza ?", 0, false);
                player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
            } else {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_box_02:30:30:-18:0|tWOW INCRIVEL, ME DA LOGO ESSES ITEMS !", 1, 0);
                player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
            }
			
        } else {
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
                    player->AddItem(33478, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    player->AddItem(60119, 50);
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
                    player->AddItem(50052, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    player->AddItem(60019, 50);
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
                    player->AddItem(60119, 50);
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
                    player->AddItem(50731, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    player->AddItem(60119, 50);
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
                    player->AddItem(50731, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    player->AddItem(60119, 50);
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
                    player->AddItem(50731, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    player->AddItem(60119, 50);
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
                    player->AddItem(30906, 1);
                    player->AddAura(30567, player);
                    player->AddAura(30557, player);
                    player->AddAura(30562, player);
                    player->AddItem(37836, 1);
                    player->AddItem(60119, 50);
                    ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Caçador");
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
                player->AddItem(45695, 1);
                player->AddItem(37836, 1);
                player->AddItem(60119, 50);
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
                player->AddItem(50731, 1);
                player->AddItem(37836, 1);
                player->AddItem(60119, 50);
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
                player->AddItem(51798, 1);
                player->AddItem(45887, 1);
                player->AddItem(37836, 1);
                player->AddItem(60119, 50);
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
                player->AddItem(50303, 1);
                player->AddItem(50303, 1);
                player->AddItem(37836, 1);
                player->AddItem(60119, 50);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Xamã");
                CloseGossipMenuFor(player);
            }break;

            case 300:
            {
                player->AddAura(30567, player);
                player->AddAura(30557, player);
                player->AddAura(30562, player);
                player->AddItem(37836, 1);
                player->AddItem(60119, 20);
                ChatHandler(player->GetSession()).PSendSysMessage("Você já está bem avançado em sua jornada, não precisa da minha ajuda. Receba apenas minha benção");
                CloseGossipMenuFor(player);
            }break;

            case 301:
            {
                int DKL = 1;

                if (player->getLevel() == 80) {
                    DKL = 80
                }else{
                    DKL = 58
                }

                player->SetLevel(DKL);
                player->learnSpell(53428);//runeforging
                player->learnSpell(53441);//runeforging
                player->learnSpell(53344);//runeforging
                player->learnSpell(62158);//runeforging
                player->learnSpell(33391);//journeyman riding
                player->learnSpell(54586);//runeforging credit
                player->learnSpell(48778);//acherus deathcharger
                player->learnSpell(49998);//Death Strike Rank 1 (Sem bug)
                player->removeSpell(45470, SPEC_MASK_ALL, false);//Remove a DeathStrike Bugada (cura infinita)
                player->learnSkillRewardedSpells(776, 375);//Runeforging
                player->learnSkillRewardedSpells(960, 375);//Runeforging
                player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 38661, true);//Greathelm of the Scourge Champion
                player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 38666, true);//Plated Saronite Bracers
                player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 38668, true);//The Plaguebringer's Girdle
                player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 38667, true);//Bloodbane's Gauntlets of Command
                player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 38665, true);//Saronite War Plate
                player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 38669, true);//Engraved Saronite Legplates
                player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 38663, true);// Blood-Soaked Saronite Plated Spaulders
                player->EquipNewItem(EQUIPMENT_SLOT_FEET, 38670, true);//Greaves of the Slaughter
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 38675, true);//Signet of the Dark Brotherhood
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 38674, true);//Soul Harvester's Charm
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 38671, true);//Valanar's Signet Ring
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 38672, true);// Keleseth's Signet Ring
                player->EquipNewItem(19, 10050, true);
                player->EquipNewItem(20, 10050, true);
                player->EquipNewItem(21, 10050, true);
                player->EquipNewItem(22, 10050, true);
                player->AddItem(39320, true);//Sky Darkener's Shroud of Blood
                player->AddItem(38664, true);//Sky Darkener's Shroud of the Unholy
                player->AddItem(39322, true);//Shroud of the North Wind
                player->AddItem(38632, true);//Greatsword of the Ebon Blade
                player->AddItem(6948, true);//Hearthstone
                player->AddItem(38707, true);//Runed Soulblade
                player->AddItem(40483, true);//Insignia of the Scourge

                // Quests
                if (player->GetQuestStatus(12657) == QUEST_STATUS_NONE)//The Might Of The Scourge
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(12657), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(12657), false, player);
                }
                if (player->GetQuestStatus(12801) == QUEST_STATUS_NONE)//The Light of Dawn
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(12801), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(12801), false, player);
                }
                if (player->GetTeamId() == TEAM_ALLIANCE && player->GetQuestStatus(13188) == QUEST_STATUS_NONE)//Where Kings Walk
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13188), nullptr);
                else if (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(13189) == QUEST_STATUS_NONE)//Saurfang's Blessing
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13189), nullptr);


                player->AddAura(30567, player);
                player->AddAura(30557, player);
                player->AddAura(30562, player);
                player->AddItem(33478, 1);
                player->AddItem(37836, 1);
                player->AddItem(60119, 10);

                ChatHandler(player->GetSession()).PSendSysMessage("Você já está bem avançado em sua jornada, não precisa da minha ajuda. Receba apenas minha benção");

                // Teleport
                if (player->GetTeamId() == TEAM_ALLIANCE)
                    player->TeleportTo(0, -8833.37f, 628.62f, 94.00f, 1.06f);//Stormwind
                else
                    player->TeleportTo(1, 1569.59f, -4397.63f, 16.06f, 0.54f);//Orgrimmar

                ObjectAccessor::SaveAllPlayers();//Save
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

    //int skillid[11] = {SKILL_BLACKSMITHING, SKILL_TAILORING, SKILL_LEATHERWORKING, SKILL_ENGINEERING, SKILL_ENCHANTING, SKILL_ALCHEMY, SKILL_MINING, SKILL_HERBALISM, SKILL_SKINNING, SKILL_INSCRIPTION, SKILL_JEWELCRAFTING};
    //int skillid2[3] = { SKILL_FISHING, SKILL_FIRST_AID, SKILL_COOKING };

    bool MarkCheck(Player* player, int count, int skill) {

        if (player->HasSkill(skill))
        {
            player->GetSession()->SendNotification("Você já tem essa profissão");
            CloseGossipMenuFor(player);
            return false;
        }

        if (player->HasItemCount(600600, count, true)) {
            player->DestroyItemCount(600600, count, true);
            return true;
        }
        else {
            ChatHandler(player->GetSession()).PSendSysMessage("Você não tem EtMaXx Event Mark suficientes ou uma EtMaXx Profession Token.");
            CloseGossipMenuFor(player);
            return false;
        }
    }

    bool ProfTokenCheck(Player* player, int count, int choice) {

        if (player->HasSkill(choice))
        {
            player->GetSession()->SendNotification("Você já tem essa profissão");
            CloseGossipMenuFor(player);
            return false;
        }

        if (player->HasItemCount(80009, count, true)) {
            player->DestroyItemCount(80009, count, true);
            return true;
        }
        else {
            return false;
        }
    }

    bool LearnProfession(Player* player, int skill) {
        learn_commandscript::HandleLearnSkillRecipesHelper(player, skill);
        player->SetSkill(skill, player->GetSkillStep(skill), 450, 450);
        return true;
    }

    static bool HasFreeProfession(Player* player, SkillType Skill)
    {
        if (Skill == SKILL_FISHING || Skill == SKILL_COOKING || Skill == SKILL_FIRST_AID)
            return true;

        uint8 SkillCount = 0;

        if (player->HasSkill(SKILL_MINING))
            SkillCount++;
        if (player->HasSkill(SKILL_SKINNING))
            SkillCount++;
        if (player->HasSkill(SKILL_HERBALISM))
            SkillCount++;

        for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
        {
            if (SkillLineEntry const* SkillInfo = sSkillLineStore.LookupEntry(i))
            {
                if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
                    continue;

                if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
                    continue;

                if (player->HasSkill(SkillInfo->id))
                    SkillCount++;
            }
        }

        if (SkillCount > 0 && player->HasSkill(Skill))
            SkillCount--;

        return SkillCount < 2;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();
        
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_bag_17:35:35:-30:0|tResgate sua Recompensa", 100, 0);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "----------------------------------------", 9999, 0);
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
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_book_11:35:35:-25:0|tProfissão Full - 3 Event Mark", 1000, 0,"Tem certeza ?",0,false);                           // 03 Event Mark                                        // 03 Event Mark
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:35:35:-25:0|t10 000 Honor Points - 2 Event Mark", 2000, 0, "Tem certeza ?", 0, false);              // 02 Event Mark
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:35:35:-25:0|t200 Arena Points - 2 Event Mark", 3000, 0, "Tem certeza ?", 0, false); // 02 Event Mark
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:35:35:-25:0|t30 Emblem of Frost - 2 Event Mark", 4000, 0, "Tem certeza ?", 0, false);                // 02 Event Mark
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_championsgrace:35:35:-25:0|tEtMaXx Transmog Mark - 4 Event Mark", 5000, 0, "Tem certeza ?", 0, false);            // 04 Event Mark
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_shirt_guildtabard_01:35:35:-25:0|tEtMaXx Tabard Mark - 5 Event Mark", 6000, 0, "Tem certeza ?", 0, false);               // 05 Event Mark 
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_jewelry_amulet_01:35:35:-25:0|tEtMaXx Mount Mark - 7 Event Mark", 7000, 0, "Tem certeza ?", 0, false);                   // 07 Event Mark
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_gem_pearl_04:35:35:-25:0|tEtMaXx Sanctified Mark - 8 Event Mark", 8000, 0, "Tem certeza ?", 0, false);              // 08 Event Mark 
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "----------------------------------------", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bag_10:35:35:-25:0|tComprar Tabard", 1, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bag_10:35:35:-25:0|tComprar Token Sanctified Normal", 2, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bag_10:35:35:-25:0|tTrocar Marks de Natal", 3, 0);
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

        case 3: {
            player->GetSession()->SendListInventory(creature->GetGUID(), 65001);
        }break;
            
        case 1000: {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_blacksmithing:35:35:-25:0|tBlacksmithing", 10000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_gem_02:35:35:-25:0|tJewelcrafting", 20000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_tailoring:35:35:-25:0|tTailoring", 30000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_engraving:35:35:-25:0|tEncanting", 40000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_alchemy:35:35:-25:0|tAlchemy", 50000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_inscription_tradeskill01:35:35:-25:0|tInscription", 60000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_engineering:35:35:-25:0|tEngineering", 70000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_armorkit_17:35:35:-25:0|tLeatherworking", 80000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_mining:35:35:-25:0|tMining", 90000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_pelt_wolf_01:35:35:-25:0|tSkinning", 100000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_herbalism:35:35:-25:0|tHerbalism", 110000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_food_15:35:35:-25:0|tCooking", 120000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_fishing:35:35:-25:0|tFishing", 130000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_sealofsacrifice:35:35:-25:0|tFirst Aid", 140000, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "----------------------------------------", 1000, 0);
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/ICONS/Ability_Spy:35:35:-25:0|tVoltar...", 100, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }break;

        case 2000: {
            if (MarkCheck(player, 2, 2000)) {
                player->ModifyHonorPoints(10000);
                ChatHandler(player->GetSession()).PSendSysMessage("10.000 pontos de honra recebidos");
                CloseGossipMenuFor(player);
            }
        }break;

        case 3000: {
            if (MarkCheck(player,2, 3000)) {
                player->ModifyArenaPoints(200);
                ChatHandler(player->GetSession()).PSendSysMessage("200 pontos de Arena recebidos");
                CloseGossipMenuFor(player);
            }
        }break;

        case 4000: {
            if (MarkCheck(player, 2, 4000)) {
                player->AddItem(49426, 30);
                ChatHandler(player->GetSession()).PSendSysMessage("30 Emblem of Frost recebidos");
                CloseGossipMenuFor(player);
            }
        }break;

        case 5000: {
            if (MarkCheck(player, 4, 5000)) {
                player->AddItem(80004, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }
        }break;

        case 6000: {
            if (MarkCheck(player, 5, 6000)) {
                player->AddItem(80005, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Tabard Mark recebida");
                CloseGossipMenuFor(player);
            }
        }break;

        case 7000: {
            if (MarkCheck(player, 7, 7000)) {
                player->AddItem(47395, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Mount Mark recebida");
                CloseGossipMenuFor(player);
            }
        }break;

        case 8000: {
            if (MarkCheck(player, 8, 8000)) {
                player->AddItem(80006, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Sanctified Mark recebida");
                CloseGossipMenuFor(player);
            }
        }break;

        //BS
        case 10000:
        {
            if (HasFreeProfession(player, SKILL_BLACKSMITHING)) {
                if (ProfTokenCheck(player, 1, SKILL_BLACKSMITHING)) {
                    LearnProfession(player, SKILL_BLACKSMITHING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_BLACKSMITHING)) {
                    LearnProfession(player, SKILL_BLACKSMITHING);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
            
        }break;

        //Jewel
        case 20000:
        {
            if (HasFreeProfession(player, SKILL_JEWELCRAFTING)) {
                if (ProfTokenCheck(player, 1, SKILL_JEWELCRAFTING)) {
                    LearnProfession(player, SKILL_JEWELCRAFTING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_JEWELCRAFTING)) {
                    LearnProfession(player, SKILL_JEWELCRAFTING);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        //Tailor
        case 30000:
        {
            if (HasFreeProfession(player, SKILL_TAILORING)) {
                if (ProfTokenCheck(player, 1, SKILL_TAILORING)) {
                    LearnProfession(player, SKILL_TAILORING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_TAILORING)) {
                    LearnProfession(player, SKILL_TAILORING);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        //Enchanting
        case 40000:
        {
            if (HasFreeProfession(player, SKILL_ENCHANTING)) {
                if (ProfTokenCheck(player, 1, SKILL_ENCHANTING)) {
                    LearnProfession(player, SKILL_ENCHANTING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_ENCHANTING)) {
                    LearnProfession(player, SKILL_ENCHANTING);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        //Alchemy
        case 50000:
        {
            if (HasFreeProfession(player, SKILL_ALCHEMY)) {
                if (ProfTokenCheck(player, 1, SKILL_ALCHEMY)) {
                    LearnProfession(player, SKILL_ALCHEMY);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_ALCHEMY)) {
                    LearnProfession(player, SKILL_ALCHEMY);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        //Inscription
        case 60000:
        {
            if (HasFreeProfession(player, SKILL_INSCRIPTION)) {
                if (ProfTokenCheck(player, 1, SKILL_INSCRIPTION)) {
                    LearnProfession(player, SKILL_INSCRIPTION);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_INSCRIPTION)) {
                    LearnProfession(player, SKILL_INSCRIPTION);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        //Engineering
        case 70000:
        {
            if (HasFreeProfession(player, SKILL_ENGINEERING)) {
                if (ProfTokenCheck(player, 1, SKILL_ENGINEERING)) {
                    LearnProfession(player, SKILL_ENGINEERING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_ENGINEERING)) {
                    LearnProfession(player, SKILL_ENGINEERING);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        //leatherworking
        case 80000:
        {
            if (HasFreeProfession(player, SKILL_LEATHERWORKING)) {
                if (ProfTokenCheck(player, 1, SKILL_LEATHERWORKING)) {
                    LearnProfession(player, SKILL_LEATHERWORKING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_LEATHERWORKING)) {
                    LearnProfession(player, SKILL_LEATHERWORKING);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        //Mining
        case 90000:
        {
            if (HasFreeProfession(player, SKILL_MINING)) {
                if (ProfTokenCheck(player, 1, SKILL_MINING)) {
                    LearnProfession(player, SKILL_MINING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_MINING)) {
                    LearnProfession(player, SKILL_MINING);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        //Skinning
        case 100000:
        {
            if (HasFreeProfession(player, SKILL_SKINNING)) {
                if (ProfTokenCheck(player, 1, SKILL_SKINNING)) {
                    LearnProfession(player, SKILL_SKINNING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_SKINNING)) {
                    LearnProfession(player, SKILL_SKINNING);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        //Herbalism
        case 110000:
        {
            if (HasFreeProfession(player, SKILL_HERBALISM)) {
                if (ProfTokenCheck(player, 1, SKILL_HERBALISM)) {
                    LearnProfession(player, SKILL_HERBALISM);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_HERBALISM)) {
                    LearnProfession(player, SKILL_HERBALISM);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        //Cooking
        case 120000:
        {
            if (HasFreeProfession(player, SKILL_COOKING)) {
                if (ProfTokenCheck(player, 1, SKILL_COOKING)) {
                    LearnProfession(player, SKILL_COOKING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_COOKING)) {
                    LearnProfession(player, SKILL_COOKING);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        //Fishing
        case 130000:
        {
            if (HasFreeProfession(player, SKILL_FISHING)) {
                if (ProfTokenCheck(player, 1, SKILL_FISHING)) {
                    LearnProfession(player, SKILL_FISHING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_FISHING)) {
                    LearnProfession(player, SKILL_FISHING);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        //First Aid
        case 140000:
        {
            if (HasFreeProfession(player, SKILL_FIRST_AID)) {
                if (ProfTokenCheck(player, 1, SKILL_FIRST_AID)) {
                    LearnProfession(player, SKILL_FIRST_AID);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_FIRST_AID)) {
                    LearnProfession(player, SKILL_FIRST_AID);
                    CloseGossipMenuFor(player);
                }
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }break;

        }

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC T8                                ///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_startset : public CreatureScript
{
public:
    etmaxx_startset() : CreatureScript("etmaxx_startset") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        ClearGossipMenuFor(player);

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_rune_09:35:35:-25:0|tMe da logo essa token", 100, 0,"Tem certeza que vai gastar 1500 EtMaXx Mark e 5 EtMaXx Mega Mark ?",0,false);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bag_10:35:35:-25:0|tQuero dar uma olhada no que você tem ai.", 200, 0);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "----------------------------------------", 9999, 0);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:35:35:-25:0|tUpdate Menu", 9999, 0);
 
        SendGossipMenuFor(player, 800806, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
        case 100: {
            if (player->HasItemCount(60000, 1500) && player->HasItemCount(60004, 5)) {
                player->DestroyItemCount(60000, 1500, true);
                player->DestroyItemCount(60004, 5, true);
                player->AddItem(800801, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Você Recebeu 1 EtMaXx Tier 8 Token, fale com o NPC novamente para trocar por uma parte Tier 8");
                CloseGossipMenuFor(player);
            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Você precisa de 1500 EtMaXx Mark + 5 EtMaXx Mega Mark para pegar uma EtMaXx Tier 8 Token");
                CloseGossipMenuFor(player);
            } 
        }break;

        case 200:  // Main menuu
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 80002);
        }break;

        case 9999:  // Main menu
        {
            OnGossipHello(player, creature);
        }break;

        }
        return true;
    }
};


///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Keystone                          ///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_keystone : public CreatureScript
{
public:
    etmaxx_keystone() : CreatureScript("etmaxx_keystone") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        ClearGossipMenuFor(player);


        // 658 = Pit of Saron
        // 668 = Halls of Reflection
        // 632 = Forge of Souls

        if (player->GetMapId() == 658) {        
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bone_skull_02:35:35:-25:0|tQuero fazer a masmorra na dificuldade Heroic Plus + 5", 5, 0, "Tem certeza?", 0, false);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bone_skull_02:35:35:-25:0|tQuero fazer a masmorra na dificuldade Heroic Plus + 10", 10, 0, "Tem certeza?", 0, false);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bone_skull_02:35:35:-25:0|tQuero fazer a masmorra na dificuldade Heroic Plus + 15", 15, 0, "Tem certeza?", 0, false);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bone_skull_02:35:35:-25:0|tQuero fazer a masmorra na dificuldade Heroic Plus + 20", 20, 0, "Tem certeza?", 0, false);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bone_skull_02:35:35:-25:0|tQuero fazer a masmorra na dificuldade Heroic Plus + 25", 25, 0, "Tem certeza?", 0, false);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bone_skull_02:35:35:-25:0|tQuero fazer a masmorra na dificuldade Heroic Plus + 30", 30, 0, "Tem certeza?", 0, false);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bone_skull_02:35:35:-25:0|tQuero fazer a masmorra na dificuldade Heroic Plus + 35", 35, 0, "Tem certeza?", 0, false);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bone_skull_02:35:35:-25:0|tQuero fazer a masmorra na dificuldade Heroic Plus + 40", 40, 0, "Tem certeza?", 0, false);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bone_skull_02:35:35:-25:0|tQuero fazer a masmorra na dificuldade Heroic Plus + 45", 45, 0, "Tem certeza?", 0, false);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bone_skull_02:35:35:-25:0|tQuero fazer a masmorra na dificuldade Heroic Plus + 50", 50, 0, "Tem certeza?", 0, false);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bone_skull_02:35:35:-25:0|tQuero fazer a masmorra na dificuldade Heroic Plus + 100", 100, 0, "Tem certeza?", 0, false);
        }
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "----------------------------------------", 9999, 0);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:35:35:-25:0|tUpdate Menu", 9999, 0);
 
        SendGossipMenuFor(player, 800809, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
        case 5:
        case 10:
        case 15:
        case 20:
        case 25:
        case 30:
        case 35:
        case 40:
        case 45:
        case 50:
        case 100:
        {
            player->GetInstanceScript()->StartHeroicPlus(sender);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }break;

        case 9999:  // Main menu
        {
            OnGossipHello(player, creature);
        }break;

        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Migração DK Fix                   ///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_start : public CreatureScript
{
public:
    etmaxx_dk() : CreatureScript("etmaxx_dk") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();

        if (player->getClass() == CLASS_DEATH_KNIGHT && !player->HasItemCount(37836, 1, true)
        {
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_deathknight_frostpresence:30:30:-18:0|tCompletar todas as Quests de DK", 301, 0, "Tem certeza ?", 0, false);
            player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
            return true;
        }
        else {
            ChatHandler(player->GetSession()).PSendSysMessage("Eu só falo com Cavaleiros da Morte!");
            CloseGossipMenuFor(player);
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 /*action*/)
    {
        switch (sender)
        {
        case 301:
        {
            player->SetLevel(80);
            player->learnSpell(53428);//runeforging
            player->learnSpell(53441);//runeforging
            player->learnSpell(53344);//runeforging
            player->learnSpell(62158);//runeforging
            player->learnSpell(33391);//journeyman riding
            player->learnSpell(54586);//runeforging credit
            player->learnSpell(48778);//acherus deathcharger
            player->learnSpell(49998);//Death Strike Rank 1 (Sem bug)
            player->removeSpell(45470, SPEC_MASK_ALL, false);//Remove a DeathStrike Bugada (cura infinita)
            player->learnSkillRewardedSpells(776, 375);//Runeforging
            player->learnSkillRewardedSpells(960, 375);//Runeforging
            player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 38661, true);//Greathelm of the Scourge Champion
            player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 38666, true);//Plated Saronite Bracers
            player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 38668, true);//The Plaguebringer's Girdle
            player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 38667, true);//Bloodbane's Gauntlets of Command
            player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 38665, true);//Saronite War Plate
            player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 38669, true);//Engraved Saronite Legplates
            player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 38663, true);// Blood-Soaked Saronite Plated Spaulders
            player->EquipNewItem(EQUIPMENT_SLOT_FEET, 38670, true);//Greaves of the Slaughter
            player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 38675, true);//Signet of the Dark Brotherhood
            player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 38674, true);//Soul Harvester's Charm
            player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 38671, true);//Valanar's Signet Ring
            player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 38672, true);// Keleseth's Signet Ring
            player->EquipNewItem(19, 10050, true);
            player->EquipNewItem(20, 10050, true);
            player->EquipNewItem(21, 10050, true);
            player->EquipNewItem(22, 10050, true);
            player->AddItem(39320, true);//Sky Darkener's Shroud of Blood
            player->AddItem(38664, true);//Sky Darkener's Shroud of the Unholy
            player->AddItem(39322, true);//Shroud of the North Wind
            player->AddItem(38632, true);//Greatsword of the Ebon Blade
            player->AddItem(6948, true);//Hearthstone
            player->AddItem(38707, true);//Runed Soulblade
            player->AddItem(40483, true);//Insignia of the Scourge

            // Quests
            if (player->GetQuestStatus(12657) == QUEST_STATUS_NONE)//The Might Of The Scourge
            {
                player->AddQuest(sObjectMgr->GetQuestTemplate(12657), nullptr);
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12657), false, player);
            }
            if (player->GetQuestStatus(12801) == QUEST_STATUS_NONE)//The Light of Dawn
            {
                player->AddQuest(sObjectMgr->GetQuestTemplate(12801), nullptr);
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12801), false, player);
            }
            if (player->GetTeamId() == TEAM_ALLIANCE && player->GetQuestStatus(13188) == QUEST_STATUS_NONE) {
                player->AddQuest(sObjectMgr->GetQuestTemplate(13188), nullptr);
                player->RewardQuest(sObjectMgr->GetQuestTemplate(13188), false, player);
            }
            else if (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(13189) == QUEST_STATUS_NONE) {//Saurfang's Blessing
                player->AddQuest(sObjectMgr->GetQuestTemplate(13189), nullptr);
                player->RewardQuest(sObjectMgr->GetQuestTemplate(13189), false, player);
            }
            player->AddItem(37836, 1);
            player->TeleportTo(571, 5741.36f, 626.982f, 648.354f, 0.28f); //Dalaran

            ObjectAccessor::SaveAllPlayers();//Save

        }break;
        }
    }

}

///////////////////////////////////////////////////////////////////////////////////
/////////////                 Instanciando o NPC                    ///////////////
///////////////////////////////////////////////////////////////////////////////////;

void AddNpcEtmaxxScripts()
{
    new etmaxx_npc();
    new etmaxx_battlepass();
    new etmaxx_transmog_vendor();
    new etmaxx_start();
	new etmaxx_tabard();
    new etmaxx_event();
    new etmaxx_startset();
    new etmaxx_keystone();
    new etmaxx_dk();
}
