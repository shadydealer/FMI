#include "htmlController.h"

#define DEFAULT_START_TAGS "<html>\n<body>\n"
#define DEFAULT_END_TAGS "</html>\n</body>"

/*
    creates an html file with a given file name 
    and populates it with the passed in html string.

    @params fileName - name of the html file we're creating.
    @param htmlString - html format string we're populating the file with.
 
    @return value:
        True if the file creation was successful.
        False otherwise.
 */
bool HTMLController::create_html_file(const String &fileName, const String &htmlString)
{
    std::ofstream out(fileName.get_cstr());

    if (out.is_open())
    {
        out << DEFAULT_START_TAGS;
        out << htmlString.get_cstr();
        out << DEFAULT_END_TAGS;
        
        out.close();
        printf("Successfully created %s.\n", fileName.get_cstr());
        return true;
    }
    printf("Failed to create %s.\n", fileName.get_cstr());
    return false;
}