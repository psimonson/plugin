#include <stdio.h>
#include "../../plugin_manager.h"

int init_plugin(plugin_manager_t *pm)
{
	printf("Welcome to plugin1!\n\nHello world!\n");
	return 0;
}
