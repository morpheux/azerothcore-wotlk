/*
 * This file is part of the WarheadCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Log.h"
#include "ScriptMgr.h"
#include "Config.h"
#include "Chat.h"
#include "Player.h"
#include "AccountMgr.h"

class GMChatColor_Player : public PlayerScript
{
public:
    GMChatColor_Player() : PlayerScript("GMChatColor_Player") { }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg) override
    {
        SetColorMessage(player, msg);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Player* /*receiver*/) override
    {
        SetColorMessage(player, msg);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Group* /*group*/) override
    {
        SetColorMessage(player, msg);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Guild* /*guild*/) override
    {
        SetColorMessage(player, msg);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Channel* /*channel*/) override
    {
        SetColorMessage(player, msg);
    }

private:
    void SetColorMessage(Player* player, std::string& Message)
    {
        if (AccountMgr::IsPlayerAccount(player->GetSession()->GetSecurity()) || !player->isGMChat() || Message.empty())
            return;

        uint8 gmLevel = player->GetSession()->GetSecurity();

        if (gmLevel > 4)
            return;
		
		std::string gmColor1 = "|cffADFF2F"; // GREENYELLOW
		std::string gmColor2 = "|cff388E8E"; // TEAL
		std::string gmColor3 = "|cffff00ff"; // MAGENTA
		std::string gmColor4 = "|cffffcc00"; // GOLD
		
		switch(gmLevel)
		{
		case 1:
		Message = gmColor1 + Message;
		break;
		case 2:
		Message = gmColor2 + Message;
		break;
		case 3:
		Message = gmColor3 + Message;
		break;
		case 4:
		Message = gmColor4 + Message;
		break;
		}
    };
};

// Group all custom scripts
void AddSC_GMChatColor()
{
    new GMChatColor_Player();
}
