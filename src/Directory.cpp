#include "Directory.h"
#include <sys/types.h>
#include <dirent.h>
#include <queue>


Directory::Directory() {
}

Directory::~Directory() {
}

void Directory::list_files(
        std::vector<std::string>& file_vec,
        const std::string& folder,
        const std::string& extension) {

    fprintf(stdout, "start to list files ...\n");
    DIR* dir = opendir(folder.c_str());
    if (NULL == dir) {
        fprintf(stderr, "Could not open %s directory\n", folder.c_str());
        return;
    }

    struct dirent* ent = NULL;
    while (NULL != (ent = readdir(dir))) {
        fprintf(stdout, "==>%s\n", ent->d_name);
        std::string name(ent->d_name);
        ///忽略"."和".."，以及"."开头的文件和文件夹
        if (name.empty() || '.' == name[0] || "." == name || ".." == name) {
            continue;
        }
        std::string path = folder;
        path.append("/");
        path.append(name);
        DIR* sub_dir = opendir(path.c_str());
        if (NULL != sub_dir) {
            /// if it is a folder
            closedir(sub_dir);
            continue;
        }

        /// if it is a file
        if (extension.empty()) {
            file_vec.push_back(path);
        }
        else {
            size_t last_dot = name.find_last_of('.');
            std::string ext = name.substr(last_dot + 1);
            if (extension == ext) {
                file_vec.push_back(path);
            }
        }
    }
    closedir(dir);
}
