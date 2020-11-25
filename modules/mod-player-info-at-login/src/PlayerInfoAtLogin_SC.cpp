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
#include "Time.h"

class PlayerInfoAtLogin_Player : public PlayerScript
{
public:
    PlayerInfoAtLogin_Player() : PlayerScript("PlayerInfoAtLogin_Player") {}

    void OnLogin(Player* player) override
    {
        ChatHandler handler(player->GetSession());

        std::string NameLink = handler.GetNameLink(player);
        std::string PlayerName = player->GetName();
        uint32 PlayerOnlineCount = sWorld->GetPlayerCount();
        std::string ServerUptime = secsToTimeString(sWorld->GetUptime());
        std::string PlayerIP = player->GetSession()->GetRemoteAddress();
        uint32 GMLevel = player->GetSession()->GetSecurity();
        uint32 connPeak = sWorld->GetMaxActiveSessionCount();

		handler.PSendSysMessage("|cffff0000##############################|r");        
        handler.PSendSysMessage("|cffff0000# |cff00ff00Oi,|r %s", PlayerName.c_str());
		handler.PSendSysMessage("|cffff0000# |cff00ff00Level da Conta:|r %u", GMLevel);
        handler.PSendSysMessage("|cffff0000# |cff00ff00Seu IP:|r %s", PlayerIP.c_str());
        handler.PSendSysMessage("|cffff0000# |cff00ff00Tempo do Servidor Online:|r %s", ServerUptime.c_str());
		
		if (GMLevel)
			handler.PSendSysMessage("|cffff0000# |cff00ff00Agora|r %u |cff00ff00jogadores online|r |cff00ff00(max:|r %u|cff00ff00)|r", PlayerOnlineCount, connPeak);
					
        handler.PSendSysMessage("|cffff0000##############################|r");
    }
};

// Group all custom scripts
void AddSC_PlayerInfoAtLogin()
{
    new PlayerInfoAtLogin_Player();
}
