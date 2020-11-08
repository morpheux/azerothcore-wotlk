#!/usr/bin/env bash

MOD_GUILDHOUSE_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"

source $MOD_GUILDHOUSE_ROOT"/conf/conf.sh.dist"

if [ -f $MOD_GUILDHOUSE_ROOT"/conf/conf.sh" ]; then
    source $MOD_GUILDHOUSE_ROOT"/conf/conf.sh"
fi
