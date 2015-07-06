#include "../Plugin.h"
#include "../PluginManager.h"
#include <iostream>

using namespace std;

class FirstPlugin : public Plugin{
public:
    void run();
    string name();
};

