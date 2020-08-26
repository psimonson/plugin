#ifndef _PLUGIN_MANAGER_H_
#define _PLUGIN_MANAGER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct plugin_manager plugin_manager_t;

int PluginManager_Init(const char *dirname);
int PluginManager_Exec(size_t id);
void PluginManager_Print(void);
void PluginManager_Destroy(void);

#ifdef __cplusplus
}
#endif

#endif
