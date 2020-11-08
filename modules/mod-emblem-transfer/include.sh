#!/usr/bin/env bash
	
	MOD_EMBLEM_TRANSFER_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"
	
	source $MOD_EMBLEM_TRANSFER_ROOT"/conf/conf.sh.dist"
	
	if [ -f $MOD_EMBLEM_TRANSFER_ROOT"/conf/conf.sh" ]; then
	    source $MOD_EMBLEM_TRANSFER_ROOT"/conf/conf.sh"
	fi
