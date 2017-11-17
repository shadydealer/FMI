#include <iostream>
#include <fstream>
#include <cstring>

std::ifstream &operator>>(std::ifstream &in, char *&buffer);
int main()
{
    std::ifstream in("Tests.txt");

    //check if the file is open.
    if (in.is_open())
    {
        while (!in.eof())
        {
            char *buffer;
            in >> buffer;
            std::cout << buffer << std::endl;
        }
    }

    in.close();

    return 0;
}

std::ifstream &operator>>(std::ifstream &in, char *&buffer)
{
    int length = 1024; //holds the current length of the buffer.
    int count = 0;     // holds the amount of characters read from the stream.
    buffer = new char[length];
    char *temp;

    //
    // getline() checks for end of file internally and sets the eofbit if
    //the end of file is reached "prematurely"(before reading *length* characters from the stream)
    //or if it still hasn't been read from the stream.
    //
    // we will keep reading from the stream until either eof or a '\n' character is reached.
    //Once we've entered the loop, that means we've not read everything from the stream.
    while (!in.getline(buffer, length).good())
    {

        //return the buffer pointer to the beginning of the allocated space everytime,
        //so we can copy all of the characters we've read so far.
        buffer -= count;

        //get the amount of characters we've read from the stream.
        count += in.gcount();

        //we will allocate enough space to store the currently read characters from the stream.
        temp = new char[length + count];

        //coppy the characters we've read so far.
        strcpy(temp, buffer);

        //free the currently allocated space.
        delete[] buffer;

        //set the buffer pointer to the beginning of the newly allocated space.
        buffer = temp;

        //move the buffer pointer forward,
        //because when we reset the flags,
        //we will keep reading from the point we've last gotten to.
        buffer += count;

        //reset the flags from the stream so we can read from it again.
        in.clear();
    }

    //move it back to the beginning once we've left the while loop
    buffer -= count;

    //checks if there are any more characters left to read and sets eof if there aren't.
    in.peek();
    return in;
}
