#include "Register.h"

/*
PluginMap* global_plugin_map = new PluginMap();

extern "C" const PluginMap* get_global_plugin_map() {
    return global_plugin_map;
}
*/

extern "C" void hello() {
    fprintf(stdout, "hello world\n");
}


void global_add_plugin(const char* plugin_name, Plugin* plugin) {
    (*g_global_plugin_map)[plugin_name] = plugin;
}
