#include "PluginManager.h"
#include <unordered_map>
#include <string>
typedef std::unordered_map<std::string, Plugin*> PluginMap;
typedef void (*hello_t)();
typedef const PluginMap* (*fn)();

int main(int argc, const char *argv[])
{
    PluginManager* pm = PluginManager::get_instance();
    pm->LoadFromFolder(".");
    /*
    PluginMap::const_iterator it = plugin_map.begin();
    for (; it != plugin_map.end(); ++it) {
        it->second->run();
    }
    */

    const LibMap& lm = pm->libraries();
    fprintf(stdout, "libraries size %lu\n", lm.size());
    
    for (auto& pair : lm) {
        fprintf(stdout, "so name: %s\n", pair.first.c_str());
        fn f = (fn)pair.second->get_symbol("get_global_plugin_map");
        if (NULL == f) {
            fprintf(stdout, "pm is null");
        }
        else {
            const PluginMap* ppm = f();
            fprintf(stdout, "plugin number => %lu\n", ppm->size());
        } 
        hello_t hello = (hello_t)pair.second->get_symbol("hello");
        if (NULL == hello) {
            fprintf(stdout, "hello is null");
        }
        else {
            hello();
        }
    }
    pm = PluginManager::get_instance();
    fprintf(stdout, "plugin_map size %lu\n", pm->plugin_map().size());

    fprintf(stdout, "g_size %lu\n", g_global_plugin_map.size());

    
    return 0;
}
