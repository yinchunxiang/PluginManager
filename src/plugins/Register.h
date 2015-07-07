#ifndef __REGISTER_H__
#define __REGISTER_H__

#include <unordered_map>
#include "../Plugin.h"
#include <string>
#include "../PluginManager.h"

typedef std::unordered_map<string, Plugin*> PluginMap;
//extern PluginMap* global_plugin_map;
/*
#ifdef _cplusplus 
extern "C" {
#endif
const PluginMap& get_global_plugin_map();
#ifdef _cplusplus
};
#endif
*/

#define TOSTRING(X) #X

#define register_plugin(clazz)\
    __attribute__((constructor)) void register_##clazz() {\
        PluginManager::get_instance()->add_plugin(#clazz, new clazz());\
        fprintf(stdout, "[%s]constructor ==> plugin:%s \n", __FILE__, #clazz);\
        fprintf(stdout, "[%s]g_global_plugin_map:%p\n", __FILE__, g_global_plugin_map);\
        (*g_global_plugin_map)[#clazz] = new clazz();\
        fprintf(stdout, "[%s]CONSTRUCTOR ==> g_size:%u \n", __FILE__, (*g_global_plugin_map).size());\
    }

        //(*global_plugin_map)[#clazz] = new clazz();\
        //fprintf(stdout, "constructor so map size:%lu\n", (*global_plugin_map).size()); \
typedef void (*hello_t)();

#endif
