/*
 * Author: Philip R. Simonson
 * Description: Plugin manager header (see plugin_manager.c for more info).
 * Date: Sep 8, 2020
 *
 ****************************************************************************
 */

#ifndef _PLUGIN_MANAGER_H_
#define _PLUGIN_MANAGER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct plugin_manager plugin_manager_t;

int PluginManager_register(void);
int PluginManager_init(const char *dirname);
int PluginManager_exec(size_t id);
size_t PluginManager_search(const char *name);
void PluginManager_print(void);
void PluginManager_destroy(void);
const char *PluginManager_getName(plugin_manager_t *pm);

#ifdef __cplusplus
}
#endif

#endif
