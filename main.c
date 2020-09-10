/*
 * Author: Philip R. Simonson
 * Description: Shell example showing off my plugin manager.
 * Date: Sep 9, 2020
 *
 ***************************************************************************
 */

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

#include "plugin_manager.h"

/* ----------------- Data Structures and Constants --------------------- */

typedef struct command {
	char *cmd;
	char *help;
	int (*func)(void);
} command_t;

#define MAXBUF 256
#define MAXTOK 256

/* ----------------------------- Macros -------------------------------- */

/* Miscellaneous macros */
#define TO_STR(a) #a
#define DEF_FNC(a) int cmd_##a(void)

/* Macros for building commands. */
#define BEG_CMD static command_t g_commands[] = {
#define ADD_CMD(a,b) {TO_STR(a), b, cmd_##a}
#define END_CMD };
#define CNT_CMD static const int g_cmd_total =\
 sizeof(g_commands)/sizeof(g_commands[0]);

/* -------------------- Prototypes and Commands ------------------------ */

DEF_FNC(version);
DEF_FNC(help);
DEF_FNC(exit);

BEG_CMD
ADD_CMD(version, "Print the version information."),
ADD_CMD(help, "Print the help for this program."),
ADD_CMD(exit, "Quit this application.")
END_CMD
CNT_CMD

/* Version information command.
 */
DEF_FNC(version)
{
	printf("Version 1.0 - By Philip R. Simonson\n");
	return 0;
}
/* Help command, display help for program.
 */
DEF_FNC(help)
{
	printf("*** Available Commands ***\n");
	printf("==========================================================\n");
	for(int i = 0; i < g_cmd_total; i++)
		printf("%s \t- %s\n", g_commands[i].cmd, g_commands[i].help);
	(void)PluginManager_register(PM_COMMAND, -1, NULL);
	printf("==========================================================\n");
	return 0;
}
/* Exit command, quit this shell.
 */
DEF_FNC(exit)
{
	printf("Quitting shell...\n");
	return -1;
}

/* ----------------------- Private Functions --------------------------- */

/* Get a line of user input from keyboard.
 */
static int getln(char *buf, FILE *fp)
{
	int i;

	if(fgets(buf, MAXBUF, fp) == NULL)
		return -1;

	i = strlen(buf);
	while(i >= 0 && (buf[i-1] == '\r' || buf[i-1] == '\n'))
		i--;
	buf[i] = 0;
	return i;
}
/* Split command into tokens.
 */
static char **shell_split(char *buf, int *argc)
{
	static char *tokens[MAXTOK];
	char *tmp;
	int i;

	i = 0;
	tmp = strtok(buf, " \r\n");
	while(tmp != NULL) {
		tokens[i++] = tmp;
		tmp = strtok(NULL, " \r\n");
	}
	tokens[i] = NULL;
	if(argc != NULL) *argc = i;
	return tokens;
}
/* Execute shell command.
 */
static int shell_exec(int argc, char **argv)
{
	for(int i = 0; i < g_cmd_total; i++)
		if(!strcmp(argv[0], g_commands[i].cmd))
			return g_commands[i].func();

	int res = PluginManager_register(PM_COMMAND, argc, argv);
	if(!res) return res;

#ifdef _WIN32
		printf("Not yet implemented!\n");
#else
		int pid = fork();
		if(pid < 0) {
			fprintf(stderr, "Warning: Cannot fork process.\n");
		} else if(pid == 0) {
			int rc = execvp(argv[0], argv);
			if(rc < 0) {
				fprintf(stderr, "Error: Bad command - '%s'.\n", argv[0]);
				return 1;
			} else if(rc > 0) {
				fprintf(stderr, "Error: Command failed.\n");
				return 2;
			}
		} else {
			wait(NULL);
		}
#endif
	return 0;
}

/* ------------------------ Public Functions --------------------------- */

/* Main loop for shell.
 */
int shell_run(void)
{
	char buf[MAXBUF];
	int rc;

	do {
		char **argv = NULL;
		int argc;

		printf("Shell >> ");
		getln(buf, stdin);
		argv = shell_split(buf, &argc);
		rc = shell_exec(argc, argv);
	} while(rc != EOF);
	return -1;
}

/* -------------------------- Entry Point ------------------------------ */

int main(void)
{
	PluginManager_init("plugins");
//	PluginManager_print();
//	PluginManager_register();

	while(shell_run() != EOF);
	PluginManager_destroy();
	return 0;
}
