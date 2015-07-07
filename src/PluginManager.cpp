#include "PluginManager.h"
#include "Directory.h"

PluginMap* g_global_plugin_map = new PluginMap();

PluginManager* PluginManager::_instance = NULL;
std::once_flag PluginManager::_once_flag;

PluginManager::PluginManager() {
    fprintf(stdout, "********* PluginManager called *************\n");
}

void PluginManager::add_plugin(const char* plugin_name, Plugin* plugin) {
    fprintf(stdout, "==> In add_plugin size:%lu\n", _plugin_map.size());
    _plugin_map[plugin_name] = plugin;
    fprintf(stdout, "===> after add_plugin size:%lu\n", _plugin_map.size());
}


PluginManager* PluginManager::get_instance() {
    /*
    fprintf(stdout, "get_instance start ...\n");
    try {
        std::call_once(_once_flag, []{ _instance = new PluginManager();});
    }
    catch (exception& e) {
        fprintf(stdout, "%s\n", e.what());
    }
    fprintf(stdout, "get_instance end ...\n");
    */
    fprintf(stdout, "get_instance start ...\n");
    if (NULL == _instance) {
        _instance = new PluginManager();
    }
    fprintf(stdout, "get_instance end ...\n");
    return _instance;
}

int PluginManager::LoadFromFolder(const std::string& folder) {
    std::vector<std::string> files;
    Directory::list_files(files, folder, "so");
    for (auto& file : files) {
        fprintf(stdout, "find file => %s\n", file.c_str());
    }
    // Try to load every library
    int ret = 0;
    std::vector<std::string>::const_iterator it = files.begin();
    for (; it != files.end(); ++it) {
        if (load(*it)) {
            ++ret;
        }
    }
    return ret;
}

std::string PluginManager::GetDynamicLibraryName(const std::string& path) {
    size_t lastDash = path.find_last_of("/");
    size_t lastDot = path.find_last_of('.');
    if (lastDash == std::string::npos) lastDash = 0;
    else ++lastDash;
    if (lastDot < lastDash || lastDot == std::string::npos){
        // path without extension
        lastDot = path.length();
    }
    return path.substr(lastDash, lastDot-lastDash);
}

std::string PluginManager::ResolvePathExtension(const std::string& path) {
    size_t lastDash = path.find_last_of("/");
    size_t lastDot = path.find_last_of('.');
    if (lastDash == std::string::npos) lastDash = 0;
    else ++lastDash;
    if (lastDot < lastDash || lastDot == std::string::npos){
        // path without extension, add it
        return path + "." + "dylib";
    }
    return path;
}

bool PluginManager::load(const std::string& path) {
    std::string dynamic_library_name = GetDynamicLibraryName(path);
    std::string real_path = ResolvePathExtension(path);
    DynamicLibrary* dl = DynamicLibrary::load(real_path);
    if (NULL == dl) {
        fprintf(stderr, "load dynamic library failed");
        return false;
    }

    _libraries[dynamic_library_name] = dl;
    return true;
}


