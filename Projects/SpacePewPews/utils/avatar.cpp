#include "avatar.h"

Avatar::Avatar() : data()
{
}

Avatar::Avatar(const Avatar &rhs) : data(rhs.data)
{
}

Avatar &Avatar::operator=(const Avatar &rhs)
{
    if (this != &rhs)
    {
        data = rhs.data;
    }
    return *this;
}

Avatar::~Avatar()
{
}

Avatar::Avatar(const char *filePath) : Avatar()
{
    open_file(filePath);
}

/*
    Checks if the passed if files format is valid.
 */
bool Avatar::valid_file(std::ifstream &charMap) const
{
    int rows = 0;
    char rowData[MAX_AVATAR_DIMENSIONS];

    int currRowLen = 0;

    while (charMap.good())
    {
        /*
            We try reading 11 characters 
            so we can set the failbit to true
            if we've read n-1 characters already and the next character
            in the stream IS NOT and end of line specifier.
         */
        charMap.getline(rowData, MAX_AVATAR_DIMENSIONS + 1);

        /*
         printf("failbit: %d\n", charMap.rdstate() & charMap.failbit);
         printf("eofbit: %d\n", charMap.rdstate() & charMap.eofbit);
        */

        /*
            Checks if ONLY the failbit flag is set
            which in our case would mean that the line is too long.

            If both eofbit and failbit have been set
            it's due to getline setting both flags to true
            when reaching the end of the file which will cause us to exist
            on the next while loop iteration.
         */
        if ((charMap.rdstate() & charMap.failbit) != 0 &&
            (charMap.rdstate() & charMap.eofbit) == 0)
        {
            return false;
        }
        ++rows;
        charMap.peek();
    }
    charMap.clear();
    charMap.seekg(std::ios::beg);
    return (rows <= MAX_AVATAR_DIMENSIONS) && (rows > 0);
}

void Avatar::extract_data(std::ifstream &charMap)
{

    if (valid_file(charMap))
    {
        char **temp = new char *[MAX_AVATAR_DIMENSIONS];
        for (unsigned int r = 0; r < MAX_AVATAR_DIMENSIONS; ++r)
            temp[r] = new char[MAX_AVATAR_DIMENSIONS + 1]{};

        int row = 0;
        int maxRowLen = 0;
        int currRowLen = 0;

        while (charMap.good())
        {
            charMap.getline(temp[row], MAX_AVATAR_DIMENSIONS + 1);
            currRowLen = strlen(temp[row++]);
            maxRowLen = currRowLen > maxRowLen ? currRowLen : maxRowLen;
            charMap.peek();
        }

        data.copy_data(row,
                       maxRowLen,
                       temp);

        for (unsigned int r = 0; r < MAX_AVATAR_DIMENSIONS; ++r)
            delete[] temp[r];
        delete[] temp;
    }
    else
        throw InvalidFileFormat(MAX_AVATAR_DIMENSIONS, MAX_AVATAR_DIMENSIONS + 1);
}

void Avatar::open_file(const char *filePath)
{
    std::ifstream charMap(filePath);

    if (charMap)
    {
        try
        {
            extract_data(charMap);
            charMap.close();
        }
        catch (InvalidFileFormat &iff)
        {
            charMap.close();
            throw iff;
        }
    }
    else
        throw FileNotOpen(filePath);
}

array2D<char> Avatar::get_data() const
{
    return data;
}