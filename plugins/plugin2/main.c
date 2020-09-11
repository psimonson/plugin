/*
 * Author: Philip R. Simonson
 * Description: Simple hello world plugin.
 * Date: Sep 9, 2020
 *
 ************************************************************************
 */

#include <stdio.h>

#include "plugin_manager.h"

SET_PLUGIN_TYPE(PM_NORMAL);

/* Get user input from the keyboard.
 */
int get_line(char *buf, int size, FILE *fp)
{
	int c, i;

	for(i = 0; i < size-1 && ((c = fgetc(fp)) != EOF && c != '\n'); i++)
		buf[i] = c;
	buf[i] = 0;
	return i-1;
}
/* Entry point for program.
 */
int init_plugin(plugin_manager_t *pm)
{
	char buf[64];

	printf("Welcome to %s!\n\n", PluginManager_getName(pm));
	printf("Please enter your name? ");
	(void)get_line(buf, sizeof(buf), stdin);
	printf("Hello, %s.\n", buf);

	return 0; // Can return anything in a normal plugin, but
						// in a command extension plugin has to be 1.
}
