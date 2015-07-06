#ifndef  __DIRECTORY_H__
#define  __DIRECTORY_H__

#include <string>
#include <vector>


class Directory {
public:
    Directory();
    ~Directory();
    static void list_files(
            std::vector<std::string>& file_vec,
            const std::string& folder,
            const std::string& extension);
};


#endif
