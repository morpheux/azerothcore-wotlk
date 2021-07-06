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

// 100 tabards
uint32 tabardHorda[] = {
60080, 60081, 60082, 60083, 60100, 60101, 60102, 60103, 60275, 60121,
60122, 60123, 60140, 60141, 60142, 60143, 60160, 60161, 60162, 60163,
60084, 60085, 60086, 60087, 60104, 60105, 60106, 60107, 60124, 60125,
60126, 60127, 60144, 60145, 60146, 60147, 60164, 60165, 60166, 60167,
60088, 60089, 60090, 60091, 60108, 60109, 60110, 60111, 60128, 60129,
60130, 60131, 60148, 60149, 60150, 60151, 60168, 60169, 60170, 60171,
60092, 60093, 60094, 60095, 60112, 60113, 60114, 60115, 60132, 60133,
60134, 60135, 60152, 60153, 60154, 60155, 60172, 60173, 60174, 60175,
60096, 60097, 60098, 60099, 60116, 60117, 60118, 60120, 60136, 60137,
60138, 60139, 60156, 60157, 60158, 60159, 60176, 60177, 60178, 60179
};

// 96 Tabards
uint32 tabardAlly[] = {
60180, 60184, 60188, 60192, 60196, 60181, 60185, 60189, 60193, 60197,
60182, 60186, 60190, 60194, 60198, 60183, 60187, 60191, 60195, 60199,
60200, 60204, 60208, 60212, 60216, 60201, 60205, 60209, 60213, 60217,
60202, 60206, 60210, 60214, 60218, 60203, 60207, 60211, 60215, 60219,
60220, 60224, 60228, 60232, 60236, 60221, 60225, 60229, 60233, 60237,
60222, 60226, 60230, 60234, 60238, 60223, 60227, 60231, 60235, 60239,
60240, 60244, 60248, 60252, 60272, 60241, 60245, 60249, 60253, 60273,
60242, 60246, 60250, 60254, 60274, 60243, 60247, 60251, 60255, 60276,
60256, 60260, 60264, 60268, 60257, 60261, 60265, 60269, 60258, 60262,
60266, 60270, 60259, 60263, 60267, 60271
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
/////////////	                    EtMaXx Cafe      				///////////////
///////////////////////////////////////////////////////////////////////////////////
class etmaxx_npc : public CreatureScript
{
public:
    etmaxx_npc() : CreatureScript("etmaxx_npc") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        ClearGossipMenuFor(player);

        if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 37500)
        {
            if (player->GetTeamId(true) == TEAM_ALLIANCE && !player->HasSpell(16056))
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/Ability_mount_whitetiger:35:35:-25:0|tResgate seu Reins of the Ancient Frostsaber", 3, 0);

            if (player->GetTeamId(true) == TEAM_HORDE && !player->HasSpell(16081))
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/Ability_mount_whitedirewolf:35:35:-25:0|tResgate seu Horn of the Arctic Wolf", 3, 0);
        }

        if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 50000 && !player->HasSpell(43688))
        {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/Ability_druid_challangingroar:35:35:-25:0|tResgate seu Amani War Bear", 2, 0);
        }

        if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 62500 && !player->HasSpell(75614))
        {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/Ability_mount_celestialhorse:35:35:-25:0|tResgate Seu Celestial Steed", 1, 0);
        }

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_jewelry_necklace_27:35:35:-25:0|tResgate Sua Mount Mark", 5, 0);

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bag_10:35:35:-25:0|tQuero dar uma olhada", 4, 0);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "------------------------------------------", 999, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-18:0|tUpdate menu", 999, 0);
        //AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-18:0|tToca Musica", 9999, 0);

        SendGossipMenuFor(player, 800807, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
        case 999:
        {
            OnGossipHello(player, creature);
        }
        break;

        case 1:
        {
            player->DestroyItemCount(54811, 1, true);
            player->AddItem(54811, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Team: Item Adicionado em sua Bag. Parabéns!");
            CloseGossipMenuFor(player);
        }
        break;

        case 2:
        {
            player->DestroyItemCount(33809, 1, true);
            player->AddItem(33809, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Team: Item Adicionado em sua Bag. Parabéns!");
            CloseGossipMenuFor(player);
        }
        break;

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
        }

        break;

        case 4:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 65000);
        }
        break;

        case 5:
        {
            if (player->HasItemCount(60018, 15, true))
            {
                player->DestroyItemCount(60018, 15, true);
                player->AddItem(47395, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Parabéns, você é um vitorioso!");
                CloseGossipMenuFor(player);
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você precisa de 15 EtMaXx Victory Mark");
                CloseGossipMenuFor(player);
            }
        }
        break;
        }

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////               NPC Battle Pass                        	///////////////
///////////////////////////////////////////////////////////////////////////////////

class etmaxx_battlepass : public CreatureScript
{
public:
    etmaxx_battlepass() : CreatureScript("etmaxx_battlepass") {}

    uint32 bpvip = 0;
    uint points = 0;
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
    uint32 viptier4 = 0;
    uint32 viptier5 = 0;
    uint32 viptier6 = 0;
    uint32 viptier7 = 0;
    uint32 viptier8 = 0;
    uint32 viptier9 = 0;
    uint32 viptier10 = 0;

    bool OnGossipHello(Player *player, Creature *creature)
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT bpvip,points FROM character_battlepass WHERE guid = %u", player->GetSession()->GetGuidLow());
        if (result)
        {
            Field *fields = result->Fetch();
            bpvip = fields[0].GetUInt32();
            points = fields[1].GetUInt32();
        }

        player->PlayerTalkClass->ClearMenus();

        if (result && bpvip == 0)
        {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_qiraj_jewelglyphed:30:30:-18:0|tQuero participar do EtMaXx VIP Battle Pass", 2, 0, "Tem certeza ?", 0, false);

            if (player->HasItemCount(80001, 1, true))
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_08:30:30:-18:0|tQuero entregar um EtMaXx BP Daily Mark", 4, 0, "Tem certeza ?", 0, false);
            }

