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
#include "Channel.h"
#include "AccountMgr.h"

class FactionsIconsChannel_Player : public PlayerScript
{
public:
    FactionsIconsChannel_Player() : PlayerScript("FactionsIconsChannel_Player") { }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Channel* channel) override
    {
        if (!player || !channel)
            return;

        std::string iconHorde = "|TInterface\\PVPFrame\\PVP-Currency-Horde:18:18:-3:-3|t";
        std::string iconAlliance = "|TInterface\\PVPFrame\\PVP-Currency-Alliance:18:18:-3:-3|t";

        std::stringstream ssMsg;
        ssMsg << ((player->GetTeamId() == TEAM_HORDE) ? iconHorde : iconAlliance) << msg;
        msg = ssMsg.str();
    }
};

// Group all custom scripts
void AddSC_FactionsIconsChannel()
{
    new FactionsIconsChannel_Player();
}
