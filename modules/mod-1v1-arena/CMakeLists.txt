# Set Path
CU_SET_PATH("CMAKE_1V1_ARENA_DIR" "${CMAKE_CURRENT_LIST_DIR}")

# Add script files
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/npc_arena1v1.cpp")

# Add scripts to script loader
AC_ADD_SCRIPT_LOADER("1v1Arena" "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")

# Add config file
AC_ADD_CONFIG_FILE("${CMAKE_CURRENT_LIST_DIR}/conf/1v1arena.conf.dist")
CU_ADD_HOOK(AFTER_WORLDSERVER_CMAKE "${CMAKE_CURRENT_LIST_DIR}/src/cmake/after_ws_install.cmake")



