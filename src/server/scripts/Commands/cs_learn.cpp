/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

/* ScriptData
Name: learn_commandscript
%Complete: 100
Comment: All learn related commands
Category: commandscripts
EndScriptData */

#include "Chat.h"
#include "Language.h"
#include "ObjectMgr.h"
#include "Pet.h"
#include "Player.h"
#include "PlayerCommand.h"
#include "ScriptMgr.h"
#include "SpellInfo.h"
#include "SpellMgr.h"

class learn_commandscript : public CommandScript, public PlayerCommand
{
public:
    learn_commandscript() : CommandScript("learn_commandscript") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> learnAllMyCommandTable =
        {
            { "class",          SEC_GAMEMASTER,  false, &HandleLearnAllMyClassCommand,       "" },
            { "pettalents",     SEC_GAMEMASTER,  false, &HandleLearnAllMyPetTalentsCommand,  "" },
            { "spells",         SEC_GAMEMASTER,  false, &HandleLearnAllMySpellsCommand,      "" },
            { "talents",        SEC_GAMEMASTER,  false, &HandleLearnAllMyTalentsCommand,     "" }
        };

        static std::vector<ChatCommand> learnAllCommandTable =
        {
            { "my",             SEC_GAMEMASTER,  false, nullptr,                             "", learnAllMyCommandTable },
            { "gm",             SEC_GAMEMASTER,  false, &HandleLearnAllGMCommand,            "" },
            { "crafts",         SEC_GAMEMASTER,  false, &HandleLearnAllCraftsCommand,        "" },
            { "default",        SEC_GAMEMASTER,  false, &HandleLearnAllDefaultCommand,       "" },
            { "lang",           SEC_GAMEMASTER,  false, &HandleLearnAllLangCommand,          "" },
            { "recipes",        SEC_GAMEMASTER,  false, &HandleLearnAllRecipesCommand,       "" }
        };

        static std::vector<ChatCommand> learnCommandTable =
        {
            { "all",            SEC_GAMEMASTER,  false, nullptr,                             "", learnAllCommandTable },
            { "",               SEC_GAMEMASTER,  false, &HandleLearnCommand,                 "" }
        };

