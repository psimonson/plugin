#ifndef _PLUGIN_MANAGER_H_
#define _PLUGIN_MANAGER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct plugin_manager plugin_manager_t;

int PluginManager_register(void);
int PluginManager_init(const char *dirname);
int PluginManager_exec(size_t id);
void PluginManager_print(void);
void PluginManager_destroy(void);
const char *PluginManager_getName(plugin_manager_t *pm);

#ifdef __cplusplus
}
#endif

#endif
