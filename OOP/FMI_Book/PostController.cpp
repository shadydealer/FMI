#include "PostController.h"

/*
    Fetches a post from the post list by given id.

    @params id - id of the post we're looking for.s

    @return value:
        PolymorphicList Iterator pointing to the post if we've found it.
        PolymorphicList Iterator pointing to null otherwise.
 */
PolymorphicList<Post>::Iterator PostController::_fetch_post(const unsigned int id)
{
    PolymorphicList<Post>::Iterator it = posts.beg();

    for (; it != posts.end(); ++it)
        if ((it)->get_id())
            break;

    return it;
}
/*
    Generates a post by given type and data.

    @params data- what the post contains.
    @param type -type of the post.

    @return type:
        Pointer to one of the following post types:
            PicturePost
            LinkPost
            TextPost
 */
Post *PostController::create_post(const String &data,
                                  const User *creator,
                                  const PostType type)
{
    if (type == PICTURE_POST)
    {
        return new PicturePost(data, creator);
    }
    if (type == TEXT_POST)
    {
        return new TextPost(data, creator);
    }
    else if (type == LINK_POST)
    {
        const char *runner = data.get_cstr();
        unsigned int linkLength = 0;
        while (*(runner++) != ' ')
            ++linkLength;

        String description(runner);

        runner -= linkLength + 1;

        char *temp = new char[linkLength + 1]{0};
        strncpy(temp, runner, linkLength);

        String link(temp);
        
        delete[] temp;
        
        return new LinkPost(link, description, creator);
    };
}

/*
    Adds a post to the end of the post list.

    @params rhs- post to be added.
 */
void PostController::add_post(Post *rhs)
{
    posts.push_back(rhs);
}

/*
    Removes a po`st from the post list by given id.

    @params id- id o`f the post we want to remove.

 */
void PostController::remove_post(const unsigned int id)
{
    PolymorphicList<Post>::Iterator it = _fetch_post(id);

    if (it)
    {
        posts.remove(it);
        printf("Successfully removed post %d.\n", id);
        return;
    }

    printf("Failed to remove post %d.\n", id);
}

/*
    Fetches a post by id.

    @params id- id of the post.

    @return value:
        Pointer to a post object if we've found the post.
        Pointer to null otherwise.
 */
Post * PostController::fetch_post(const unsigned int id)
{
    PolymorphicList<Post>::Iterator it = _fetch_post(id);
    if (it)
        return (&(*it));

    return nullptr;
}

/*
    Generates an html file with a name: <id>.html
    containing a single post.

    @params id - id of the post.
 */
void PostController::generate_single_post_html(const unsigned int id)
{
    String fileName((String::ull_to_string(id)).get_cstr());
    fileName.append(".html");

    PolymorphicList<Post>::Iterator it = _fetch_post(id);

    if (it)
    {
        HTMLController::create_html_file(fileName, it->generate_html_string());
    }
    else
        printf("Post %d does not exist.\n", id);
}

/*
    Generates an html file with the name:<providerNickName>.html
    containing all the posts of a specific user.
`
    @params providerNickName - nickName of the user we're getting the information of.
 */
void PostController::generate_full_post_history(const String &providerNickName)
{
    String fileName (providerNickName.get_cstr());
    fileName.append(".html");

    PolymorphicList<Post>::Iterator it = posts.beg();

    String data;

    for (; it != posts.end(); ++it)
    {
        if (it->get_creator()->get_nickname() == providerNickName)
        {
            data.append("\n");
            data.append(it->generate_html_string().get_cstr());
        }
    }

    if (data.get_cstr())
    {
        HTMLController::create_html_file(fileName, data);
        printf("Successfully generated an html file containg all the posts of %s.\n",
               providerNickName.get_cstr());
    }
    else
        printf("Failed to generate an html containing all the posts of %s.\n",
               providerNickName.get_cstr());
}