            if (player->HasItemCount(80002, 1, true))
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_11:30:30:-18:0|tQuero entregar um EtMaXx BP Week Mark", 5, 0, "Tem certeza ?", 0, false);
            }

            if (player->HasItemCount(80003, 1, true))
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_qiraj_jewelblessed:30:30:-18:0|tQuero entregar um EtMaXx BP Unique Mark", 6, 0, "Tem certeza ?", 0, false);
            }

            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_elvencoins:30:30:-18:0|tQuero ver meus Battle Points", 3, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "------------------------", 5000, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_scroll_05:30:30:-18:0|tMe Mostre o Battle Pass", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_02:30:30:-18:0|tResgate sua Recompensa", 2000, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_weapon_shortblade_47:30:30:-18:0|tTransmogs Exclusivos do Battlepass", 10, 0);
        }
        else if (result && bpvip == 1)
        {
            if (player->HasItemCount(80001, 1, true))
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_08:30:30:-18:0|tQuero entregar um EtMaXx BP Daily Mark", 4, 0, "Tem certeza ?", 0, false);
            }

            if (player->HasItemCount(80002, 1, true))
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_11:30:30:-18:0|tQuero entregar um EtMaXx BP Week Mark", 5, 0, "Tem certeza ?", 0, false);
            }

            if (player->HasItemCount(80003, 1, true))
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_qiraj_jewelblessed:30:30:-18:0|tQuero entregar um EtMaXx BP Unique Mark", 6, 0, "Tem certeza ?", 0, false);
            }

            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_elvencoins:30:30:-18:0|tQuero ver meus Battle Points", 3, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "------------------------", 5000, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_scroll_05:30:30:-18:0|tMe Mostre o Battle Pass", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_02:30:30:-18:0|tResgate sua Recompensa", 2000, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_weapon_shortblade_47:30:30:-18:0|tTransmogs Exclusivos do Battlepass", 10, 0);
        }
        else
        {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_scroll_04:30:30:-18:0|tQuero Participar do EtMaXx Battle Pass", 1, 0);
        }

        SendGossipMenuFor(player, 800808, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
        case 1:
        {
            CharacterDatabase.PExecute("INSERT INTO character_battlepass(guid, bpvip, points, tier1, tier2, tier3, tier4, tier5, tier6, tier7, tier8, tier9, tier10, viptier1, viptier2, viptier3, viptier4, viptier5, viptier6, viptier7, viptier8, viptier9, viptier10) VALUES (%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u)", player->GetSession()->GetGuidLow(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            ChatHandler(player->GetSession()).PSendSysMessage("Parabens, agora você está com Battle Pass Ativo. Fale com o NPC novamente");
            CloseGossipMenuFor(player);
        }
        break;

        case 2:
        {
            if (player->HasItemCount(80000, 1))
            {
                player->DestroyItemCount(80000, 1, true);
                CharacterDatabase.PExecute("UPDATE character_battlepass SET bpvip = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por adquirir o EtMaXx VIP Battle Pass");
                CloseGossipMenuFor(player);
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você precisa de um EtMaXx VIP Battle Pass Mark para participar do Battle Pass VIP. Você pode adquirir essa Mark no site: www.etmaxx.com.br");
                CloseGossipMenuFor(player);
            }
        }
        break;

        case 4:
        {
                uint qty = player->GetItemCount(80001,true);
                points = points + (qty * 8);
                player->DestroyItemCount(80001, qty, true);
                CharacterDatabase.PExecute("UPDATE character_battlepass SET points = %u WHERE guid = %u", points, player->GetSession()->GetGuidLow());
                ChatHandler(player->GetSession()).PSendSysMessage("Battle Points adicionados ao seu Passe");
                ChatHandler(player->GetSession()).PSendSysMessage("Você tem %u Battle Points", points);
                CloseGossipMenuFor(player);
        }
        break;

        case 5:
        {
                uint qty = player->GetItemCount(80002,true);
                points = points + (qty * 40);
                player->DestroyItemCount(80002, qty, true);
                CharacterDatabase.PExecute("UPDATE character_battlepass SET points = %u WHERE guid = %u", points, player->GetSession()->GetGuidLow());
                ChatHandler(player->GetSession()).PSendSysMessage("Battle Points adicionados ao seu Passe");
                ChatHandler(player->GetSession()).PSendSysMessage("Você tem %u Battle Points", points);
                CloseGossipMenuFor(player);
        }
        break;

        case 6:
        {
                uint qty = player->GetItemCount(80003,true);
                points = points + (qty * 280);
                player->DestroyItemCount(80003, qty, true);
                CharacterDatabase.PExecute("UPDATE character_battlepass SET points = %u WHERE guid = %u", points, player->GetSession()->GetGuidLow());
                ChatHandler(player->GetSession()).PSendSysMessage("Battle Points adicionados ao seu Passe");
                ChatHandler(player->GetSession()).PSendSysMessage("Você tem %u Battle Points", points);
                CloseGossipMenuFor(player);
        }
        break;

        case 100:
        {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_engineering:30:30:-18:0|tEsta são as recompensas do Battle Pass deste mes:", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_engineering:30:30:-18:0|tBattle Pass Normal:", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:30:30:-18:0|t15 000 de Gold - 100 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_rune_08:30:30:-18:0|t2000 EtMaXx Mark - 200 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_jewelry_talisman_08:30:30:-18:0|t15 EtMaXx Mega Mark - 300 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:30:30:-18:0|t60 Emblem of Frost - 400 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:30:30:-18:0|t90 000 Honor Points - 500 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_championsgrace:30:30:-18:0|t4 EtMaXx Transmog Mark - 700 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_bijou_gold:30:30:-18:0|t5 EtMaXx Event Mark - 800 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_scroll_16:30:30:-18:0|tEtMaXx Profession Mark - 900 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_weapon_hand_18:30:30:-18:0|tEtMaXx Battle Pass Weapon - 1000 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_engineering:30:30:-18:0|t------------------", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_engineering:30:30:-18:0|tSe possuir o Battle Pass VIP além das recompensas normais você receberá:", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:30:30:-18:0|t30 000 de Gold - 100 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_weapon_hand_18:30:30:-18:0|tEtMaXx Battle Pass Weapon - 200 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:30:30:-18:0|t100 000 Honor Points  - 300 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:30:30:-18:0|t70 Emblem of Frost - 400 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:30:30:-18:0|t500 Arena Points - 500 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_scroll_16:30:30:-18:0|tEtMaXx Profession Mark - 600 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_championsgrace:30:30:-18:0|t4 EtMaXx Transmog Mark - 700 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_bijou_gold:30:30:-18:0|t5 EtMaXx Event Mark - 800 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bag_enchantedrunecloth:30:30:-18:0|t2 BAG VIP + EtMaXx Trocadorious Mark - 900 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_box_01:30:30:-18:0|tEtMaXx VIP Battle Pass + EtMaXx Blue Aura - 1000 Pontos", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/trade_engineering:30:30:-18:0|t------------------------", 100, 0);
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 5000, 0);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        break;

        case 3:
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT points FROM character_battlepass WHERE guid = %u", player->GetSession()->GetGuidLow());
            Field *fields = result->Fetch();
            points = fields[0].GetUInt32();
            ChatHandler(player->GetSession()).PSendSysMessage("Você tem um total de %u Battle Points", points);
            CloseGossipMenuFor(player);
        }
        break;

        case 5000: // Main menu
        {
            OnGossipHello(player, creature);
        }
        break;

        case 10: // Main menu
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 99000);
        }
        break;

        case 2000: // Resgate de Recompensas
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT bpvip, points, tier1, tier2, tier3, tier4, tier5, tier6, tier7, tier8, tier9, tier10, viptier1, viptier2, viptier3, viptier4, viptier5, viptier6, viptier7, viptier8, viptier9, viptier10 FROM character_battlepass WHERE guid = %u", player->GetSession()->GetGuidLow());
            Field *fields = result->Fetch();
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

            //CHECAGEM DE PONTOS
            if (points < 100)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você precisa de no minimo 100 Battle Points para resgater uma recompensa.");
                CloseGossipMenuFor(player);
            }

            //-------------------------------INICIO DA CHEGAGEM VIP------------------------------------
            if (points >= 100 && viptier1 == 0 && bpvip == 1)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:30:30:-18:0|t30 000 de Gold - 100 Pontos", 3100, 0);
            }

            if (points >= 200 && viptier2 == 0 && bpvip == 1)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_weapon_hand_18:30:30:-18:0|tEtMaXx Battle Pass Weapon - 200 Pontos", 3200, 0);
            }

            if (points >= 300 && viptier3 == 0 && bpvip == 1)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:30:30:-18:0|t100 000 Honor Points  - 300 Pontos", 3300, 0);
            }

            if (points >= 400 && viptier4 == 0 && bpvip == 1)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:30:30:-18:0|t70 Emblem of Frost - 400 Pontos", 3400, 0);
            }

            if (points >= 500 && viptier5 == 0 && bpvip == 1)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:30:30:-18:0|t500 Arena Points - 500 Pontos", 3500, 0);
            }

            if (points >= 600 && viptier6 == 0 && bpvip == 1)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_scroll_16:30:30:-18:0|tEtMaXx Profession Mark - 600 Pontos", 3600, 0);
            }

            if (points >= 700 && viptier7 == 0 && bpvip == 1)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_championsgrace:30:30:-18:0|t4 EtMaXx Transmog Mark - 700 Pontos", 3700, 0);
            }

            if (points >= 800 && viptier8 == 0 && bpvip == 1)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_bijou_gold:30:30:-18:0|t4 EtMaXx Event Mark - 800 Pontos", 3800, 0);
            }

            if (points >= 900 && viptier9 == 0 && bpvip == 1)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bag_enchantedrunecloth:30:30:-18:0|t2 BAG VIP  + EtMaXx Trocadorious Mark - 900 Pontos", 3900, 0);
            }

            if (points >= 1000 && viptier10 == 0 && bpvip == 1)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_qiraj_jewelglyphed:30:30:-18:0|tEtMaXx VIP Battle Pass + EtMaXx Blue Aura - 1000 Pontos", 31000, 0);
            }
            //-------------------------------FIM DA CHEGAGEM VIP------------------------------------

            //-------------------------------INICIO DA CHEGAGEM FREE------------------------------------
            if (points >= 100 && tier1 == 0)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_coin_01:30:30:-18:0|t15 000 de Gold - 100 Pontos", 2100, 0);
            }

            if (points >= 200 && tier2 == 0)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_rune_08:30:30:-18:0|t2 000 EtMaXx Mark - 200 Pontos", 2200, 0);
            }

            if (points >= 300 && tier3 == 0)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_jewelry_talisman_08:30:30:-18:0|t15 EtMaXx Mega Mark - 300 Pontos", 2300, 0);
            }

            if (points >= 400 && tier4 == 0)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_frostemblem_01:30:30:-18:0|t60 Emblem of Frost - 400 Pontos", 2400, 0);
            }

            if (points >= 500 && tier5 == 0)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_divinepurpose:30:30:-18:0|t90 000 Honor Points - 500 Pontos", 2500, 0);
            }

            if (points >= 700 && tier7 == 0)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_holy_championsgrace:30:30:-18:0|t4 EtMaXx Transmog Mark - 700 Pontos", 2700, 0);
            }

            if (points >= 800 && tier8 == 0)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_bijou_gold:30:30:-18:0|t5 EtMaXx Event Mark - 800 Pontos", 2800, 0);
            }

            if (points >= 900 && tier9 == 0)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_scroll_16:30:30:-18:0|tEtMaXx Profession Mark - 900 Pontos", 2900, 0);
            }

            if (points >= 1000 && tier10 == 0)
            {
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_weapon_hand_18:30:30:-18:0|tEtMaXx Battle Pass Weapon- 1000 Pontos", 21000, 0);
            }
            //-------------------------------FIM DA CHEGAGEM FREE------------------------------------
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        break;

        case 2100:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier1 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyMoney(150000000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 1 Resgatada (15 000 de Gold)");
            CloseGossipMenuFor(player);
        }
        break;

        case 2200:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier2 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(60000, 2000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 2 Resgatada (2000 EtMaXx mark)");
            CloseGossipMenuFor(player);
        }
        break;

        case 2300:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier3 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(60004, 15);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 3 Resgatada (15 EtMaXx Mega Mark)");
            CloseGossipMenuFor(player);
        }
        break;

        case 2400:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier4 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(49426, 60);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 4 Resgatada (60 Emblem of Frost)");
            CloseGossipMenuFor(player);
        }
        break;

        case 2500:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier5 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyHonorPoints(90000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 5 Resgatada (90 000 Honor Points)");
            CloseGossipMenuFor(player);
        }
        break;

        case 2700:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier7 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(80004, 4);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 7 Resgatada (4 EtMaXx Transmog Mark)");
            CloseGossipMenuFor(player);
        }
        break;

        case 2800:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier8 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(600600, 5);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 8 Resgatada ( EtMaXx Event Mark)");
            CloseGossipMenuFor(player);
        }
        break;

        case 2900:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier9 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(80009, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 9 Resgatada (EtMaXx Profession Mark)");
            CloseGossipMenuFor(player);
        }
        break;

        case 21000:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET tier10 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(800808, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do Tier 10 Resgatada (EtMaXx Battle Pass Weapon)");
            CloseGossipMenuFor(player);
        }
        break;

        case 3100:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier1 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyMoney(300000000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 1 Resgatada (30 000 de Gold)");
            CloseGossipMenuFor(player);
        }
        break;

        case 3200:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier2 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(800808, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do VIP Tier 2 Resgatada (EtMaXx Battle Pass Weapon)");
            CloseGossipMenuFor(player);
        }
        break;

        case 3300:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier3 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyHonorPoints(100000);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 3 Resgatada (100 000 Honor Points)");
            CloseGossipMenuFor(player);
        }
        break;

        case 3400:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier4 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(49426, 70);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 4 Resgatada (70 Emblem of Frost)");
            CloseGossipMenuFor(player);
        }
        break;

        case 3500:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier5 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->ModifyArenaPoints(500);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 5 Resgatada (500 Arena Points)");
            CloseGossipMenuFor(player);
        }
        break;

        case 3600:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier6 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(80009, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa do VIP Tier 6 Resgatada (EtMaXx Profession Mark)");
            CloseGossipMenuFor(player);
        }
        break;

        case 3700:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier7 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(80004, 4);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 7 Resgatada (4 EtMaXx Transmog Mark)");
            CloseGossipMenuFor(player);
        }
        break;

        case 3800:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier8 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(600600, 5);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 8 Resgatada (5 EtMaXx Event Mark)");
            CloseGossipMenuFor(player);
        }
        break;

        case 3900:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier9 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(34845, 2);
            player->AddItem(60005, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 9 Resgatada (2 Bag VIP)");
            CloseGossipMenuFor(player);
        }
        break;

        case 31000:
        {
            CharacterDatabase.PExecute("UPDATE character_battlepass SET viptier10 = 1 WHERE guid = %u", player->GetSession()->GetGuidLow());
            player->AddItem(80000, 1);
            player->AddItem(900806, 1);
            ChatHandler(player->GetSession()).PSendSysMessage("Recompensa VIP Tier 10 Resgatada (EtMaXx VIP Battle Pass + EtMaXx Blue Aura)");
            CloseGossipMenuFor(player);
        }
        break;
        }

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC transmog vendor                  	///////////////
///////////////////////////////////////////////////////////////////////////////////;
class etmaxx_transmog_vendor : public CreatureScript
{
public:
    etmaxx_transmog_vendor() : CreatureScript("etmaxx_transmog_vendor") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_bone_humanskull_01:30:30:-18:0|t50 Enemy Head + 30.000 Honor", 10, 0, "Tem certeza ?", 0, false);

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_frostemblem_01:30:30:-18:0|t30 Emblems of Frost", 20, 0, "Tem certeza ?", 0, false);

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_holy_championsbond:30:30:-18:0|t60 Badge of Justice", 40, 0, "Tem certeza ?", 0, false);

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/achievement_featsofstrength_gladiator_10:30:30:-18:0|t1200 de Arena Rating + 100 Arena Points", 30, 0, "Tem certeza ?", 0, false);

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_sword_26:30:30:-18:0|tEscolha seu Transmog", 50, 0);

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_sword_26:30:30:-18:0|tPegue um item invisivel (Para Transmog)", 60, 0);

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-18:0|tUpdate menu", 100, 0);

