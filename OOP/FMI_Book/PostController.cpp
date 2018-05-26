#include "PostController.h"

/*
    Fetches a post from the post list by given id.

    @params id - id of the post we're looking for.s

    @return value:
        PolymorphicList Iterator pointing to the post if we've found it.
        PolymorphicList Iterator pointing to null otherwise.
 */
PolymorphicList<const Post>::Iterator PostController::_fetch_post(const unsigned int id)
{
    PolymorphicList<const Post>::Iterator it = posts.beg();

    for (; it != posts.end(); ++it)
        if ((it)->get_id())
            break;

    return it;
}

/*
    Adds a post to the end of the post list.

    @params rhs- post to be added.
 */
bool PostController::add_post(const Post *rhs)
{
    posts.push_back(rhs);
}

/*
    Removes a post from the post list by given id.

    @params id- id of the post we want to remove.

    @return value:
        True if there's a post with the specified id in the list.
        False otherwise.
 */
bool PostController::remove_post(const unsigned int id)
{
    PolymorphicList<const Post>::Iterator it = _fetch_post(id);

    if (it)
    {
        posts.remove(it);
        printf("Successfully removed post %d.\n", id);
        return true;
    }

    printf("Failed to remove post %d.\n", id);
    return false;
}

/*
    Generates an html file with a name: <nickName>_<id>.html
    containing a single post.

    @params nickName - nickname of the user we're creating to file for.
    @params id - id of the post.
 */
void PostController::generate_single_post_html(const String &nickName, const unsigned int id)
{
    String fileName(nickName);
    fileName.append("_");
    fileName.append((String::ull_to_string(id)).get_cstr());
    fileName.append(".html");

    PolymorphicList<const Post>::Iterator it = _fetch_post(id);

    if (it)
    {
        HTMLController::create_html_file(fileName, it->generate_html_string());
        printf("Successfully generated %s.\n", fileName.get_cstr());
    }
    else
        printf("Failed to generate %s.\n", fileName.get_cstr());
}

/*
    Generates an html file with the name:<nickName>.html
    containing all the posts of a specific user.

    @params recieverNickName - nickName of the user we're creating the file for.
    @params providerNickName - nickName of the user we're getting the information of.
 */
void PostController::generate_full_post_history(const String &receiverNickName, const String &providerNickName)
{
    String fileName(receiverNickName);
    fileName.append("_");
    fileName.append(providerNickName.get_cstr());
    fileName.append(".html");

    PolymorphicList<const Post>::Iterator it = posts.beg();

    String data;

    for (; it != posts.end(); ++it)
    {
        if (it->get_creator()->get_nickname() == providerNickName)
        {
            data.append("\n");
            data.append(it->generate_html_string().get_cstr());
        }
    }

    if(data.get_cstr())
    {
        HTMLController::create_html_file(fileName, data);
        printf("Successfully generated an html file containg all the posts of %s.\n",
                providerNickName.get_cstr());
    }
    else
        printf("Failed to generate an html containing all the posts of %s.\n",
                providerNickName.get_cstr());
}