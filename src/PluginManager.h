#ifndef __PLUGIN_MANAGER_H__
#define __PLUGIN_MANAGER_H__ 

#include <vector>
#include <unordered_map>
#include <string>
#include <vector>
#include <mutex>
#include "Plugin.h"
#include "DynamicLibrary.h"

using namespace std;

    typedef unordered_map<string, Plugin*> PluginMap;
    typedef unordered_map<string, DynamicLibrary*> LibMap;
#ifdef _cplusplus
    extern "C" {
#endif
        extern PluginMap g_global_plugin_map;
#ifdef _cplusplus
    }
#endif

class PluginManager {
public:
    static PluginManager* get_instance();
    void add_plugin(const char* plugin_name, Plugin* plugin);
    int LoadFromFolder(const std::string& folder);
    const PluginMap& plugin_map() {
        return _plugin_map;
    }

    const LibMap& libraries() {
        return _libraries;
    }

private:
    PluginManager();
    PluginManager(const PluginManager& pm) = delete;
    static PluginManager* _instance;
    std::string ResolvePathExtension(const std::string& path);
    std::string GetDynamicLibraryName(const std::string& path);
    bool load(const std::string& path);
    
    LibMap _libraries;
    PluginMap _plugin_map;
    static std::once_flag _once_flag;

};

//unordered_map<string, Plugin*> global_plugin_map;


#endif

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100 */
