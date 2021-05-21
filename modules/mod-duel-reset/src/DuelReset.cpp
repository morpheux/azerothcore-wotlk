/*
 *  Originally written  for TrinityCore by ShinDarth and GigaDev90 (www.trinitycore.org)
 *  Converted as module for AzerothCore by ShinDarth and Yehonal   (www.azerothcore.org)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Pet.h"
#include "SpellInfo.h"
#include "Configuration/Config.h"

class DuelResetScript : public PlayerScript
{
    public:
        DuelResetScript() : PlayerScript("DuelResetScript") { }

        // Called when a duel starts (after 3s countdown)
        void OnDuelStart(Player* player1, Player* player2) override
        {
                // Temporary basic cooldown reset
                player1->RemoveArenaSpellCooldowns();
                player2->RemoveArenaSpellCooldowns();
                player1->SaveHealthBeforeDuel();
                player1->SetHealth(player1->GetMaxHealth());
                player2->SaveHealthBeforeDuel();
                player2->SetHealth(player2->GetMaxHealth());

                // check if player1 class uses mana
                if (player1->getPowerType() == POWER_MANA || player1->getClass() == CLASS_DRUID)
                {
                    player1->SaveManaBeforeDuel();
                    player1->SetPower(POWER_MANA, player1->GetMaxPower(POWER_MANA));
                }

                // check if player2 class uses mana
                if (player2->getPowerType() == POWER_MANA || player2->getClass() == CLASS_DRUID)
                {
                    player2->SaveManaBeforeDuel();
                    player2->SetPower(POWER_MANA, player2->GetMaxPower(POWER_MANA));
                }
        }

        // Called when a duel ends
        void OnDuelEnd(Player* winner, Player* loser, DuelCompleteType /*type*/) override
        {
            // Temporary basic cooldown reset
            winner->SetHealth(winner->GetMaxHealth());
            loser->SetHealth(loser->GetMaxHealth());
            //winner->RemoveAllSpellCooldown();
            //loser->RemoveAllSpellCooldown();

            // check if player1 class uses mana
            if (winner->getPowerType() == POWER_MANA || winner->getClass() == CLASS_DRUID)
            {
                winner->SaveManaBeforeDuel();
                winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA));
            }

            // check if player2 class uses mana
            if (loser->getPowerType() == POWER_MANA || loser->getClass() == CLASS_DRUID)
            {
                loser->SaveManaBeforeDuel();
                loser->SetPower(POWER_MANA, loser->GetMaxPower(POWER_MANA));
            }
        }
};

void AddSC_DuelReset()
{
    new DuelResetScript();
}
