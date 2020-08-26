#include <stdio.h>
#include "plugin_manager.h"

int main(void)
{
	PluginManager_init("plugins");
	PluginManager_print();
	PluginManager_exec(0);
	PluginManager_exec(1);
	PluginManager_destroy();
	return 0;
}
