
#include "DynamicLibrary.h"
#include <cstdio>
#include <dlfcn.h>

DynamicLibrary* DynamicLibrary::load(const std::string& path) {
    if (path.empty()) {
        fprintf(stderr, "Failed to load library: Empty path\n");
        return NULL;
    }

    ///void* handle = ::dlopen(path.c_str(), RTLD_LAZY);
    void* handle = ::dlopen(path.c_str(), RTLD_NOW|RTLD_GLOBAL);
    if (NULL == handle) {
        const char* error_string = ::dlerror();
        fprintf(stderr, "Failed to laod library %s", path.c_str());
        if (error_string) {
            fprintf(stderr, " OS returned error: %s", error_string);
            fprintf(stderr, "\n");
            return NULL;
        }
    }
    return new DynamicLibrary(handle);
}

DynamicLibrary::~DynamicLibrary() {
    if (_handle) {
        ::dlclose(_handle);
    }
}

void* DynamicLibrary::get_symbol(const std::string& symbol) {
    if (NULL == _handle) {
        fprintf(stderr, "Cannot inspect library symbols, library is not loaded.\n");
        return NULL;
    }

    void* res = (void*)(::dlsym(_handle, symbol.c_str()));
    if (NULL == res) {
        fprintf(stderr, "Library symbol %s not found", symbol.c_str());
        return NULL;
    }
    return res;
}

DynamicLibrary::DynamicLibrary(void* handle) : _handle(handle) {
}
