#include "FirstPlugin.h"
#include "Register.h"

void FirstPlugin::run() {
    cout << "FisrtPlugin run ...." << endl;
}

string FirstPlugin::name() {
    return "FirstPlugin";
}

register_plugin(FirstPlugin);


