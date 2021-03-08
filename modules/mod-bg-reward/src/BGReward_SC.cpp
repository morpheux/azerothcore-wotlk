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

#include "ScriptMgr.h"
#include "Player.h"
#include "Battleground.h"
#include "Configuration/Config.h"

class BGScript_BattlegroundsReward : public BGScript
{
public:
    BGScript_BattlegroundsReward() : BGScript("BGScript_BattlegroundsReward") {}

    void OnBattlegroundEndReward(Battleground* bg, Player* player, TeamId winnerTeamId) override
    {
        TeamId bgTeamId = player->GetBgTeamId();
        uint32 RewardCount = 0;

        if (!bg->isArena())
        {
            if (bgTeamId == winnerTeamId)
                RewardCount = 2;
            else
                RewardCount = 1;

            switch (player->GetZoneId())
            {
                case 3277:
                    player->AddItem(20558, RewardCount);
                    break;
                case 3358:
                    player->AddItem(20559, RewardCount);
                    break;
                case 3820:
                    player->AddItem(29024, RewardCount);
                    break;
                case 4710:
                    player->AddItem(47395, RewardCount);
                    break;
                case 4384:
                    player->AddItem(42425, RewardCount);
                    break;
                case 2597:
                    player->AddItem(20560, RewardCount);
                    break;
                default:
                    break;
            }
        }

        if (!bg->isBattleground())
        {
            if (bgTeamId == winnerTeamId)
                RewardCount = 2;
            else
                RewardCount = 1;

            switch (bg->GetArenaType())
            {
                case ARENA_TEAM_2v2:
                    //ArenaRewardItem(player, bgTeamId, winnerTeamId, "2v2", RewardCount);
                    break;
                case ARENA_TEAM_3v3:
                    //ArenaRewardItem(player, bgTeamId, winnerTeamId, "3v3", RewardCount);
                    break;
                case ARENA_TEAM_5v5:
                    //ArenaRewardItem(player, bgTeamId, winnerTeamId, "5v5", RewardCount);
                    break;
            }
        }
    }

    void ArenaRewardItem(Player* player, TeamId bgTeamId, TeamId winnerTeamId, std::string Type, uint32 RewardCount)
    {
        if (bgTeamId == winnerTeamId)
            player->AddItem(29434, RewardCount);
        else
            player->AddItem(29434, RewardCount);
    }
};

void AddSC_BattlegroundsReward()
{
    new BGScript_BattlegroundsReward();
}
