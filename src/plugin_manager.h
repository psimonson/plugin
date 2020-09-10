/*
 * Author: Philip R. Simonson
 * Description: Plugin manager header (see plugin_manager.c for more info).
 * Date: Sep 8, 2020
 *
 ****************************************************************************
 */

#ifndef _PLUGIN_MANAGER_H_
#define _PLUGIN_MANAGER_H_

#include "export.h"

enum PM_type {
	PM_NORMAL,
	PM_COMMAND,
	PM_TCOUNT
};

#define SET_PLUGIN_TYPE(N) type_plugin((N));

#ifdef __cplusplus
extern "C" {
#endif

typedef struct plugin_manager plugin_manager_t;

PRS_EXPORT int PluginManager_register(int type, int argc, char **argv);
PRS_EXPORT int PluginManager_init(const char *dirname);
PRS_EXPORT int PluginManager_exec(size_t id, int argc, char **argv);
PRS_EXPORT size_t PluginManager_search(const char *name);
PRS_EXPORT void PluginManager_print(void);
PRS_EXPORT void PluginManager_destroy(void);
PRS_EXPORT const char *PluginManager_getName(plugin_manager_t *pm);

#ifdef __cplusplus
}
#endif

#endif
