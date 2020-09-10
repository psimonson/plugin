#include <stdio.h>
#include "plugin_manager.h"

SET_PLUGIN_TYPE(PM_COMMAND);

int init_plugin(plugin_manager_t *pm)
{
	printf("Welcome to %s!\n\nHello world!\n", PluginManager_getName(pm));
	return 0;
}
