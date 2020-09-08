#ifdef _WIN32
#include <windows.h>
#else
#define _GNU_SOURCE
#include <dlfcn.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "vector.h"
#include "plugin_manager.h"

/* ------------------ Constants, Structs, and Variables ------------------- */

/* Main callback function to execute in plugin. */
typedef int (*callback)(plugin_manager_t *pm);

/* Definition of plugin manager structure. */
struct plugin_manager {
	char *name;
	int id;
	callback func;
	void *lib;
} *plugin_manager = NULL;

/* -------------------------- Private Functions --------------------------- */

/* Create a simple plugin manager.
 */
static int PluginManager_add(char *name, int id, callback func, void *lib)
{
	if(name == NULL || func == NULL || lib == NULL) return 1;
	vector_push_back(plugin_manager,
		((struct plugin_manager){name, id, func, lib}));
	return 0;
}
/* Discover plugins in the plugins directory.
 */
static int PluginManager_discover(const char *dirname)
{
	struct dirent *p;
	char dname[260];
	DIR *dir;
	int i, len;

	if(dirname == NULL) {
		strncpy(dname, ".", sizeof(dname));
		len = 1;
	} else {
		strncpy(dname, dirname, sizeof(dname));
		len = strlen(dirname);
	}

	errno = 0;
	if((dir = opendir(dname)) == NULL) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		return 1;
	}

	i = 0;
	while((p = readdir(dir)) != NULL) {
		if((strcmp(p->d_name, ".") && strcmp(p->d_name, "..")) != 0
			&& (strstr(p->d_name, ".dll") || strstr(p->d_name, ".so"))) {
#ifdef _WIN32
			HMODULE lib = NULL;
			char buf[512];

			// Build string for library path.
			strncpy(buf, dname, sizeof(buf));
			if(dname[len-1] != '\\')
				strncat(buf, "\\", 2);
			strncat(buf, p->d_name, strlen(p->d_name));

			lib = LoadLibrary(TEXT(buf));
			if(lib != NULL) {
				callback func = (callback)GetProcAddress(lib, "init_plugin");
				if(func == NULL) {
					fprintf(stderr, "Warning: Could not get main plugin function.\n");
				} else {
					if(!PluginManager_add(strdup(p->d_name), i, func, lib))
						i++;
				}
			} else {
				fprintf(stderr, "Warning: Could not load library.\n");
			}
#else
			void *lib = NULL;
			char buf[512];

			// Build string for library path.
			strncpy(buf, dname, sizeof(buf));
			if(dname[len-1] != '/')
				strncat(buf, "/", 1);
			strncat(buf, p->d_name, strlen(p->d_name));

			errno = 0;
			lib = dlopen(buf, RTLD_LAZY);
			if(lib != NULL) {
				errno = 0;
				callback func = dlsym(lib, "init_plugin");
				if(func == NULL) {
					fprintf(stderr, "Error: %s\n", strerror(errno));
				} else {
					if(!PluginManager_add(p->d_name, i, func, lib))
						i++;
				}
			} else {
				fprintf(stderr, "Error: %s\n", strerror(errno));
			}
#endif
		}
	}
	closedir(dir);

	printf("Total plugins loaded are %d.\n", i);
	return 0;
}

/* --------------------------- Public Functions --------------------------- */

/* Register all plugins at once.
 */
int PluginManager_register(void)
{
	size_t retval = 0, i;

	for(i = 0; i < vector_size(plugin_manager); i++) {
		int rc = PluginManager_exec(i);
		if(rc < 0)
			retval += 1;
	}
	if(retval > 0)
		printf("%lu errors occured during plugin registration.\n", retval);
	return !(retval == 0);
}
/* Initialize the plugin manager.
 */
int PluginManager_init(const char *dir)
{
	return PluginManager_discover(dir);
}
/* Execute plugin main function.
 */
int PluginManager_exec(size_t i)
{
	if(i < vector_size(plugin_manager))
		return plugin_manager[i].func(&plugin_manager[i]);
	return -1;
}
/* Search through all plugins and return index if found.
 */
size_t PluginManager_search(const char *name)
{
	char fname[80];
	size_t i = 0;
	bool found = false;

	memset(fname, 0, sizeof(fname));
	snprintf(fname, sizeof(fname), "%s%s", name,
		strstr(name, ".so") != NULL ? "" : ".so");

	for(i = 0; i < vector_size(plugin_manager); i++) {
		if(!strcmp(fname, plugin_manager[i].name)) {
			found = true;
			break;
		}
	}
	if(!found)
		fprintf(stderr, "PluginManager: Plugin not found.\n");
	return i;
}
/* Print all known plugins.
 */
void PluginManager_print(void)
{
	if(plugin_manager == NULL) {
		fprintf(stderr, "Warning: There were no plugins.\n");
		return;
	}

	printf("====================================\n");
	printf("=         AVAILABLE PLUGINS        =\n");
	printf("====================================\n");
	for(size_t i = 0; i < vector_size(plugin_manager); i++) {
		printf("Plugin [%d]: %s\n", plugin_manager[i].id,
			plugin_manager[i].name);
	}
	printf("====================================\n");
}
/* Destroy the plugin manager.
 */
void PluginManager_destroy(void)
{
	for(size_t i = 0; i < vector_size(plugin_manager); i++) {
#ifdef _WIN32
		FreeLibrary(plugin_manager[i].lib);
		free(plugin_manager[i].name);
#else
		dlclose(plugin_manager[i].lib);
#endif
		plugin_manager[i].func = NULL;
	}
	vector_free(plugin_manager);
}
/* Get name of plugin.
 */
const char *PluginManager_getName(plugin_manager_t *pm)
{
	return (const char *)pm->name;
}
