#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include "ScriptedGossip.h"
#include "Configuration/Config.h"
#include "Creature.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "Define.h"
#include "GossipDef.h"
#include "DataMap.h"
#include "GameObject.h"
#include "Transport.h"
#include "CreatureAI.h"

int cost;

class GuildHouseSpawner : public CreatureScript {

public:
    GuildHouseSpawner() : CreatureScript("GuildHouseSpawner") { }

    bool OnGossipHello(Player *player, Creature * creature)
    {

        if (player->GetGuild())
        {
            Guild* guild = sGuildMgr->GetGuildById(player->GetGuildId());
            Guild::Member const* memberMe = guild->GetMember(player->GetGUID());
            if (!memberMe->IsRankNotLower(0))
            {
                ChatHandler(player->GetSession()).PSendSysMessage("You are not authorized to make guild house purchases.");
                return false;
            }
        }
        else
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You are not in a guild!");
            return false;
        }

        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Spawn Innkeeper", GOSSIP_SENDER_MAIN, 18649, "Add an Innkeeper?", 1000000, false);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Spawn Mailbox", GOSSIP_SENDER_MAIN, 184137, "Spawn a mailbox?", 500000, false);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Spawn Stable Master", GOSSIP_SENDER_MAIN, 28690, "Spawn a Stable Master?", 500000, false);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Spawn Class Trainer", GOSSIP_SENDER_MAIN, 2);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Spawn Vendor", GOSSIP_SENDER_MAIN, 3);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Spawn EtMaxX Recipes", GOSSIP_SENDER_MAIN, 5);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Spawn EtMaxX Reagents", GOSSIP_SENDER_MAIN, 10);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Spawn City Portals / Objects / NPC's", GOSSIP_SENDER_MAIN, 4);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Spawn Bank", GOSSIP_SENDER_MAIN, 30605, "Spawn a banker?", 1000000, false);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Spawn Auctioneer", GOSSIP_SENDER_MAIN, 6, "Spawn an auctioneer", 500000, false);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Spawn Primary Profession Trainers", GOSSIP_SENDER_MAIN, 7);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Spawn Secondry Profession Trainers", GOSSIP_SENDER_MAIN, 8);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Spawn Sprirt Healer", GOSSIP_SENDER_MAIN, 6491, "Spawn a Spirit Healer?", 100000, false);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Spawn EtMaXx Fligh Master", GOSSIP_SENDER_MAIN, 191000, "Spawn a EtMaXx FlightMaster?", 100000, false);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Spawn Cromi", GOSSIP_SENDER_MAIN, 300000, "Spawn Cromi?", 100000, false);
        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature * m_creature, uint32, uint32 action)
    {

        switch (action)
        {
        case 2: // spawn class trainer
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Death Knight", GOSSIP_SENDER_MAIN, 33251, "Spawn Death Knight Trainer?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Druid", GOSSIP_SENDER_MAIN, 26324, "Spawn Druid Trainer?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Hunter", GOSSIP_SENDER_MAIN, 26325, "Spawn Hunter Trainer?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Mage", GOSSIP_SENDER_MAIN, 26326, "Spawn Mage Trainer?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Paladin", GOSSIP_SENDER_MAIN, 26327, "Spawn Paladin Trainer?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Priest", GOSSIP_SENDER_MAIN, 26328, "Spawn Priest Trainer?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Rogue", GOSSIP_SENDER_MAIN, 26329, "Spawn Rogue Trainer?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Shaman", GOSSIP_SENDER_MAIN, 26330, "Spawn Shaman Trainer?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Warlock", GOSSIP_SENDER_MAIN, 26331, "Spawn Warlock Trainer?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Warrior", GOSSIP_SENDER_MAIN, 26332, "Spawn Warrior Trainer?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Go Back!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 3: // Vendors
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Trade Supplies", GOSSIP_SENDER_MAIN, 28692, "Spawn Trade Supplies?", 500000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Tabard Vendor", GOSSIP_SENDER_MAIN, 28776, "Spawn Tabard Vendor?", 500000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Food & Drink", GOSSIP_SENDER_MAIN, 70103, "Spawn Food & Drink?", 500000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Reagent Vendor", GOSSIP_SENDER_MAIN, 29636, "Spawn Reagent Vendor?", 500000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Ammo & Repair Vendor", GOSSIP_SENDER_MAIN, 70104, "Spawn Ammo & Repair Vendor?", 500000, false);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Go Back!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 4: //objects / portals
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Forge", GOSSIP_SENDER_MAIN, 1685, "Add a forge?", 500000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Anvil", GOSSIP_SENDER_MAIN, 4087, "Add an Anvil?", 500000, false);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Guild Vault", GOSSIP_SENDER_MAIN, 187293, "Add Guild Vault?", 500000,  false);
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Barber Chair", GOSSIP_SENDER_MAIN, 191028, "Add a Barber Chair?", 500000,  false);

            if (player->GetTeamId() == TEAM_ALLIANCE)   // ALLIANCE players get these options
            {
                // Commenting out as we are auto-creating Stormwind portal upon guild purchase
                //AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: Stormwind", GOSSIP_SENDER_MAIN, 183325, "Add Stormwind Portal?", 500000, false);
                AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: Ironforge", GOSSIP_SENDER_MAIN, 183322, "Add Ironforge Portal?", 500000, false);
                AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: Darnassus", GOSSIP_SENDER_MAIN, 183317, "Add Darnassus Portal?", 500000, false);
                AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: Exodar", GOSSIP_SENDER_MAIN, 183321, "Add Exodar Portal?", 500000, false);
            }
            else    // HORDE players get these options:
            {
                // Commenting out as we are auto-creating Orgrimmar portal upon guild purchase
                //AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: Orgrimmar", GOSSIP_SENDER_MAIN, 183323, "Add Orgrimmar Portal?", 500000,  false);
                AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: Undercity", GOSSIP_SENDER_MAIN, 183327, "Add Undercity Portal?", 500000,  false);
                AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: Thunderbluff", GOSSIP_SENDER_MAIN, 183326, "Add Thunderbuff Portal?", 500000,  false);
                AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: Silvermoon", GOSSIP_SENDER_MAIN, 183324, "Add Silvermoon Portal?", 500000,  false);
            }
                    // These two portals work for either Team
            AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: Shattrath", GOSSIP_SENDER_MAIN, 191013, "Add Shattrath Portal?", 500000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: Dalaran", GOSSIP_SENDER_MAIN, 195682, "Add Dalaran Portal?", 500000, false);
			AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Training Dummy", GOSSIP_SENDER_MAIN, 31146, "Add Training Dummy?", 500000, false);

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Go Back!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 5: // spawn etmaxx recipe
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Recipe Books", GOSSIP_SENDER_MAIN, 50050, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Recipe Leather A-F", GOSSIP_SENDER_MAIN, 50051, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Recipe Leather G-R", GOSSIP_SENDER_MAIN, 50052, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Recipe Leather S-Z", GOSSIP_SENDER_MAIN, 50053, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Recipe Tailor A-G", GOSSIP_SENDER_MAIN, 50054, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Recipe Tailor H-Z", GOSSIP_SENDER_MAIN, 50055, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Engineering A-Z", GOSSIP_SENDER_MAIN, 50056, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Blacksmith A-R", GOSSIP_SENDER_MAIN, 50057, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Blacksmith S-Z", GOSSIP_SENDER_MAIN, 50059, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Cooking A-Z", GOSSIP_SENDER_MAIN, 50060, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Alchemy A-Z", GOSSIP_SENDER_MAIN, 50061, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Enchanting A-G", GOSSIP_SENDER_MAIN, 50062, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Enchanting H-Z", GOSSIP_SENDER_MAIN, 50063, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Jewelcrafting A-K", GOSSIP_SENDER_MAIN, 50064, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Jewelcrafting L-Z", GOSSIP_SENDER_MAIN, 50065, "Spawn Recipe?", 1000000, false);
			AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Jewelcrafting Epic", GOSSIP_SENDER_MAIN, 50079, "Spawn Recipe?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Go Back!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 6: // Auctioneer
        {
            uint32 auctioneer = 0;
            auctioneer = player->GetTeamId() == TEAM_ALLIANCE ? 8719 : 9856;
            SpawnNPC(auctioneer, player);
            break;
        }
        case 7: // spawn profession trainers
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Alchemy Trainer", GOSSIP_SENDER_MAIN, 33608, "Spawn Alchemy Trainer?", 500000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Blacksmithing Trainer", GOSSIP_SENDER_MAIN, 33609, "Spawn Blacksmithing Trainer?", 500000,  false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Enchanting Trainer", GOSSIP_SENDER_MAIN, 33610, "Spawn Enchanting Trainer?", 500000,  false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Engineering Trainer", GOSSIP_SENDER_MAIN, 33611, "Spawn Engineering Trainer?", 500000,  false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Tailoring Trainer", GOSSIP_SENDER_MAIN, 33613, "Spawn Tailoring Trainer?", 500000,  false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Leatherworking Trainer", GOSSIP_SENDER_MAIN, 33612, "Spawn Leatherworking Trainer?", 500000,  false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Jewlelcrafing Trainer", GOSSIP_SENDER_MAIN, 33614, "Spawn Jewelcrafting Trainer?", 500000,  false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Inscription Trainer", GOSSIP_SENDER_MAIN, 33615, "Spawn Inscription Trainer?", 500000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Skinning Trainer", GOSSIP_SENDER_MAIN, 33618, "Spawn Skinning Trainer?", 500000,  false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Mining Trainer", GOSSIP_SENDER_MAIN, 33617, "Spawn Mining Trainer?", 500000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Herbalism Trainer", GOSSIP_SENDER_MAIN, 33616, "Spawn Herbalism Trainer?", 500000,  false);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Go Back!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 8: // secondry prof trainers
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "First Aid Trainer", GOSSIP_SENDER_MAIN, 33621, "Spawn Fist Aid Trainer?", 500000,  false);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Fishing Trainer", GOSSIP_SENDER_MAIN, 33623, "Spawn Fishing Trainer?", 500000,  false);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Cooking Trainer", GOSSIP_SENDER_MAIN, 33619, "Spawn Cooking Trainer?", 500000,  false);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Go Back!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 9: // go back!
            OnGossipHello(player, m_creature);
            break;
        case 10: //etmaxx reagents
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Leather I", GOSSIP_SENDER_MAIN, 50066, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Leather II", GOSSIP_SENDER_MAIN, 50067, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Tailor I", GOSSIP_SENDER_MAIN, 50068, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Tailor II", GOSSIP_SENDER_MAIN, 50069, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Engineer I", GOSSIP_SENDER_MAIN, 50070, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Engineer II", GOSSIP_SENDER_MAIN, 50071, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Blacksmith I", GOSSIP_SENDER_MAIN, 50072, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Blacksmith II", GOSSIP_SENDER_MAIN, 50073, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Cooking", GOSSIP_SENDER_MAIN, 50074, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Alchemy", GOSSIP_SENDER_MAIN, 50075, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Enchanting", GOSSIP_SENDER_MAIN, 50076, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Jewelcrafting", GOSSIP_SENDER_MAIN, 50077, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Inscription/Miscellaneous", GOSSIP_SENDER_MAIN, 50078, "Spawn Reagent?", 1000000, false);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Go Back!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 30605: // Banker
            cost = 1000000;
            SpawnNPC(action, player);
            break;
        case 18649: // Innkeeper
            cost = 1000000;
            SpawnNPC(action, player);
            break;
        case 26327: // Paladin
        case 26324: // Druid
        case 26325: // Hunter
        case 26326: // Mage 
        case 26328: // Priest.
        case 26329: // Rogue
        case 26330: // Shaman
        case 26331: // Warlock
        case 26332: // Warrior
        case 33251: // Death Knight
            cost = 1000000;
            SpawnNPC(action, player);
            break;
        case 33609: // Blacksmithing
        case 33617: // Mining
        case 33611: // Engineering
        case 33614: // Jewelcrafting
        case 33610: // Enchanting
        case 33615: // Inscription
        case 33612: // Leatherworking
        case 33618: // Skinning
        case 33608: // Alchemy
        case 33616: // Herbalism
        case 33613: // Tailoring
        case 33619: // Cooking
        case 33623: // Fishing 
        case 33621: // First Aid
            cost = 500000;
            SpawnNPC(action, player);
            break;
        case 50050:
        case 50051:
        case 50052:
        case 50053:
        case 50054:
        case 50055:
        case 50056:
        case 50057:
        case 50059:
        case 50060:
        case 50061:
        case 50062:
        case 50063:
        case 50064:
        case 50065:
        case 50079:
        case 191000:
		case 300000:
		case 31146:
        case 50066:
        case 50067:
        case 50068:
        case 50069:
        case 50070:
        case 50071:
        case 50072:
        case 50073:
        case 50074:
        case 50075:
        case 50076:
        case 50077:
        case 50078:
            cost = 1000000;
            SpawnNPC(action, player);
            break;
        case 28692: // Trade supplies
        case 28776: // Tabard Vendor
        case 70103: // Food & Drink
        case 29636: // Reagent Vendor
        case 70104: // Ammo & Repair Vendor
        case 28690: // Stable Master
            cost = 500000;
            SpawnNPC(action, player);
            break;
        //
        // Objects
        //
        case 184137: // mailbox
            cost = 500000;
            SpawnObject(action, player);
            break;
        case 6491:  // spirit healer   
            cost = 100000;
            SpawnNPC(action, player);
            break;               
        case 1685:  // forge
        case 4087:  // Anvil
        case 187293: // Guild Vault
        case 191028: // Barber Chair
            cost = 500000;
            SpawnObject(action, player);
            break;
        case 183322: // Ironforge Portal
        case 183327: // Undercity Portal
        case 183317: // Darnassus Portal
        case 183326: // Thunder bluff portal
        case 183324: // Silvermoon Portal
        case 183321: // Exodar Portal
        case 191013: // Shattrath Portal:Alliance
        case 191014: // Shattrath Portal:Horde
        case 195682: // Dalaran Portal
            cost = 500000;
            SpawnObject(action, player);
            break;
        }
        return true;
    }

	uint32 GetGuildPhase(Player* player) {
		return player->GetGuildId() + 10;
	}

    void SpawnNPC(uint32 entry, Player* player)
    {
        if (player->FindNearestCreature(entry, VISIBILITY_RANGE, true))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You already have this creature!");
            CloseGossipMenuFor(player);
            return;
        }

        float posX;
        float posY;
        float posZ;
        float ori;

        QueryResult result = WorldDatabase.PQuery("SELECT `posX`, `posY`, `posZ`, `orientation` FROM `guild_house_spawns` WHERE `entry` = %u", entry);

        if (!result)
            return;

        do
        {
            Field* fields = result->Fetch();
            posX = fields[0].GetFloat();
            posY = fields[1].GetFloat();
            posZ = fields[2].GetFloat();
            ori = fields[3].GetFloat();

        } while (result->NextRow());

        Creature* creature = new Creature();

        if (!creature->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT), player->GetMap(), GetGuildPhase(player), entry, 0, posX,posY, posZ, ori))
        {
            delete creature;
            return;
        }
        creature->SaveToDB(player->GetMapId(), (1 << player->GetMap()->GetSpawnMode()), GetGuildPhase(player));
        uint32 db_guid = creature->GetDBTableGUIDLow();

        creature->CleanupsBeforeDelete();
        delete creature;
        creature = new Creature();
        if (!creature->LoadCreatureFromDB(db_guid, player->GetMap()))
        {
            delete creature;
            return;
        }

        sObjectMgr->AddCreatureToGrid(db_guid, sObjectMgr->GetCreatureData(db_guid));
        player->ModifyMoney(-cost);
        CloseGossipMenuFor(player);
    }

    void SpawnObject(uint32 entry, Player* player)
    {
        float posX;
        float posY;
        float posZ;
        float ori;

        QueryResult result = WorldDatabase.PQuery("SELECT `posX`, `posY`, `posZ`, `orientation` FROM `guild_house_spawns` WHERE `entry` = %u", entry);

        if (!result)
            return;

        do
        {
            Field* fields = result->Fetch();
            posX = fields[0].GetFloat();
            posY = fields[1].GetFloat();
            posZ = fields[2].GetFloat();
            ori = fields[3].GetFloat();

        } while (result->NextRow());

        if (player->FindNearestGameObject(entry, VISIBLE_RANGE))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You already have this object!");
            CloseGossipMenuFor(player);
            return;
        }

        uint32 objectId = entry;
        if (!objectId)
            return;

        const GameObjectTemplate* objectInfo = sObjectMgr->GetGameObjectTemplate(objectId);

        if (!objectInfo)
            return;

        if (objectInfo->displayId && !sGameObjectDisplayInfoStore.LookupEntry(objectInfo->displayId))
            return ;

        GameObject* object = sObjectMgr->IsGameObjectStaticTransport(objectInfo->entry) ? new StaticTransport() : new GameObject();
        uint32 guidLow = sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT);

        if (!object->Create(guidLow, objectInfo->entry, player->GetMap(), GetGuildPhase(player), posX, posY, posZ, ori, G3D::Quat(), 0, GO_STATE_READY))
        {
            delete object;
            return;
        }

        // fill the gameobject data and save to the db
        object->SaveToDB(player->GetMapId(), (1 << player->GetMap()->GetSpawnMode()), GetGuildPhase(player));
        // delete the old object and do a clean load from DB with a fresh new GameObject instance.
        // this is required to avoid weird behavior and memory leaks
        delete object;

        object = sObjectMgr->IsGameObjectStaticTransport(objectInfo->entry) ? new StaticTransport() : new GameObject();
        // this will generate a new guid if the object is in an instance
        if (!object->LoadGameObjectFromDB(guidLow, player->GetMap()))
        {
            delete object;
            return;
        }

        // TODO: is it really necessary to add both the real and DB table guid here ?
        sObjectMgr->AddGameobjectToGrid(guidLow, sObjectMgr->GetGOData(guidLow));
        player->ModifyMoney(-cost);
        CloseGossipMenuFor(player);
    }
};

void AddGuildHouseV2NPCScripts()
{
    new GuildHouseSpawner();
}
