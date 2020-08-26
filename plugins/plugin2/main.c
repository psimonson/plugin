#include <stdio.h>
#include "../../plugin_manager.h"

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

	printf("Please enter your name? ");
	(void)get_line(buf, sizeof(buf), stdin);
	printf("Welcome to plugin2!\n\nHello, %s.\n", buf);

	return 0;
}