        static std::vector<ChatCommand> commandTable =
        {
            { "learn",          SEC_GAMEMASTER,  false, nullptr,                             "", learnCommandTable },
            { "unlearn",        SEC_GAMEMASTER,  false, &HandleUnLearnCommand,               "" }
        };
        return commandTable;
    }

    static bool HandleLearnCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* targetPlayer = handler->getSelectedPlayer();

        if (!targetPlayer)
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
        uint32 spell = handler->extractSpellIdFromLink((char*)args);
        char const* all = strtok(nullptr, " ");
        return Learn(handler, targetPlayer, spell, all);
    }

    static bool HandleLearnAllGMCommand(ChatHandler* handler, char const* /*args*/)
    {
        for (uint32 i = 0; i < sSpellMgr->GetSpellInfoStoreSize(); ++i)
        {
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(i);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo))
                continue;

            if (!spellInfo->IsAbilityOfSkillType(SKILL_INTERNAL))
                continue;

            handler->GetSession()->GetPlayer()->learnSpell(i);
        }

        handler->SendSysMessage(LANG_LEARNING_GM_SKILLS);
        return true;
    }

    static bool HandleLearnAllMyClassCommand(ChatHandler* handler, char const* /*args*/)
    {
        HandleLearnAllMySpellsCommand(handler, "");
        HandleLearnAllMyTalentsCommand(handler, "");
        return true;
    }

    static bool HandleLearnAllMySpellsCommand(ChatHandler* handler, char const* /*args*/)
    {
        ChrClassesEntry const* classEntry = sChrClassesStore.LookupEntry(handler->GetSession()->GetPlayer()->getClass());
        if (!classEntry)
            return true;
        uint32 family = classEntry->spellfamily;

        for (uint32 i = 0; i < sSkillLineAbilityStore.GetNumRows(); ++i)
        {
            SkillLineAbilityEntry const* entry = sSkillLineAbilityStore.LookupEntry(i);
            if (!entry)
                continue;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(entry->spellId);
            if (!spellInfo)
                continue;

            // skip server-side/triggered spells
            if (spellInfo->SpellLevel == 0)
                continue;

            // skip wrong class/race skills
            if (!handler->GetSession()->GetPlayer()->IsSpellFitByClassAndRace(spellInfo->Id))
                continue;

            // skip other spell families
            if (spellInfo->SpellFamilyName != family)
                continue;

            // skip spells with first rank learned as talent (and all talents then also)
            uint32 firstRank = sSpellMgr->GetFirstSpellInChain(spellInfo->Id);
            if (GetTalentSpellCost(firstRank) > 0)
                continue;

            // skip broken spells
            if (!SpellMgr::IsSpellValid(spellInfo))
                continue;

            handler->GetSession()->GetPlayer()->learnSpell(spellInfo->Id);
        }

        handler->SendSysMessage(LANG_COMMAND_LEARN_CLASS_SPELLS);
        return true;
    }

    static bool HandleLearnAllMyTalentsCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        uint32 classMask = player->getClassMask();

        for (uint32 i = 0; i < sTalentStore.GetNumRows(); ++i)
        {
            TalentEntry const* talentInfo = sTalentStore.LookupEntry(i);
            if (!talentInfo)
                continue;

            TalentTabEntry const* talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);
            if (!talentTabInfo)
                continue;

            if ((classMask & talentTabInfo->ClassMask) == 0)
                continue;

            // xinef: search highest talent rank
            uint32 spellId = 0;
            uint8 rankId = MAX_TALENT_RANK;
            for (int8 rank = MAX_TALENT_RANK - 1; rank >= 0; --rank)
            {
                if (talentInfo->RankID[rank] != 0)
                {
                    rankId = rank;
                    spellId = talentInfo->RankID[rank];
                    break;
                }
            }

            // xinef: some errors?
            if (!spellId || rankId == MAX_TALENT_RANK)
                continue;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo))
                continue;

            player->LearnTalent(talentInfo->TalentID, rankId);
        }

        handler->SendSysMessage(LANG_COMMAND_LEARN_CLASS_TALENTS);
        return true;
    }

    static bool HandleLearnAllMyPetTalentsCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        Pet* pet = player->GetPet();
        if (!pet)
        {
            handler->SendSysMessage(LANG_NO_PET_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        CreatureTemplate const* creatureInfo = pet->GetCreatureTemplate();
        if (!creatureInfo)
        {
            handler->SendSysMessage(LANG_WRONG_PET_TYPE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        CreatureFamilyEntry const* petFamily = sCreatureFamilyStore.LookupEntry(creatureInfo->family);
        if (!petFamily)
        {
            handler->SendSysMessage(LANG_WRONG_PET_TYPE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (petFamily->petTalentType < 0)                       // not hunter pet
        {
            handler->SendSysMessage(LANG_WRONG_PET_TYPE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        for (uint32 i = 0; i < sTalentStore.GetNumRows(); ++i)
        {
            TalentEntry const* talentInfo = sTalentStore.LookupEntry(i);
            if (!talentInfo)
                continue;

            TalentTabEntry const* talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);
            if (!talentTabInfo)
                continue;

            // prevent learn talent for different family (cheating)
            if (((1 << petFamily->petTalentType) & talentTabInfo->petTalentMask) == 0)
                continue;

            // search highest talent rank
            uint32 spellId = 0;

            for (int8 rank = MAX_TALENT_RANK - 1; rank >= 0; --rank)
            {
                if (talentInfo->RankID[rank] != 0)
                {
                    spellId = talentInfo->RankID[rank];
                    break;
                }
            }

            if (!spellId)                                        // ??? none spells in talent
                continue;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo))
                continue;

            // learn highest rank of talent and learn all non-talent spell ranks (recursive by tree)
            pet->learnSpellHighRank(spellId);
        }

        pet->SetFreeTalentPoints(0);

        handler->SendSysMessage(LANG_COMMAND_LEARN_PET_TALENTS);
        return true;
    }

    static bool HandleLearnAllLangCommand(ChatHandler* handler, char const* /*args*/)
    {
        // skipping UNIVERSAL language (0)
        for (uint8 i = 1; i < LANGUAGES_COUNT; ++i)
            handler->GetSession()->GetPlayer()->learnSpell(lang_description[i].spell_id);

        handler->SendSysMessage(LANG_COMMAND_LEARN_ALL_LANG);
        return true;
    }

    static bool HandleLearnAllDefaultCommand(ChatHandler* handler, char const* args)
    {
        Player* target;
        if (!handler->extractPlayerTarget((char*)args, &target))
            return false;

        target->learnDefaultSpells();
        target->learnQuestRewardedSpells();

        handler->PSendSysMessage(LANG_COMMAND_LEARN_ALL_DEFAULT_AND_QUEST, handler->GetNameLink(target).c_str());
        return true;
    }

    static bool HandleLearnAllCraftsCommand(ChatHandler* handler, char const* /*args*/)
    {
        for (uint32 i = 0; i < sSkillLineStore.GetNumRows(); ++i)
        {
            SkillLineEntry const* skillInfo = sSkillLineStore.LookupEntry(i);
            if (!skillInfo)
                continue;

            if ((skillInfo->categoryId == SKILL_CATEGORY_PROFESSION || skillInfo->categoryId == SKILL_CATEGORY_SECONDARY) &&
                    skillInfo->canLink)                             // only prof. with recipes have
            {
                HandleLearnSkillRecipesHelper(handler->GetSession()->GetPlayer(), skillInfo->id);
            }
        }

        handler->SendSysMessage(LANG_COMMAND_LEARN_ALL_CRAFT);
        return true;
    }

    static bool HandleLearnAllRecipesCommand(ChatHandler* handler, char const* args)
    {
        //  Learns all recipes of specified profession and sets skill to max
        //  Example: .learn all_recipes enchanting

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            return false;
        }

        if (!*args)
            return false;

        std::wstring namePart;

        if (!Utf8toWStr(args, namePart))
            return false;

        // converting string that we try to find to lower case
        wstrToLower(namePart);

        std::string name;

        SkillLineEntry const* targetSkillInfo = nullptr;
        for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
        {
            SkillLineEntry const* skillInfo = sSkillLineStore.LookupEntry(i);
            if (!skillInfo)
                continue;

            if ((skillInfo->categoryId != SKILL_CATEGORY_PROFESSION &&
                    skillInfo->categoryId != SKILL_CATEGORY_SECONDARY) ||
                    !skillInfo->canLink)                            // only prof with recipes have set
                continue;

            int locale = handler->GetSessionDbcLocale();
            name = skillInfo->name[locale];
            if (name.empty())
                continue;

            if (!Utf8FitTo(name, namePart))
            {
                locale = 0;
                for (; locale < TOTAL_LOCALES; ++locale)
                {
                    if (locale == handler->GetSessionDbcLocale())
                        continue;

                    name = skillInfo->name[locale];
                    if (name.empty())
                        continue;

                    if (Utf8FitTo(name, namePart))
                        break;
                }
            }

            if (locale < TOTAL_LOCALES)
            {
                targetSkillInfo = skillInfo;
                break;
            }
        }

        if (!targetSkillInfo)
            return false;

        HandleLearnSkillRecipesHelper(target, targetSkillInfo->id);

        uint16 maxLevel = target->GetPureMaxSkillValue(targetSkillInfo->id);
        target->SetSkill(targetSkillInfo->id, target->GetSkillStep(targetSkillInfo->id), maxLevel, maxLevel);
        handler->PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, name.c_str());
        return true;
    }

    static void HandleLearnSkillRecipesHelper(Player* player, uint32 skillId)
    {
        switch (skillId)
        {
        case SKILL_ALCHEMY:
            player->learnSpell(2259);
            player->learnSpell(3101);
            player->learnSpell(3464);
            player->learnSpell(11611);
            player->learnSpell(28596);
            player->learnSpell(51304);
            break;
        case SKILL_BLACKSMITHING:
            player->learnSpell(2018);
            player->learnSpell(3100);
            player->learnSpell(3538);
            player->learnSpell(9785);
            player->learnSpell(29844);
            player->learnSpell(51300);
            break;
        case SKILL_ENCHANTING:
            player->learnSpell(7411);
            player->learnSpell(7412);
            player->learnSpell(7413);
            player->learnSpell(13920);
            player->learnSpell(28029);
            player->learnSpell(51313);
            break;
        case SKILL_ENGINEERING:
            player->learnSpell(4036);
            player->learnSpell(4037);
            player->learnSpell(4038);
            player->learnSpell(12656);
            player->learnSpell(30350);
            player->learnSpell(51306);
            break;
        case SKILL_INSCRIPTION:
            player->learnSpell(45357);
            player->learnSpell(45358);
            player->learnSpell(45359);
            player->learnSpell(45360);
            player->learnSpell(45361);
            player->learnSpell(45363);
            break;
        case SKILL_JEWELCRAFTING:
            player->learnSpell(25229);
            player->learnSpell(25230);
            player->learnSpell(28894);
            player->learnSpell(28895);
            player->learnSpell(28897);
            player->learnSpell(51311);
            break;
        case SKILL_LEATHERWORKING:
            player->learnSpell(2108);
            player->learnSpell(3104);
            player->learnSpell(3811);
            player->learnSpell(10662);
            player->learnSpell(32549);
            player->learnSpell(51302);
            break;
        case SKILL_TAILORING:
            player->learnSpell(3908);
            player->learnSpell(3909);
            player->learnSpell(3910);
            player->learnSpell(12180);
            player->learnSpell(26790);
            player->learnSpell(51309);
            break;
        case SKILL_COOKING:
            player->learnSpell(51296);
            break;
        case SKILL_FIRST_AID:
            player->learnSpell(45542);
            break;
        case SKILL_FISHING:
            player->learnSpell(65293);
            break;
        case SKILL_MINING:
            player->learnSpell(2575);
            player->learnSpell(2576);
            player->learnSpell(3564);
            player->learnSpell(10248);
            player->learnSpell(29354);
            player->learnSpell(50310);
            break;
        case SKILL_SKINNING:
            player->learnSpell(8613);
            player->learnSpell(8617);
            player->learnSpell(8618);
            player->learnSpell(10768);
            player->learnSpell(32678);
            player->learnSpell(50305);
            break;
        case SKILL_HERBALISM:
            player->learnSpell(2366);
            player->learnSpell(2368);
            player->learnSpell(3570);
            player->learnSpell(11993);
            player->learnSpell(28695);
            player->learnSpell(50300);
            break;
        default:
            break;
        }

        if (SkillLineEntry const* SkillInfo = sSkillLineStore.LookupEntry(skillId))
        {
            player->SetSkill(SkillInfo->id, player->GetSkillStep(SkillInfo->id), 450, 450);

            for (uint32 I = 0; I < sSkillLineAbilityStore.GetNumRows(); ++I)
            {
                if (SkillLineAbilityEntry const* SkillLine = sSkillLineAbilityStore.LookupEntry(I))
                {
                    if (SkillLine->skillId != SkillInfo->id)
                        continue;

                    if (SkillLine->forward_spellid)
                        continue;

                    if (SkillLine->racemask != 0)
                        continue;

                    if (SkillLine->classmask && (SkillLine->classmask & player->getClassMask()) == 0)
                        continue;

                    SpellInfo const* SpellInfo2 = sSpellMgr->GetSpellInfo(SkillLine->spellId);

                    if (!SpellInfo2 || !SpellMgr::IsSpellValid(SpellInfo2))
                        continue;

                    player->learnSpell(SkillLine->spellId);

                }

            }
        }
    }

    static bool HandleUnLearnCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r
        uint32 spellId = handler->extractSpellIdFromLink((char*)args);
        char const* allStr = strtok(nullptr, " ");
        return UnLearn(handler, target, spellId, allStr);
    }
};

void AddSC_learn_commandscript()
{
    new learn_commandscript();
}
