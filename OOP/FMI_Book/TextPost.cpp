#include "TextPost.h"

//Default ctor.
TextPost::TextPost() : Post()
{
}


/*
    String and User parameter ctor.

    @params text- self explanatory.
    @params rhsOwner - pointer to the creator of the post.
*/
TextPost::TextPost(const String &text,
                   const User *rhsCreator) : Post(text,
                                                  rhsCreator)
{
}

/*
    Generates a valid html paragraph string.

    @return value:
    
    String object containing:
    <p>(data attribute value)</p>
 */
const String TextPost::generate_html_string() const
{
    String result("<p>");
    result.append(data.get_cstr());
    result.append("</p>");

    return result;
}
