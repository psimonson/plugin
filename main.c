#include <stdio.h>
#include "plugin_manager.h"

int main(void)
{
	PluginManager_Init("plugins");
	PluginManager_Print();
	PluginManager_Exec(0);
	PluginManager_Exec(1);
	PluginManager_Destroy();
	return 0;
}
