
#include "ScriptMgr.h"
#include "Player.h"
#include "GuildMgr.h"
#include "Configuration/Config.h"
#include "Chat.h"

#define Welcome_Name "Notice"


class StartGuild : public PlayerScript
{

public:
	StartGuild() : PlayerScript("StartGuild") { }

	// Announce Module
	void OnLogin(Player *player)
	{
        if (player->getLevel() > 0 && player->getLevel() <= 79 && !player->GetGuild())
            addPlayerToGuild(player);
	};

	// Start Guild
	void OnFirstLogin(Player* player)
	{
        addPlayerToGuild(player);
	}

	void addPlayerToGuild(Player* player) {
		const uint32 GUILD_ID_ALLIANCE = 32;
		const uint32 GUILD_ID_HORDE = 33;

		Guild* guild = sGuildMgr->GetGuildById(player->GetTeamId() == TEAM_ALLIANCE ? GUILD_ID_ALLIANCE : GUILD_ID_HORDE);

		// If a guild is present, assign the character to the guild; otherwise skip assignment.
		if (guild)
		{
			guild->AddMember(player->GetGUID());

			// Inform the player they have joined the guild
			std::ostringstream ss;
			ss << "Bem vindo a " << player->GetGuildName() << ", " << player->GetName() << "!";
			ChatHandler(player->GetSession()).SendSysMessage(ss.str().c_str());
		}
    }
};

void AddStartGuildScripts()
{
	new StartGuild();
}

