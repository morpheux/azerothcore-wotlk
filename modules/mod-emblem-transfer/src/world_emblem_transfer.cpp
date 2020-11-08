#include "Configuration/Config.h"
#include "ScriptMgr.h"

class world_emblem_transfer : public WorldScript
{
public:
    world_emblem_transfer() : WorldScript("world_emblem_transfer") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            std::string conf_path = _CONF_DIR;
            std::string cfg_file = conf_path + "/emblem_transfer.conf";
            std::string cfg_def_file = cfg_file +".dist";

            sConfigMgr->LoadMore(cfg_def_file.c_str());
            sConfigMgr->LoadMore(cfg_file.c_str());
        }
    }
};

void AddWorldEmblemTransferScripts()
{
    new world_emblem_transfer();
}
