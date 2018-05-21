#include "LinkPost.h"

//Default ctor.
LinkPost::LinkPost() : Post(), description()
{
}

/*
    String and User parameter ctor.

    @params address- holds an url.
    @params rhsDescription- holds a description for the url.
    @params rhsOwner - pointer to the creator of the post.
*/
LinkPost::LinkPost(const String &address,
                   const String &rhsDescription,
                   const User *rhsCreator) : Post(address,
                                                  rhsCreator),
                                             description(rhsDescription)
{
}

/*
    Generates a valid html link string.

    @return value:
    
    String object with value:
    <a href="(url held in the data attribute)">(description attribute value)</a>
 */
const String LinkPost::generate_html_string() const
{
    String result("<a href=\"");
    result.append(data.get_cstr());
    result.append("\">");
    result.append(description.get_cstr());
    result.append("</a>");

    return result;
}
