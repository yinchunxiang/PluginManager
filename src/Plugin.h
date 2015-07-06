#ifndef __PLUGIN_H__
#define __PLUGIN_H__ 

#include <string>

using namespace std;


#define ANYTHING_TO_STRING(X) #X

class Plugin {
public:
    virtual void run() = 0;
    virtual string name() = 0;
};



#define regist_plugin(clazz)\
PluginManager::get_instance()->add_plugin(ANYTHING_TO_STRING(clazz), new clazz());


#endif

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100 */