        SendGossipMenuFor(player, 800800, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
        case 100: // Main menu
        {
            OnGossipHello(player, creature);
        }
        break;

        case 10:
        {
            if (player->HasItemCount(600500, 50, true) && (player->GetHonorPoints() >= 30000))
            {
                player->DestroyItemCount(600500, 50, true);
                player->ModifyHonorPoints(-30000);
                player->AddItem(80004, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por adquirir uma EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }
            else
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVocê precisa de 50 enemy Head + 30.000 de Honor", 100, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }
        break;

        case 20:
        {
            if (player->HasItemCount(49426, 30, true))
            {
                player->DestroyItemCount(49426, 30, true);
                player->AddItem(80004, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por adquirir uma EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }
            else
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVocê precisa de 30 Emblem of Frost", 100, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }
        break;

        case 30:
        {
            if (player->HasItemCount(80004, 1))
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVocê só pode ter 1 EtMaXx Transmog Mark, gaste a sua para pegar outra", 100, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
            else if (player->GetArenaPersonalRating(0) >= 1200 && player->GetArenaPoints() >= 100)
            {
                player->ModifyArenaPoints(-100);
                player->AddItem(80004, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por adquirir uma EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }
            else
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVocê precisa de 1200 de Arena Rating + 100 Arena Points", 100, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }
        break;

        case 40:
        {
            if (player->HasItemCount(29434, 60, true))
            {
                player->DestroyItemCount(29434, 60, true);
                player->AddItem(80004, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Obrigado por adquirir uma EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }
            else
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVocê precisa de 60 Badge of Justice", 100, 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }
        break;

        //Menu Geral
        case 50:
        {
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_sword_27:30:30:-18:0|tArmas", 70, 0);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shirt_guildtabard_01:30:30:-18:0|tTabards", 13000, 0);

            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "---------------------------------------", 100, 0);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tVoltar...", 100, 0);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        break;

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
        }
        break;

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
        }
        break;

        case 600:
        {
            player->AddItem(100100, 1);
            CloseGossipMenuFor(player);
        }
        break;

        case 601:
        {
            player->AddItem(100103, 1);
            CloseGossipMenuFor(player);
        }
        break;

        case 602:
        {
            player->AddItem(100110, 1);
            CloseGossipMenuFor(player);
        }
        break;

        case 603:
        {
            player->AddItem(100101, 1);
            CloseGossipMenuFor(player);
        }
        break;

        case 604:
        {
            player->AddItem(100108, 1);
            CloseGossipMenuFor(player);
        }
        break;

        case 605:
        {
            player->AddItem(100105, 1);
            CloseGossipMenuFor(player);
        }
        break;

        case 606:
        {
            player->AddItem(100109, 1);
            CloseGossipMenuFor(player);
        }
        break;

        case 607:
        {
            player->AddItem(100104, 1);
            CloseGossipMenuFor(player);
        }
        break;

        case 608:
        {
            player->AddItem(100106, 1);
            CloseGossipMenuFor(player);
        }
        break;

        case 609:
        {
            player->AddItem(100111, 1);
            CloseGossipMenuFor(player);
        }
        break;

        case 610:
        {
            player->AddItem(100112, 1);
            CloseGossipMenuFor(player);
        }
        break;

        // Machados 2Hand
        case 1000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90500);
        }
        break;

        //Machados 1Hand
        case 2000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90501);
        }
        break;

        //Adagas
        case 3000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90502);
        }
        break;

