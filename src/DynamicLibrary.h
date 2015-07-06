#ifndef __DYNAMIC_LIBRARY_H__
#define __DYNAMIC_LIBRARY_H__ 

#include <string>

using namespace std;


class DynamicLibrary{
    public:
        /*
         * \brief Load a library
         * \param Path to the library
         * \return Pointer to the loaded library, or NULL if failed
         */
        static DynamicLibrary* load(const std::string& path);
        ~DynamicLibrary();

        /*
         * \brief Get a symbol from the library
         * \param symbol - Symbol that we are looking for
         * \return Pointer to what the symbol refers to, or NULL if
         * the symbol is not found
         */
        void* get_symbol(const std::string& symbol);
    private:
        /*
         * \brief Default constructor
         * Library instances cannot be created, use load instead
         * \see load
         */
        DynamicLibrary();


        /* \brief Constructor via library handler
         * Used on load function
         * \see load
         */
        DynamicLibrary(void* handle);

    private:
        void* _handle; ///< Library handle
};

#endif
