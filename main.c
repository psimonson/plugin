#include <stdio.h>
#include "plugin_manager.h"

int main(void)
{
	PluginManager_init("plugins");
	PluginManager_print();
	PluginManager_register();
	PluginManager_destroy();
	return 0;
}
