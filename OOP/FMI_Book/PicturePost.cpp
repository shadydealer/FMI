#include "PicturePost.h"

//Default ctor.
PicturePost::PicturePost() : Post()
{
}

/*
    String and User parameter ctor.

    @params picturePath- holds the path to a picture.
    @params rhsOwner - pointer to the creator of the post.
*/
PicturePost::PicturePost(const String &picturePath,
                         const User *rhsCreator) : Post(picturePath,
                                                      rhsCreator)
{
}

/*
    Generates a valid html image string.

    @return value:
    String object with value:
    <img="(image url held in the data attribute)">
 */
const String PicturePost::generate_html_string() const
{
    String result("<img src=\"");
    result.append(data.get_cstr());
    result.append("\">");

    return result;
}