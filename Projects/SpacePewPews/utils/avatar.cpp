#include "avatar.h"

#pragma region Big Four
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
#pragma endregion

/*
    Cstring paramter Ctor.

    @params filePath - full path to the file holding the char map.
 */
Avatar::Avatar(const char *filePath) : Avatar()
{
    open_file(filePath);
}

/*
    Checks if the passed in files format is valid.
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
            in the stream IS NOT an end of line specifier.
         */
        charMap.getline(rowData, MAX_AVATAR_DIMENSIONS + 1);

        if (charMap.fail())
            return false;

        ++rows;
        charMap.peek();
    }
    /*
        we clear the eofbit and failbit
        so we can re-read the file to actually extract the data from it
        since if failbit and/or badbit were set off
        we would've returned false already. 
     */
    charMap.clear();

    //start from the beginning of the file again.
    charMap.seekg(std::ios::beg);

    //will return false if there aren't enough or too many rows in the file.
    return (rows <= MAX_AVATAR_DIMENSIONS) && (rows > 0);
}

/*
    Extracts the charmap from the file after validating the file.

    @params charMap - stream containing the char map to be extracted.
 */
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
            /*
                We get each rows length every time so we can
                get the exact char map dimensions which will help us
                whe we print the window. 
             */
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