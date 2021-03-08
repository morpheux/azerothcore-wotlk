#include "Configuration/Config.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include <time.h>

bool Enabled;
uint32 xpAmount;
time_t t = time(NULL);
tm *now = localtime(&t);

class DoubleXpWeekend : public PlayerScript
{
public:
    DoubleXpWeekend() : PlayerScript("DoubleXpWeekend") {}

        void OnLogin(Player* player) override
        {
            if (now->tm_wday == 5 /*Friday*/ || now->tm_wday == 6 /*Satureday*/ || now->tm_wday == 0/*Sunday*/)
                ChatHandler(player->GetSession()).PSendSysMessage("Chegou o Final de Semana!!! XP em Dobro para todos!! Rate: X %u", xpAmount);
        }

        void OnGiveXP(Player* /*p*/, uint32& amount, Unit* /*victim*/) override
        {
            if (now->tm_wday == 5 /*Friday*/ || now->tm_wday == 6 /*Satureday*/ || now->tm_wday == 0/*Sunday*/)
                amount *= 2;
        }
};

void AdddoublexpScripts()
{
    new DoubleXpWeekend();
}