        //Armas de Punho
        case 4000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90503);
        }
        break;

        //Maças 1Hand
        case 5000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90504);
        }
        break;

        //Maças 2Hand
        case 6000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90505);
        }
        break;

        //Espada 2Hand
        case 8000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90506);
        }
        break;

        //Espada 1Hand
        case 7000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90507);
        }
        break;

        //polearm
        case 9000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90508);
        }
        break;

        //Staff
        case 10000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90509);
        }
        break;

        //Bow
        case 11000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90510);
        }
        break;

        //Shield
        case 12000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90511);
        }
        break;

        //Tabards
        case 13000:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 90512);
        }
        break;

        case 100000:
        {
            if (action == 1) // Isso nunca deveria acontecer
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Error");
            }
        }
        break;
        }

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC EtMaXx Start                     	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_start : public CreatureScript
{
public:
    etmaxx_start() : CreatureScript("etmaxx_start") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();

        if (player->getClass() == CLASS_DEATH_KNIGHT && !player->HasItemCount(37836, 1, true) && player->GetAreaId() == 4342)
        {
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_deathknight_unholypresence:30:30:-18:0|tQuero fazer todas as Quests de DK", 300, 0, "Tem certeza ?", 0, false);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_deathknight_frostpresence:30:30:-18:0|tWOW INCRIVEL, JÁ CONHECO A LORE QUERO PULAR AS QUESTS DE DK !", 301, 0, "Tem certeza ?", 0, false);
            player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
            return true;
        }

        if (!player->HasItemCount(37836, 1, true) && player->getLevel() <= 60)
        {
            if (player->getClass() == CLASS_DRUID)
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/ability_druid_catform:30:30:-18:0|tWOW INCRIVEL, QUERO UPAR DE FERAL !", 100, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_forceofnature:30:30:-18:0|tWOW INCRIVEL, QUERO UPAR DE BALANCE !", 101, 0, "Tem certeza ?", 0, false);
                player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
            }
            else if (player->getClass() == CLASS_SHAMAN)
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_shaman_lavaburst:30:30:-18:0|tWOW INCRIVEL, QUERO UPAR DE ELEMENTAL !", 200, 0, "Tem certeza ?", 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/ability_shaman_stormstrike:30:30:-18:0|tWOW INCRIVEL, QUERO UPAR DE ENHANCEMENT !", 201, 0, "Tem certeza ?", 0, false);
                player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
            }
            else
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_box_02:30:30:-18:0|tWOW INCRIVEL, ME DA LOGO ESSES ITEMS !", 1, 0);
                player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
            }
        }
        else
        {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "Não posso mais lhe ajudar aventureiro, siga seu caminho...", 1000, 0);
            player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
        }

        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        if (sender == 1)
        {
            switch (player->getClass())
            {
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
                player->AddItem(60119, 50); // token lvlup
                player->AddItem(70506, 2); // Etmaxx Start
                player->AddItem(70310, 1); // Shirt Normal DPS
                player->AddQuest(sObjectMgr->GetQuestTemplate(80211), nullptr); 
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Guerreiro");
                CloseGossipMenuFor(player);
            }
            break;

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
                player->AddItem(70506, 2);
                player->AddItem(70307, 1);
                player->AddQuest(sObjectMgr->GetQuestTemplate(80208), nullptr);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Paladino");
                CloseGossipMenuFor(player);
            }
            break;

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
                player->AddItem(70506, 2);
                player->AddItem(70316, 1);
                player->AddQuest(sObjectMgr->GetQuestTemplate(80216), nullptr);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Ladino");
                CloseGossipMenuFor(player);
            }
            break;

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
                player->AddItem(70506, 2);
                player->AddItem(70301, 1);
                player->AddQuest(sObjectMgr->GetQuestTemplate(80205), nullptr);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Sacerdote");
                CloseGossipMenuFor(player);
            }
            break;

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
                player->AddItem(70506, 2);
                player->AddItem(70315, 1);
                player->AddQuest(sObjectMgr->GetQuestTemplate(80200), nullptr);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Mago");
                CloseGossipMenuFor(player);
            }
            break;

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
                player->AddItem(70506, 2);
                player->AddItem(70305, 1);
                player->AddQuest(sObjectMgr->GetQuestTemplate(80210), nullptr);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Bruxo");
                CloseGossipMenuFor(player);
            }
            break;

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
                player->AddItem(70506, 2);
                player->AddItem(70314, 1);
                player->AddQuest(sObjectMgr->GetQuestTemplate(80209), nullptr);
                ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Caçador");
                CloseGossipMenuFor(player);
            }
            break;
            }
        }

        switch (sender)
        {
            //Druid Feral
        case 100:
        {
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
            player->AddItem(70506, 2);
            player->AddItem(70311, 1);
            player->AddQuest(sObjectMgr->GetQuestTemplate(80202), nullptr);
            ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Druida");
            CloseGossipMenuFor(player);
        }
        break;

        //Druid Balance
        case 101:
        {
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
            player->AddItem(70506, 2);
            player->AddItem(70313, 1);
            player->AddQuest(sObjectMgr->GetQuestTemplate(80201), nullptr);
            ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Druida");
            CloseGossipMenuFor(player);
        }
        break;

        //Shaman Elemental
        case 200:
        {
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
            player->AddItem(70506, 2);
            player->AddItem(70304, 1);
            player->AddQuest(sObjectMgr->GetQuestTemplate(80213), nullptr);
            ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Xamã");
            CloseGossipMenuFor(player);
        }
        break;

        //Shaman Enhancement
        case 201:
        {
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
            player->AddItem(70506, 2);
            player->AddItem(70302, 1);
            player->AddQuest(sObjectMgr->GetQuestTemplate(80215), nullptr);
            ChatHandler(player->GetSession()).PSendSysMessage("Boa Sorte em sua jornada bravo Xamã");
            CloseGossipMenuFor(player);
        }
        break;

        case 300:
        {
            player->AddAura(30567, player);
            player->AddAura(30557, player);
            player->AddAura(30562, player);
            player->AddItem(37836, 1);
            player->AddItem(60119, 20);
            ChatHandler(player->GetSession()).PSendSysMessage("Você já está bem avançado em sua jornada, não precisa da minha ajuda. Receba apenas minha benção");
            CloseGossipMenuFor(player);
        }
        break;

        case 301:
        {
            int DKL = 1;

            if (player->getLevel() == 80)
            {
                DKL = 80;
            }
            else
            {
                DKL = 58;
            }
            player->SetLevel(DKL);
            player->learnSpell(53428);                                   //runeforging
            player->learnSpell(53441);                                   //runeforging
            player->learnSpell(53344);                                   //runeforging
            player->learnSpell(62158);                                   //runeforging
            player->learnSpell(33391);                                   //journeyman riding
            player->learnSpell(54586);                                   //runeforging credit
            player->learnSpell(48778);                                   //acherus deathcharger
            player->learnSpell(49998);                                   //Death Strike Rank 1 (Sem bug)
            player->removeSpell(45470, SPEC_MASK_ALL, false);            //Remove a DeathStrike Bugada (cura infinita)
            player->learnSkillRewardedSpells(776, 375);                  //Runeforging
            player->learnSkillRewardedSpells(960, 375);                  //Runeforging
            player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 38661, true);      //Greathelm of the Scourge Champion
            player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 38666, true);    //Plated Saronite Bracers
            player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 38668, true);     //The Plaguebringer's Girdle
            player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 38667, true);     //Bloodbane's Gauntlets of Command
            player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 38665, true);     //Saronite War Plate
            player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 38669, true);      //Engraved Saronite Legplates
            player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 38663, true); // Blood-Soaked Saronite Plated Spaulders
            player->EquipNewItem(EQUIPMENT_SLOT_FEET, 38670, true);      //Greaves of the Slaughter
            player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 38675, true);  //Signet of the Dark Brotherhood
            player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 38674, true);  //Soul Harvester's Charm
            player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 38671, true);   //Valanar's Signet Ring
            player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 38672, true);   // Keleseth's Signet Ring
            player->EquipNewItem(19, 10050, true);
            player->EquipNewItem(20, 10050, true);
            player->EquipNewItem(21, 10050, true);
            player->EquipNewItem(22, 10050, true);
            player->AddItem(39320, true); //Sky Darkener's Shroud of Blood
            player->AddItem(38664, true); //Sky Darkener's Shroud of the Unholy
            player->AddItem(39322, true); //Shroud of the North Wind
            player->AddItem(38632, true); //Greatsword of the Ebon Blade
            player->AddItem(6948, true);  //Hearthstone
            player->AddItem(38707, true); //Runed Soulblade
            player->AddItem(40483, true); //Insignia of the Scourge
            player->AddItem(70318, 1);

            // Quests
            if (player->GetQuestStatus(12657) == QUEST_STATUS_NONE) //The Might Of The Scourge
            {
                player->AddQuest(sObjectMgr->GetQuestTemplate(12657), nullptr);
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12657), false, player);
            }

            if (player->GetQuestStatus(12801) == QUEST_STATUS_NONE) //The Light of Dawn
            {
                player->AddQuest(sObjectMgr->GetQuestTemplate(12801), nullptr);
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12801), false, player);
            }

            if (player->GetTeamId() == TEAM_ALLIANCE && player->GetQuestStatus(13188) == QUEST_STATUS_NONE) //Where Kings Walk
                player->AddQuest(sObjectMgr->GetQuestTemplate(13188), nullptr);
            else if (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(13189) == QUEST_STATUS_NONE) //Saurfang's Blessing
                player->AddQuest(sObjectMgr->GetQuestTemplate(13189), nullptr);

            player->AddAura(30567, player);
            player->AddAura(30557, player);
            player->AddAura(30562, player);
            player->AddItem(33478, 1);
            player->AddItem(37836, 1);
            player->AddItem(60119, 10);
            player->AddQuest(sObjectMgr->GetQuestTemplate(80217), nullptr);

            ChatHandler(player->GetSession()).PSendSysMessage("Você já está bem avançado em sua jornada, não precisa da minha ajuda. Receba apenas minha benção");

            // Teleport
            if (player->GetTeamId() == TEAM_ALLIANCE)
                player->TeleportTo(0, -8833.37f, 628.62f, 94.00f, 1.06f); //Stormwind
            else
                player->TeleportTo(1, 1569.59f, -4397.63f, 16.06f, 0.54f); //Orgrimmar

            ObjectAccessor::SaveAllPlayers(); //Save
        }
        break;

        case 1000:
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Só é possivel usar o EtMaXx Start uma unica vez");
            CloseGossipMenuFor(player);
        }
        break;
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC de Troca de Tabard               	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_tabard : public CreatureScript
{
public:
    etmaxx_tabard() : CreatureScript("etmaxx_tabard") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        ClearGossipMenuFor(player);
        bool acheitabardfaccaooposta = false;

        // Se o player for alliance, verificar se ele tem tabard horda na bag
        if (player->GetTeamId() == TEAM_ALLIANCE)
        {
            for (uint8 i = 0; i < 100; ++i)
            {
                if (player->HasItemCount(tabardHorda[i], 1, true))
                    acheitabardfaccaooposta = true;
            }
        };

        // Se o player for horda, verificar se ele tem tabard alliancce na bag
        if (player->GetTeamId() == TEAM_HORDE)
        {
            for (uint8 i = 0; i < 96; ++i)
            {
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
            if (player->getRace() == RACE_BLOODELF)
            {
                if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_DEATH_KNIGHT)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60176, 0);
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60168, 0);
                }

                if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60172, 0);
                }

                if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_HUNTER)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60164, 0);
                }

                if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60160, 0);
                }
            }
            else if (player->getRace() == RACE_ORC)
            {
                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60096, 0);
                }

                if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_WARLOCK)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60092, 0);
                }

                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60088, 0);
                }

                if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_SHAMAN)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60084, 0);
                }

                if (player->getClass() == CLASS_SHAMAN)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60080, 0);
                }
            }
            else if (player->getRace() == RACE_TROLL)
            {
                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60136, 0);
                }

                if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_MAGE)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60132, 0);
                }

                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60128, 0);
                }

                if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_SHAMAN)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60124, 0);
                }

                if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_PRIEST)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60275, 0);
                }
            }
            else if (player->getRace() == RACE_UNDEAD_PLAYER)
            {
                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60116, 0);
                }

                if (player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60112, 0);
                }

                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60108, 0);
                }

                if (player->getClass() == CLASS_ROGUE)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60104, 0);
                }

                if (player->getClass() == CLASS_PRIEST)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60100, 0);
                }
            }
            else if (player->getRace() == RACE_TAUREN)
            {
                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_DRUID)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60156, 0);
                }

                if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_DRUID)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60152, 0);
                }

                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60148, 0);
                }

                if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_DRUID || player->getClass() == CLASS_HUNTER)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60144, 0);
                }

                if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_DRUID)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60140, 0);
                }
            }

            if (player->getRace() == RACE_HUMAN)
            {
                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_PALADIN)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60196, 0);
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60188, 0);
                }

                if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60192, 0);
                }

                if (player->getClass() == CLASS_ROGUE)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60184, 0);
                }

                if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60180, 0);
                }
            }
            else if (player->getRace() == RACE_DWARF)
            {
                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_PALADIN)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60216, 0);
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60208, 0);
                }

                if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60212, 0);
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60200, 0);
                }

                if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_HUNTER)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60204, 0);
                }
            }
            else if (player->getRace() == RACE_GNOME)
            {
                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60252, 0);
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60244, 0);
                }

                if (player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60248, 0);
                }

                if (player->getClass() == CLASS_ROGUE)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60240, 0);
                }
            }
            else if (player->getRace() == RACE_DRAENEI)
            {
                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_PALADIN)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60272, 0);
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60264, 0);
                }

                if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_SHAMAN)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60268, 0);
                }

                if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_HUNTER)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60260, 0);
                }

                if (player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_SHAMAN)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60256, 0);
                }
            }
            else if (player->getRace() == RACE_NIGHTELF)
            {
                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_DRUID)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60236, 0);
                }

                if (player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_DRUID)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60232, 0);
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60220, 0);
                }

                if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60228, 0);
                }

                if (player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_DRUID)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60224, 0);
                }
            }
        }

        SendGossipMenuFor(player, 800804, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
        case 60180:
        case 60200:
        case 60220:
        case 60240:
        case 60256:
        case 60080:
        case 60100:
        case 60275:
        case 60140:
        case 60160:
        case 60184:
        case 60204:
        case 60224:
        case 60244:
        case 60260:
        case 60084:
        case 60104:
        case 60124:
        case 60144:
        case 60164:
        case 60188:
        case 60208:
        case 60228:
        case 60248:
        case 60264:
        case 60088:
        case 60108:
        case 60128:
        case 60148:
        case 60168:
        case 60192:
        case 60212:
        case 60232:
        case 60252:
        case 60268:
        case 60092:
        case 60112:
        case 60132:
        case 60152:
        case 60172:
        case 60196:
        case 60216:
        case 60236:
        case 60272:
        case 60096:
        case 60116:
        case 60136:
        case 60156:
        case 60176:
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

    void addTabard(uint32 itemid, Player *player)
    {
        player->AddItem(itemid, 1);
    }

    bool destroyTabard(Player *player)
    {
        // Se o player for alliance, verificar se ele tem tabard horda na bag
        if (player->GetTeamId() == TEAM_ALLIANCE)
        {
            for (uint8 i = 0; i < 100; ++i)
            {
                if (player->HasItemCount(tabardHorda[i], 1, true))
                {
                    player->DestroyItemCount(tabardHorda[i], 1, true);
                    return true;
                }
            }
        };

        // Se o player for hprda, verificar se ele tem tabard alliancce na bag
        if (player->GetTeamId() == TEAM_HORDE)
        {
            for (uint8 i = 0; i < 96; ++i)
            {
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
/////////////                 EtMaXx Event Trocadorious            	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_event : public CreatureScript
{
public:
    etmaxx_event() : CreatureScript("etmaxx_event") {}

    //int skillid[11] = {SKILL_BLACKSMITHING, SKILL_TAILORING, SKILL_LEATHERWORKING, SKILL_ENGINEERING, SKILL_ENCHANTING, SKILL_ALCHEMY, SKILL_MINING, SKILL_HERBALISM, SKILL_SKINNING, SKILL_INSCRIPTION, SKILL_JEWELCRAFTING};
    //int skillid2[3] = { SKILL_FISHING, SKILL_FIRST_AID, SKILL_COOKING };

    bool MarkCheck(Player *player, int count, int skill)
    {
        if (player->HasSkill(skill))
        {
            player->GetSession()->SendNotification("Você já tem essa profissão");
            CloseGossipMenuFor(player);
            return false;
        }

        if (player->HasItemCount(600600, count, true))
        {
            player->DestroyItemCount(600600, count, true);
            return true;
        }
        else
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Você não tem EtMaXx Event Mark suficientes ou uma EtMaXx Profession Token.");
            CloseGossipMenuFor(player);
            return false;
        }
    }

    bool ProfTokenCheck(Player *player, int count, int choice)
    {
        if (player->HasSkill(choice))
        {
            player->GetSession()->SendNotification("Você já tem essa profissão");
            CloseGossipMenuFor(player);
            return false;
        }

        if (player->HasItemCount(80009, count, true))
        {
            player->DestroyItemCount(80009, count, true);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool LearnProfession(Player *player, int skill)
    {
        learn_commandscript::HandleLearnSkillRecipesHelper(player, skill);
        player->SetSkill(skill, player->GetSkillStep(skill), 450, 450);
        return true;
    }

    static bool HasFreeProfession(Player *player, SkillType Skill)
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
            if (SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i))
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

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();

        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_bag_17:35:35:-30:0|tResgate sua Recompensa", 100, 0);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "----------------------------------------", 9999, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:35:35:-30:0|tUpdate menu", 9999, 0);

        SendGossipMenuFor(player, 800805, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
        case 9999: // Main menu
        {
            OnGossipHello(player, creature);
        }
        break;

        case 100:
        {
            AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_book_11:35:35:-25:0|tProfissão Full - 3 Event Mark", 1000, 0, "Tem certeza ?", 0, false);                           // 03 Event Mark                                       	// 03 Event Mark
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
        }
        break;

        case 1:
        {
            if (player->GetTeamId() == TEAM_HORDE)
            {
                player->GetSession()->SendListInventory(creature->GetGUID(), 91500);
            }
            else
            {
                player->GetSession()->SendListInventory(creature->GetGUID(), 92500);
            }
        }
        break;

        case 2:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 93500);
        }
        break;

        case 3:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 65001);
        }
        break;

        case 1000:
        {
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
        }
        break;

        case 2000:
        {
            if (MarkCheck(player, 2, 2000))
            {
                player->ModifyHonorPoints(10000);
                ChatHandler(player->GetSession()).PSendSysMessage("10.000 pontos de honra recebidos");
                CloseGossipMenuFor(player);
            }
        }
        break;

        case 3000:
        {
            if (MarkCheck(player, 2, 3000))
            {
                player->ModifyArenaPoints(200);
                ChatHandler(player->GetSession()).PSendSysMessage("200 pontos de Arena recebidos");
                CloseGossipMenuFor(player);
            }
        }
        break;

        case 4000:
        {
            if (MarkCheck(player, 2, 4000))
            {
                player->AddItem(49426, 30);
                ChatHandler(player->GetSession()).PSendSysMessage("30 Emblem of Frost recebidos");
                CloseGossipMenuFor(player);
            }
        }
        break;

        case 5000:
        {
            if (MarkCheck(player, 4, 5000))
            {
                player->AddItem(80004, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Transmog Mark");
                CloseGossipMenuFor(player);
            }
        }
        break;

        case 6000:
        {
            if (MarkCheck(player, 5, 6000))
            {
                player->AddItem(80005, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Tabard Mark recebida");
                CloseGossipMenuFor(player);
            }
        }
        break;

        case 7000:
        {
            if (MarkCheck(player, 7, 7000))
            {
                player->AddItem(47395, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Mount Mark recebida");
                CloseGossipMenuFor(player);
            }
        }
        break;

        case 8000:
        {
            if (MarkCheck(player, 8, 8000))
            {
                player->AddItem(80006, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Sanctified Mark recebida");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //BS
        case 10000:
        {
            if (HasFreeProfession(player, SKILL_BLACKSMITHING))
            {
                if (ProfTokenCheck(player, 1, SKILL_BLACKSMITHING))
                {
                    LearnProfession(player, SKILL_BLACKSMITHING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_BLACKSMITHING))
                {
                    LearnProfession(player, SKILL_BLACKSMITHING);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //Jewel
        case 20000:
        {
            if (HasFreeProfession(player, SKILL_JEWELCRAFTING))
            {
                if (ProfTokenCheck(player, 1, SKILL_JEWELCRAFTING))
                {
                    LearnProfession(player, SKILL_JEWELCRAFTING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_JEWELCRAFTING))
                {
                    LearnProfession(player, SKILL_JEWELCRAFTING);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //Tailor
        case 30000:
        {
            if (HasFreeProfession(player, SKILL_TAILORING))
            {
                if (ProfTokenCheck(player, 1, SKILL_TAILORING))
                {
                    LearnProfession(player, SKILL_TAILORING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_TAILORING))
                {
                    LearnProfession(player, SKILL_TAILORING);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //Enchanting
        case 40000:
        {
            if (HasFreeProfession(player, SKILL_ENCHANTING))
            {
                if (ProfTokenCheck(player, 1, SKILL_ENCHANTING))
                {
                    LearnProfession(player, SKILL_ENCHANTING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_ENCHANTING))
                {
                    LearnProfession(player, SKILL_ENCHANTING);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //Alchemy
        case 50000:
        {
            if (HasFreeProfession(player, SKILL_ALCHEMY))
            {
                if (ProfTokenCheck(player, 1, SKILL_ALCHEMY))
                {
                    LearnProfession(player, SKILL_ALCHEMY);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_ALCHEMY))
                {
                    LearnProfession(player, SKILL_ALCHEMY);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //Inscription
        case 60000:
        {
            if (HasFreeProfession(player, SKILL_INSCRIPTION))
            {
                if (ProfTokenCheck(player, 1, SKILL_INSCRIPTION))
                {
                    LearnProfession(player, SKILL_INSCRIPTION);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_INSCRIPTION))
                {
                    LearnProfession(player, SKILL_INSCRIPTION);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //Engineering
        case 70000:
        {
            if (HasFreeProfession(player, SKILL_ENGINEERING))
            {
                if (ProfTokenCheck(player, 1, SKILL_ENGINEERING))
                {
                    LearnProfession(player, SKILL_ENGINEERING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_ENGINEERING))
                {
                    LearnProfession(player, SKILL_ENGINEERING);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //leatherworking
        case 80000:
        {
            if (HasFreeProfession(player, SKILL_LEATHERWORKING))
            {
                if (ProfTokenCheck(player, 1, SKILL_LEATHERWORKING))
                {
                    LearnProfession(player, SKILL_LEATHERWORKING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_LEATHERWORKING))
                {
                    LearnProfession(player, SKILL_LEATHERWORKING);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //Mining
        case 90000:
        {
            if (HasFreeProfession(player, SKILL_MINING))
            {
                if (ProfTokenCheck(player, 1, SKILL_MINING))
                {
                    LearnProfession(player, SKILL_MINING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_MINING))
                {
                    LearnProfession(player, SKILL_MINING);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //Skinning
        case 100000:
        {
            if (HasFreeProfession(player, SKILL_SKINNING))
            {
                if (ProfTokenCheck(player, 1, SKILL_SKINNING))
                {
                    LearnProfession(player, SKILL_SKINNING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_SKINNING))
                {
                    LearnProfession(player, SKILL_SKINNING);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //Herbalism
        case 110000:
        {
            if (HasFreeProfession(player, SKILL_HERBALISM))
            {
                if (ProfTokenCheck(player, 1, SKILL_HERBALISM))
                {
                    LearnProfession(player, SKILL_HERBALISM);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_HERBALISM))
                {
                    LearnProfession(player, SKILL_HERBALISM);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //Cooking
        case 120000:
        {
            if (HasFreeProfession(player, SKILL_COOKING))
            {
                if (ProfTokenCheck(player, 1, SKILL_COOKING))
                {
                    LearnProfession(player, SKILL_COOKING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_COOKING))
                {
                    LearnProfession(player, SKILL_COOKING);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //Fishing
        case 130000:
        {
            if (HasFreeProfession(player, SKILL_FISHING))
            {
                if (ProfTokenCheck(player, 1, SKILL_FISHING))
                {
                    LearnProfession(player, SKILL_FISHING);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_FISHING))
                {
                    LearnProfession(player, SKILL_FISHING);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;

        //First Aid
        case 140000:
        {
            if (HasFreeProfession(player, SKILL_FIRST_AID))
            {
                if (ProfTokenCheck(player, 1, SKILL_FIRST_AID))
                {
                    LearnProfession(player, SKILL_FIRST_AID);
                    CloseGossipMenuFor(player);
                }
                else if (MarkCheck(player, 3, SKILL_FIRST_AID))
                {
                    LearnProfession(player, SKILL_FIRST_AID);
                    CloseGossipMenuFor(player);
                }
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você não tem mais espaço para novas profissões");
                CloseGossipMenuFor(player);
            }
        }
        break;
        }

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Ladrão de Ulduar                 	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_startset : public CreatureScript
{
public:
    etmaxx_startset() : CreatureScript("etmaxx_startset") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        ClearGossipMenuFor(player);

        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_rune_09:35:35:-25:0|tMe da logo essa token", 100, 0, "Tem certeza que vai gastar 500 EtMaXx Mark e 2 EtMaXx Mega Mark ?", 0, false);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/inv_misc_bag_10:35:35:-25:0|tQuero dar uma olhada no que você tem ai.", 200, 0);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "----------------------------------------", 9999, 0);
        AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:35:35:-25:0|tUpdate Menu", 9999, 0);

        SendGossipMenuFor(player, 800806, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
        case 100:
        {
            if (player->HasItemCount(60000, 500) && player->HasItemCount(60004, 2))
            {
                player->DestroyItemCount(60000, 500, true);
                player->DestroyItemCount(60004, 2, true);
                player->AddItem(800801, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("Você Recebeu 1 EtMaXx Tier 8 Token, fale com o NPC novamente para trocar por uma parte Tier 8");
                CloseGossipMenuFor(player);
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Você precisa de 1500 EtMaXx Mark + 5 EtMaXx Mega Mark para pegar uma EtMaXx Tier 8 Token");
                CloseGossipMenuFor(player);
            }
        }
        break;

        case 200: // Main menuu
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 80002);
        }
        break;

        case 9999: // Main menu
        {
            OnGossipHello(player, creature);
        }
        break;
        }

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Keystone                         	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_keystone : public CreatureScript
{
public:
    etmaxx_keystone() : CreatureScript("etmaxx_keystone") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        ClearGossipMenuFor(player);

        // 658 = Pit of Saron
        // 668 = Halls of Reflection
        // 632 = Forge of Souls

        if (player->GetMapId() == 658)
        {
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

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
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
        }
        break;

        case 9999: // Main menu
        {
            OnGossipHello(player, creature);
        }
        break;
        }

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Migração DK Fix                  	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_dk : public CreatureScript
{
public:
    etmaxx_dk() : CreatureScript("etmaxx_dk") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();

        if (player->getClass() == CLASS_DEATH_KNIGHT && !player->HasItemCount(37836, 1, true))
        {
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_deathknight_frostpresence:30:30:-18:0|tCompletar todas as Quests de DK", 301, 0, "Tem certeza ?", 0, false);
            player->SEND_GOSSIP_MENU(800802, creature->GetGUID());
            return true;
        }
        else
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Eu só falo com Cavaleiros da Morte!");
            CloseGossipMenuFor(player);
        }

        return true;
    }

    bool OnGossipSelect(Player *player, Creature * /*creature*/, uint32 sender, uint32 /*action*/)
    {
        switch (sender)
        {
        case 301:
        {
            player->SetLevel(80);
            player->learnSpell(53428);                                   //runeforging
            player->learnSpell(53441);                                   //runeforging
            player->learnSpell(53344);                                   //runeforging
            player->learnSpell(62158);                                   //runeforging
            player->learnSpell(33391);                                   //journeyman riding
            player->learnSpell(54586);                                   //runeforging credit
            player->learnSpell(48778);                                   //acherus deathcharger
            player->learnSpell(49998);                                   //Death Strike Rank 1 (Sem bug)
            player->removeSpell(45470, SPEC_MASK_ALL, false);            //Remove a DeathStrike Bugada (cura infinita)
            player->learnSkillRewardedSpells(776, 375);                  //Runeforging
            player->learnSkillRewardedSpells(960, 375);                  //Runeforging
            player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 38661, true);      //Greathelm of the Scourge Champion
            player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 38666, true);    //Plated Saronite Bracers
            player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 38668, true);     //The Plaguebringer's Girdle
            player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 38667, true);     //Bloodbane's Gauntlets of Command
            player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 38665, true);     //Saronite War Plate
            player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 38669, true);      //Engraved Saronite Legplates
            player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 38663, true); // Blood-Soaked Saronite Plated Spaulders
            player->EquipNewItem(EQUIPMENT_SLOT_FEET, 38670, true);      //Greaves of the Slaughter
            player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 38675, true);  //Signet of the Dark Brotherhood
            player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 38674, true);  //Soul Harvester's Charm
            player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 38671, true);   //Valanar's Signet Ring
            player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 38672, true);   // Keleseth's Signet Ring
            player->EquipNewItem(19, 10050, true);
            player->EquipNewItem(20, 10050, true);
            player->EquipNewItem(21, 10050, true);
            player->EquipNewItem(22, 10050, true);
            player->AddItem(39320, true); //Sky Darkener's Shroud of Blood
            player->AddItem(38664, true); //Sky Darkener's Shroud of the Unholy
            player->AddItem(39322, true); //Shroud of the North Wind
            player->AddItem(38632, true); //Greatsword of the Ebon Blade
            player->AddItem(6948, true);  //Hearthstone
            player->AddItem(38707, true); //Runed Soulblade
            player->AddItem(40483, true); //Insignia of the Scourge

            // Quests
            if (player->GetQuestStatus(12657) == QUEST_STATUS_NONE) //The Might Of The Scourge
            {
                player->AddQuest(sObjectMgr->GetQuestTemplate(12657), nullptr);
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12657), false, player);
            }
            if (player->GetQuestStatus(12801) == QUEST_STATUS_NONE) //The Light of Dawn
            {
                player->AddQuest(sObjectMgr->GetQuestTemplate(12801), nullptr);
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12801), false, player);
            }
            if (player->GetTeamId() == TEAM_ALLIANCE && player->GetQuestStatus(13188) == QUEST_STATUS_NONE)
            {
                player->AddQuest(sObjectMgr->GetQuestTemplate(13188), nullptr);
                player->RewardQuest(sObjectMgr->GetQuestTemplate(13188), false, player);
            }
            else if (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(13189) == QUEST_STATUS_NONE)
            { //Saurfang's Blessing
                player->AddQuest(sObjectMgr->GetQuestTemplate(13189), nullptr);
                player->RewardQuest(sObjectMgr->GetQuestTemplate(13189), false, player);
            }
            player->AddItem(37836, 1);
            player->TeleportTo(571, 5741.36f, 626.982f, 648.354f, 0.28f); //Dalaran

            ObjectAccessor::SaveAllPlayers(); //Save
        }
        break;
        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Profissão Dalaran Jewel         	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_jc : public CreatureScript
{
public:
    etmaxx_jc() : CreatureScript("etmaxx_jc") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_misc_conjuremanajewel:30:30:-18:0|tReagentes", 1, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 1", 2, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 2", 3, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 3", 4, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        switch (sender)
        {
        case 1:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50077);
        }
        break;

        case 2:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50064);
        }
        break;

        case 3:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50065);
        }
        break;

        case 4:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50079);
        }
        break;
        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Profissão Dalaran Leather       	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_lw : public CreatureScript
{
public:
    etmaxx_lw() : CreatureScript("etmaxx_lw") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_armorkit_17:30:30:-18:0|tReagentes 1", 1, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_armorkit_17:30:30:-18:0|tReagentes 2", 2, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 1", 3, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 2", 4, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 3", 5, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        switch (sender)
        {
        case 1:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50066);
        }
        break;

        case 2:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50067);
        }
        break;

        case 3:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50051);
        }
        break;

        case 4:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50052);
        }
        break;

        case 5:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50053);
        }
        break;
        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Profissão Dalaran tailor         	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_tl : public CreatureScript
{
public:
    etmaxx_tl() : CreatureScript("etmaxx_tl") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/trade_tailoring:30:30:-18:0|tReagentes 1", 1, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/trade_tailoring:30:30:-18:0|tReagentes  2", 2, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 1", 3, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 2", 4, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        switch (sender)
        {
        case 1:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50068);
        }
        break;

        case 2:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50069);
        }
        break;

        case 3:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50054);
        }
        break;

        case 4:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50055);
        }
        break;
        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Profissão Dalaran BS           	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_bs : public CreatureScript
{
public:
    etmaxx_bs() : CreatureScript("etmaxx_bs") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/trade_blacksmithing:30:30:-18:0|tReagentes 1", 1, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/trade_blacksmithing:30:30:-18:0|tReagentes 2", 2, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 1", 3, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 2", 4, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        switch (sender)
        {
        case 1:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50072);
        }
        break;

        case 2:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50073);
        }
        break;

        case 3:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50057);
        }
        break;

        case 4:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50059);
        }
        break;
        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Profissão Dalaran Enchanting     	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_ec : public CreatureScript
{
public:
    etmaxx_ec() : CreatureScript("etmaxx_ec") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/trade_engraving:30:30:-18:0|tReagentes 1", 1, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 2", 2, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 1", 3, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        switch (sender)
        {
        case 1:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50076);
        }
        break;

        case 2:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50062);
        }
        break;

        case 3:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50063);
        }
        break;
        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Profissão Dalaran Engineering  	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_eng : public CreatureScript
{
public:
    etmaxx_eng() : CreatureScript("etmaxx_eng") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/trade_engineering:30:30:-18:0|tReagentes 1", 1, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/trade_engineering:30:30:-18:0|tReagentes 2", 2, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 1", 3, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        switch (sender)
        {
        case 1:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50070);
        }
        break;

        case 2:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50071);
        }
        break;

        case 3:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50056);
        }
        break;
        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Profissão Dalaran Cooking     	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_cook : public CreatureScript
{
public:
    etmaxx_cook() : CreatureScript("etmaxx_cook") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_food_15:30:30:-18:0|tReagentes 1", 1, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 1", 2, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        switch (sender)
        {
        case 1:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50074);
        }
        break;

        case 2:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50060);
        }
        break;
        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Profissão Dalaran Alchemy     	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_alc : public CreatureScript
{
public:
    etmaxx_alc() : CreatureScript("etmaxx_alc") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/trade_alchemy:30:30:-18:0|tReagentes 1", 1, 0);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tRecipes 1", 2, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        switch (sender)
        {
        case 1:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50075);
        }
        break;

        case 2:
        {
            player->GetSession()->SendListInventory(creature->GetGUID(), 50061);
        }
        break;
        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Buffs em ICC                    	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_buff : public CreatureScript
{
public:
    etmaxx_buff() : CreatureScript("etmaxx_buff") {}

    uint itemid1 = 0;
    uint qty1 = 0;
    uint qtytotal1 = 0;

    uint itemid2 = 0;
    uint qty2 = 0;
    uint qtytotal2 = 0;

    uint itemid3 = 0;
    uint qty3 = 0;
    uint qtytotal3 = 0;

    uint itemid4 = 0;
    uint qty4 = 0;
    uint qtytotal4 = 0;

    uint itemid5 = 0;
    uint qty5 = 0;
    uint qtytotal5 = 0;

    uint itemid6 = 0;
    uint qty6 = 0;
    uint qtytotal6 = 0;

    uint itemid7 = 0;
    uint qty7 = 0;
    uint qtytotal7 = 0;

    uint itemid8 = 0;
    uint qty8 = 0;
    uint qtytotal8 = 0;

    uint itemid9 = 0;
    uint qty9 = 0;

    uint spellid1 = 0;
    uint autocast1 = 0;

    uint spellid2 = 0;
    uint autocast2 = 0;

    uint spellid3 = 0;
    uint autocast3 = 0;
    
    uint spellid4 = 0;
    uint autocast4 = 0;

    char tempo;
    
    

    bool OnGossipHello(Player *player, Creature *creature)
    {
        //EtMaXx Mark
        QueryResult result1 = WorldDatabase.PQuery("SELECT itemID, qty, qtytotal FROM mod_icc_buff WHERE id = 1" );
        if (result1)
        {
            Field *fields1 = result1->Fetch();
            itemid1 = fields1[0].GetUInt32();
            qty1 = fields1[1].GetUInt32();
            qtytotal1 = fields1[2].GetUInt32();
        }

        //EtMaXx Mega Mark
        QueryResult result2 = WorldDatabase.PQuery("SELECT itemID, qty, qtytotal FROM mod_icc_buff WHERE id = 2" );
        if (result2)
        {
            Field *fields2 = result2->Fetch();
            itemid2 = fields2[0].GetUInt32();
            qty2 = fields2[1].GetUInt32();
            qtytotal2 = fields2[2].GetUInt32();
        }

        //Enemy Head
        QueryResult result3 = WorldDatabase.PQuery("SELECT itemID, qty, qtytotal FROM mod_icc_buff WHERE id = 3" );
        if (result3)
        {
            Field *fields3 = result3->Fetch();
            itemid3 = fields3[0].GetUInt32();
            qty3 = fields3[1].GetUInt32();
            qtytotal3 = fields3[2].GetUInt32();
        }

        //Emblem of Frost
        QueryResult result4 = WorldDatabase.PQuery("SELECT itemID, qty, qtytotal FROM mod_icc_buff WHERE id = 4" );
        if (result4)
        {
            Field *fields4 = result4->Fetch();
            itemid4 = fields4[0].GetUInt32();
            qty4 = fields4[1].GetUInt32();
            qtytotal4 = fields4[2].GetUInt32();
        }

        //EtMaXx Event Mark
        QueryResult result5 = WorldDatabase.PQuery("SELECT itemID, qty, qtytotal FROM mod_icc_buff WHERE id = 5" );
        if (result5)
        {
            Field *fields5 = result5->Fetch();
            itemid5 = fields5[0].GetUInt32();
            qty5 = fields5[1].GetUInt32();
            qtytotal5 = fields5[2].GetUInt32();
        }

        //Badge of Justice
        QueryResult result6 = WorldDatabase.PQuery("SELECT itemID, qty, qtytotal FROM mod_icc_buff WHERE id = 6" );
        if (result6)
        {
            Field *fields6 = result6->Fetch();
            itemid6 = fields6[0].GetUInt32();
            qty6 = fields6[1].GetUInt32();
            qtytotal6 = fields6[2].GetUInt32();
        }

        //Gold
        QueryResult result7 = WorldDatabase.PQuery("SELECT itemID, qty, qtytotal FROM mod_icc_buff WHERE id = 7" );
        if (result7)
        {
            Field *fields7 = result7->Fetch();
            itemid7 = fields7[0].GetUInt32();
            qty7 = fields7[1].GetUInt32();
            qtytotal7 = fields7[2].GetUInt32();
        }

        //Sacrificios
        QueryResult result8 = WorldDatabase.PQuery("SELECT itemID, qty, qtytotal FROM mod_icc_buff WHERE id = 8" );
        if (result8)
        {
            Field *fields8 = result8->Fetch();
            itemid8 = fields8[0].GetUInt32();
            qty8 = fields8[1].GetUInt32();
            qtytotal8 = fields8[2].GetUInt32();
        }

        //Buff Fortitude of Frost 62650
        QueryResult buff1 = WorldDatabase.PQuery("SELECT spell, autocast FROM spell_area WHERE area = 4812 AND spell = 62650" );
        if (buff1)
        {
            Field *fields8 = buff1->Fetch();
            spellid1 = fields8[0].GetUInt32();
            autocast1 = fields8[1].GetUInt32();
        }

        //Buff Resilience of nature 62670
        QueryResult buff2 = WorldDatabase.PQuery("SELECT spell, autocast FROM spell_area WHERE area = 4812 AND spell = 62670" );
        if (buff2)
        {
            Field *fields8 = buff2->Fetch();
            spellid2 = fields8[0].GetUInt32();
            autocast2 = fields8[1].GetUInt32();
        }

        //Buff Speed of Invention 62671
        QueryResult buff3 = WorldDatabase.PQuery("SELECT spell, autocast FROM spell_area WHERE area = 4812 AND spell = 62671" );
        if (buff3)
        {
            Field *fields8 = buff3->Fetch();
            spellid3 = fields8[0].GetUInt32();
            autocast3 = fields8[1].GetUInt32();
        }

        //Buff Fury of the Storm 62702
        QueryResult buff4 = WorldDatabase.PQuery("SELECT spell, autocast FROM spell_area WHERE area = 4812 AND spell = 62702" );
        if (buff4)
        {
            Field *fields8 = buff4->Fetch();
            spellid4 = fields8[0].GetUInt32();
            autocast4 = fields8[1].GetUInt32();
        }

        //Buff Ativo ?
        QueryResult result9 = WorldDatabase.PQuery("SELECT itemID, qty FROM mod_icc_buff WHERE id = 9" );
        if (result9)
        {
            Field *fields8 = result9->Fetch();
            itemid9 = fields8[0].GetUInt32();
            qty9 = fields8[1].GetUInt32();
        }

        player->PlayerTalkClass->ClearMenus();
        
        if(autocast1 == 0 && autocast2 == 0 && autocast3 == 0 && autocast4 == 0){

            if (qty1 < qtytotal1 && player->HasItemCount(itemid1,1000)){
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_rune_08:30:30:-18:0|tDoar EtMaXx Mark", 1, 0, "Será descontado 1.000 EtMaXx Marks, Tem Certeza?", 0, false);
            }
        
            if (qty2 < qtytotal2 && player->HasItemCount(itemid2,10)){
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_jewelry_talisman_08:30:30:-18:0|tDoar EtMaXx Mega Mark", 2, 0, "Será Descontado 10 EtMaXx Mega Mark, Tem certeza?", 0, false);
            }

            if (qty3 < qtytotal3 && player->HasItemCount(itemid3,10)){
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_bone_humanskull_01:30:30:-18:0|tDoar Enemy Head", 3, 0, "Será Descontado 10 Enemy Head, Tem certeza?", 0, false);
            }

            if (qty4 < qtytotal4 && player->HasItemCount(itemid4,10)){
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_frostemblem_01:30:30:-18:0|tDoar Emblem of Frost", 4, 0, "Será Descontado 10 Emblem of Frost, Tem certeza?", 0, false);
            }

            if (qty5 < qtytotal5 && player->HasItemCount(itemid5,1)){
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_bijou_gold:30:30:-18:0|tDoar EtMaXx Event Mark", 5, 0, "Será Descontado 1 EtMaXx Event Mark, Tem certeza?", 0, false);
            }
            
            if (qty6 < qtytotal6 && player->HasItemCount(itemid6,10)){
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_holy_championsbond:30:30:-18:0|tDoar Badge of Justice", 6, 0, "Será Descontado 10 Badge of Justice, Tem certeza?", 0, false);
            }

            if (qty7 < qtytotal7 && player->GetMoney() > 100000000){
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_coin_01:30:30:-18:0|tDoar Gold", 7, 0, "Será Descontado 10.000 de Gold, Tem certeza?", 0, false);
            }

            if (qty8 < qtytotal8){
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_shadow_lifedrain:30:30:-18:0|tSacrificar sua própria vida!", 8, 0, "Essa Ação levará a sua morte! Tem certeza disso ?", 0, false);
            }
            
            if(qty1 >= qtytotal1 && qty2 >= qtytotal2 && qty3 >= qtytotal3 && qty4 >= qtytotal4 && qty5 >= qtytotal5 && qty6 >= qtytotal6 && qty7 >= qtytotal7 && qty8 >= qtytotal8){
                AddGossipItemFor(player, GOSSIP_ACTION_AUCTION, "|TInterface/Icons/spell_lightning_lightningbolt01:30:30:-18:0|tO RITUAL ESTÁ PRONTO, ATIVAR ?", 10, 0, "Isso Ativará os Buff em ICC por 24 horas, porém será possivel reativar dentro de 48 horas, tem certeza que deseja iniciar o ritual ?", 0, false);
            }

            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tVerificar estado do ritual", 9, 0);
            
        }else{
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_scroll_03:30:30:-18:0|tVerificar estado do ritual", 9, 0);
        }
        
        player->SEND_GOSSIP_MENU(800810, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 /*action*/)
    {
        switch (sender)
        {
        case 1:
        {
            player->DestroyItemCount(itemid1,1000,true);
            WorldDatabase.PExecute("UPDATE mod_icc_buff SET qty = %u WHERE itemid = %u", qty1+1000, itemid1);
            ChatHandler(player->GetSession()).PSendSysMessage("1000 EtMaXx Marks foram removidas para o ritual");
            CloseGossipMenuFor(player);
        }
        break;

        case 2:
        {
            player->DestroyItemCount(itemid2,10,true);
            WorldDatabase.PExecute("UPDATE mod_icc_buff SET qty = %u WHERE itemid = %u", qty2+10, itemid2);
            ChatHandler(player->GetSession()).PSendSysMessage("10 EtMaXx Mega Marks foram removidas para o ritual");
            CloseGossipMenuFor(player);
        }
        break;

        case 3:
        {
            player->DestroyItemCount(itemid3,10,true);
            WorldDatabase.PExecute("UPDATE mod_icc_buff SET qty = %u WHERE itemid = %u", qty3+10, itemid3);
            ChatHandler(player->GetSession()).PSendSysMessage("10 Enemy Heads foram removidas para o ritual");
            CloseGossipMenuFor(player);
        }
        break;

        case 4:
        {
            player->DestroyItemCount(itemid4,10,true);
            WorldDatabase.PExecute("UPDATE mod_icc_buff SET qty = %u WHERE itemid = %u", qty4+10, itemid4);
            ChatHandler(player->GetSession()).PSendSysMessage("10 Emblem of Frost foram removidos para o ritual");
            CloseGossipMenuFor(player);
        }
        break;

        case 5:
        {
            player->DestroyItemCount(itemid5,1,true);
            WorldDatabase.PExecute("UPDATE mod_icc_buff SET qty = %u WHERE itemid = %u", qty5+1, itemid5);
            ChatHandler(player->GetSession()).PSendSysMessage("1 EtMaXx Event Marks foi removida para o ritual");
            CloseGossipMenuFor(player);
        }
        break;

        case 6:
        {
            player->DestroyItemCount(itemid6,10,true);
            WorldDatabase.PExecute("UPDATE mod_icc_buff SET qty = %u WHERE itemid = %u", qty6+10, itemid6);
            ChatHandler(player->GetSession()).PSendSysMessage("10 Badge of Justice foram removidos para o ritual");
            CloseGossipMenuFor(player);
        }
        break;

        case 7:
        {
            player->ModifyMoney(-100000000);
            WorldDatabase.PExecute("UPDATE mod_icc_buff SET qty = %u WHERE itemid = %u", qty7+10000, itemid7);
            ChatHandler(player->GetSession()).PSendSysMessage("10000 de Gold foram removidos para o Ritual");
            CloseGossipMenuFor(player);
        }
        break;

        case 8:
        {
            player->CastSpell(player, 7, false);
            WorldDatabase.PExecute("UPDATE mod_icc_buff SET qty = %u WHERE itemid = %u", qty8+1, itemid8);
            ChatHandler(player->GetSession()).PSendSysMessage("Seu Sacrificio não será em vão");
            CloseGossipMenuFor(player);
        }
        break;

        case 9:
        {
            if(autocast1 == 1 && autocast2 == 1 && autocast3 == 1 && autocast4 == 1){
                QueryResult resultexpire1 = WorldDatabase.PQuery("SELECT FROM_UNIXTIME(expiredate, '%%d-%%m-%%Y..%%H:%%I:%%s') as expiredate FROM mod_icc_buff WHERE id = 9;");
                if (resultexpire1) {
                    Field* fields = resultexpire1->Fetch();
                    ChatHandler(player->GetSession()).PSendSysMessage("O Ritual está ativo! os Buffs em ICC estão habilitados até %s", fields[0].GetCString());
                }
                CloseGossipMenuFor(player);
            }else{
            ChatHandler(player->GetSession()).PSendSysMessage("-------------------------------");
            ChatHandler(player->GetSession()).PSendSysMessage("RESUMO DOS ITEMS PARA O RITUAL");
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Mark, %u de 50000", qty1);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Mega Mark, %u de 500", qty2);
            ChatHandler(player->GetSession()).PSendSysMessage("Enemy Head, %u de 100", qty3);
            ChatHandler(player->GetSession()).PSendSysMessage("Emblem of Frost, %u de 500", qty4);
            ChatHandler(player->GetSession()).PSendSysMessage("EtMaXx Event Mark, %u de 5", qty5);
            ChatHandler(player->GetSession()).PSendSysMessage("Badge of Justice, %u de 200", qty6);
            ChatHandler(player->GetSession()).PSendSysMessage("Gold, %u de 500000", qty7);
            ChatHandler(player->GetSession()).PSendSysMessage("Sacrificios, %u de 10", qty8);
            ChatHandler(player->GetSession()).PSendSysMessage("-------------------------------");
            CloseGossipMenuFor(player);
            }
        }
        break;

        case 10:
        {
            WorldDatabase.PExecute("UPDATE spell_area SET autocast = 1 WHERE area = 4812 AND spell = 62650");
            WorldDatabase.PExecute("UPDATE spell_area SET autocast = 1 WHERE area = 4812 AND spell = 62702");
            WorldDatabase.PExecute("UPDATE spell_area SET autocast = 1 WHERE area = 4812 AND spell = 62670");
            WorldDatabase.PExecute("UPDATE spell_area SET autocast = 1 WHERE area = 4812 AND spell = 62671");
            sSpellMgr->LoadSpellAreas();
            WorldDatabase.PExecute("UPDATE mod_icc_buff SET qty = %u WHERE itemid = %u", qty9+1, itemid9);
            WorldDatabase.PExecute("UPDATE mod_icc_buff SET usedate = UNIX_TIMESTAMP(NOW()) WHERE id = 9");
            WorldDatabase.PExecute("UPDATE mod_icc_buff SET expiredate = UNIX_TIMESTAMP(NOW() + INTERVAL 24 HOUR) WHERE id = 9");
            QueryResult resultexpire2 = WorldDatabase.PQuery("SELECT FROM_UNIXTIME(expiredate, '%%d-%%m-%%Y..%%H:%%I:%%s') as expiredate FROM mod_icc_buff WHERE id = 9;");
            if (resultexpire2) {
                Field* fields = resultexpire2->Fetch();
                char msg[1000];
                sprintf(msg, "|cffFF0000[Ritual dos Titãns]|r Os Buffs em ICC Foram ativados até %s", fields[0].GetCString());
                sWorld->SendGlobalText(msg, NULL);
            }

            CloseGossipMenuFor(player);
        }
        break;

        case 1000: // Main menu
        {
            OnGossipHello(player, creature);
        }
        break;

        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC tutorial                        	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_tutorial : public CreatureScript
{
public:
    etmaxx_tutorial() : CreatureScript("etmaxx_tutorial") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();
        if (player->HasItemCount(800810, 1, true) && player->HasItemCount(70506, 1, true))
        {
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_book_11:30:30:-18:0|tVamos para Dalaran!", 1, 0);
        }
        else
        {
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/Ability_Spy:30:30:-18:0|tVocê ainda tem algo a fazer por aqui...", 2, 0);
        }
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature * /*creature*/, uint32 sender, uint32 /*action*/)
    {
        switch (sender)
        {
        case 1:
        {
            player->DestroyItemCount(70506, 1, true);
            player->TeleportTo(571, 5920.42f, 646.38f, 644.69f, 0.49f);
            CloseGossipMenuFor(player);
        }
        break;

        case 2:
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Complete todas as missões iniciais, fala com o EtMaXx Start e depois volte até mim");
            CloseGossipMenuFor(player);
        }
        break;
        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 NPC Cassandra                        	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_tabard_up : public CreatureScript
{
public:
    etmaxx_tabard_up() : CreatureScript("etmaxx_tabard_up") {}

    bool OnGossipHello(Player *player, Creature *creature)
    {
        player->PlayerTalkClass->ClearMenus();

        if (player->HasItemCount(90100, 30, true) ALLY OU HORDA)
        {
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shirt_15:30:30:-18:0|tAtualizar minha Tabard para o Rank 2", 2, 0); // OU 3 para Ally
        } else {
            // AVISAR QUE NÃO TEM TOKEN
        }
        //AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shirt_12:30:30:-18:0|tAtualizar minha Tabard para o Rank 1", 1, 0);
        
        //AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shirt_guildtabard_01:30:30:-18:0|tAtualizar minha Tabard para o Rank 3", 3, 0);
        //AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_misc_tabardsummer01:30:30:-18:0|tAtualizar minha Tabard para o Rank 4", 4, 0);
        player->SEND_GOSSIP_MENU(800811, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature * /*creature*/, uint32 sender, uint32 /*action*/)
    {
        // Heal
        int32 orgrimmarHeal1 = 60080;
        int32 orgrimmarHeal2 = 60081;
        int32 orgrimmarHeal3 = 60082;
        int32 orgrimmarHeal4 = 60083;

        // Agi
        int32 orgrimmarAgi1 = 60084;
        int32 orgrimmarAgi2 = 60085;
        int32 orgrimmarAgi3 = 60086;
        int32 orgrimmarAgi4 = 60087;

        // Str
        int32 orgrimmarStr1 = 60088;
        int32 orgrimmarStr2 = 60089;
        int32 orgrimmarStr3 = 60090;
        int32 orgrimmarStr4 = 60091;

        // SDPS
        int32 orgrimmarSDps1 = 60092;
        int32 orgrimmarSDps2 = 60093;
        int32 orgrimmarSDps3 = 60094;
        int32 orgrimmarSDps4 = 60095;

        // Tank
        int32 orgrimmarTank1 = 60096;
        int32 orgrimmarTank2 = 60097;
        int32 orgrimmarTank3 = 60098;
        int32 orgrimmarTank4 = 60099;

        switch (sender)
        {
        case 2:// HORDA
        {
            if (player->getRace() == RACE_ORC)
            {
                 if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT)
                 {
                     if (player->HasItemCount(orgrimmarTank1, 1) || player->HasItemCount(orgrimmarTank2, 1) || player->HasItemCount(orgrimmarTank3, 1))
                     {
                     AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_shield_32:30:30:-18:0|tTANK", 60096, 0);
                     }
                 }

                 if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_WARLOCK)
                 {
                     if (player->HasItemCount(orgrimmarSDps1, 1) || player->HasItemCount(orgrimmarSDps2, 1) || player->HasItemCount(orgrimmarSDps3, 1))
                     {
                         AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_staff_52:30:30:-18:0|tSPELL DPS", 60092, 0);
                     }
                     
                 }

                 if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT)
                 {
                     if (player->HasItemCount(orgrimmarStr1, 1) || player->HasItemCount(orgrimmarStr2, 1) || player->HasItemCount(orgrimmarStr3, 1))
                     {
                         AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_hammer_unique_sulfuras:30:30:-18:0|tSTRENGTH DPS", 60088, 0);
                     }
                     
                 }

                 if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_SHAMAN)
                 {
                     if (player->HasItemCount(orgrimmarAgi1, 1) || player->HasItemCount(orgrimmarAgi2, 1) || player->HasItemCount(orgrimmarAgi3, 1))
                     {
                         AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/inv_weapon_bow_39:30:30:-18:0|tAGILITY DPS", 60084, 0);
                     }
                     
                 }

                 if (player->getClass() == CLASS_SHAMAN)
                 {
                     if (player->HasItemCount(orgrimmarHeal1, 1) || player->HasItemCount(orgrimmarHeal2, 1) || player->HasItemCount(orgrimmarHeal3, 1))
                     {
                         AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface/Icons/spell_nature_healingwavegreater:30:30:-18:0|tHEAL", 60080, 0);
                     }
                 }
            }
        }
        break;
        case 60096:
        {
            int32 leveltabard = 3;

            if ((player->HasItemCount(orgrimmarTank1, 1)) {
                leveltabard = 1;
            }
            else if (player->HasItemCount(orgrimmarTank2, 1)) {
                leveltabard = 2;
            }

        }

            if (destroyTabard(player))
            {
                if (leveltabard = 1) {
                    player->AddItem(orgrimmarTank2, 1);
                }

                if (leveltabard = 2)
                {
                    player->AddItem(orgrimmarTank3, 1);
                }

                if (leveltabard = 3)
                {
                    player->AddItem(orgrimmarTank4, 1);
                }
                
                CloseGossipMenuFor(player);
            }
            break;

        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////        Scripts de Itens - EtMaXx Fire Aura 	        ///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_fireaura : public ItemScript
{
public:
    etmaxx_fireaura() : ItemScript("etmaxx_fireaura") {}

    bool OnUse(Player *p, Item * /*i*/, const SpellCastTargets &) override
    {
        if (p->HasAura(51193))
        {
            p->RemoveAura(51193);
        }
        else
        {
            p->AddAura(51193, p);
        }

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////      Scripts de Itens - EtMaXx Blue Aura             	///////////////
///////////////////////////////////////////////////////////////////////////////////;

class etmaxx_blueaura : public ItemScript
{
public:
    etmaxx_blueaura() : ItemScript("etmaxx_blueaura") {}

    bool OnUse(Player *p, Item * /*i*/, const SpellCastTargets &) override
    {
        if (p->HasAura(46933))
        {
            p->RemoveAura(46933);
        }
        else
        {
            p->AddAura(46933, p);
        }

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////////
/////////////                 Instanciando o NPC                   	///////////////
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
    new etmaxx_fireaura();
    new etmaxx_jc();
    new etmaxx_lw();
    new etmaxx_tl();
    new etmaxx_bs();
    new etmaxx_ec();
    new etmaxx_eng();
    new etmaxx_cook();
    new etmaxx_alc();
    new etmaxx_tutorial();
    new etmaxx_buff();
    new etmaxx_blueaura();
}
