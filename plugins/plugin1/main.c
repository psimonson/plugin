#include <stdio.h>
#include <string.h>

#include "plugin_manager.h"

SET_PLUGIN_TYPE(PM_COMMAND);

/* Command structure. */
typedef struct command {
	char *cmd;
	char *help;
	int (*func)(int argc, char **argv);
} command_t;

/* Some macro definitions. */
#define TO_STR(x) #x
#define DEF_CMD(a) int cmd_##a(int argc, char **argv)
#define BEG_CMD static const command_t g_commands[] = {
#define ADD_CMD(a,b) {TO_STR(a), b, cmd_##a}
#define END_CMD };
#define CNT_CMD static const int g_cmd_total =\
 sizeof(g_commands)/sizeof(g_commands[0]);

/* -------------------------- Commands -------------------------------- */

/* Command prototypes. */
DEF_CMD(dummy);
DEF_CMD(launch);
DEF_CMD(modules);

/* Command definitions. */
BEG_CMD
ADD_CMD(dummy, "This is a dummy command."),
ADD_CMD(launch, "Launch module by name."),
ADD_CMD(modules, "List normal modules.")
END_CMD
CNT_CMD

/* This is a dummy command, just as an example.
 */
DEF_CMD(dummy) {
	if(argc != 1) {
		printf("Usage: %s\n", argv[0]);
		return 0;
	}
	printf("You've used a dummy command!\n");
	return 0;
}
/* Launch command, execute module by name.
 */
DEF_CMD(launch) {
	int rc = 0;
	if(argc != 2) {
		printf("Usage: %s <module-name[.so]>\n", argv[0]);
		return 0;
	}
	--argc;
	++argv;
	rc = PluginManager_exec(PluginManager_search(argv[0]), argc, argv);
	return (int)((rc >= 0) ? 0 : (rc < 0) ? 0 : 1);
}
/* Modules command, list all normal modules.
 */
DEF_CMD(modules) {
	if(argc != 1) {
		printf("Usage: %s\n", argv[0]);
		return 0;
	}
	printf("Command not yet implemented!\n");
	return 0;
}

/* -------------------------- Functions ------------------------------- */

int init_plugin(plugin_manager_t *pm, int argc, char **argv)
{
	if(argc > 0) {
		for(int i = 0; i < g_cmd_total; i++)
			if(!strcmp(g_commands[i].cmd, argv[0]))
				return g_commands[i].func(argc, argv);
	} else {
		for(int i = 0; i < g_cmd_total; i++)
			printf("%s \t - %s\n", g_commands[i].cmd, g_commands[i].help);
	}
	return 1;
}
