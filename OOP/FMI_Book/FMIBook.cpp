#include "FMIBook.h"

FMIBook::FMIBook(const String &adminName,
                 const unsigned int adminAge) : admin(adminName, adminAge),
                                                users(),
                                                posts()
{
}

/*
    Adds a user by given nickname and age.

    @params nickName - nick name of the user.
    @params age - age of the user.

 */
void FMIBook::add_user(const String &nickName, const unsigned int age)
{
    users.add_user(nickName, age, USER);
}

/*
    Adds a moderator by given nickname and age.

    @params nickName - nick name of the moderator.
    @params age - age of the moderator.

 */
void FMIBook::add_moderator(const String &nickName, const unsigned int age)
{
    return users.add_user(nickName, age, MODERATOR);
}

/*
    Removes a user from the list of users by given nickname.

    @params nickName - name of the user we want removed.
 */
void FMIBook::remove_user(const String &nickName)
{
    users.remove_user(nickName);
}

/*
    Block user with receiverNickName as nickname if
    user with actorNickName has permission to do so.

    @params actorNickName - nickName of the user that does the blocking.
    @params receiverNickName - nickName of the user that is getting blocked.
 */
void FMIBook::block_user(const String &actorNickName, const String &receiverNickName)
{
    users.block_user(actorNickName, receiverNickName);
}

/*
    Unblock user with receiverNickName as nickname if
    user with actorNickName has permission to do so.

    @params actorNickName - nickName of the user that does the unblocking.
    @params receiverNickName - nickName of the user that is getting unblocked.
 */
void FMIBook::unblock_user(const String &actorNickName, const String &receiverNickName)
{
    users.unblock_user(actorNickName, receiverNickName);
}
/*
    Changes a users nickname to a new one.

    @params newNickName - the users new nickname.
    @params userCurrNickName - the users current nickname.
 */
void FMIBook::change_nickname(const String &newNickname, const String &userCurrNickName)
{
    User *user = users.fetch_user(userCurrNickName);
    if (user)
    {
        user->change_nickname(newNickname);
        printf("Successfully changed %s to %s", userCurrNickName.get_cstr(), newNickname.get_cstr());
    }
    printf("User doesn't exist.\n");
}
/* 
    Adds a post to the post list if
    the user with userNickName as a nick name isnt banned.

    @params userNickName- nickname of the poster.
    @params postData- data of the post.
    @params postTpe - type of the post.
 */
void FMIBook::make_post(const String &userNickName,
                        const String &postData,
                        const String &postType)
{
    PostType type;
    if (postType == "[image]")
        type = PICTURE_POST;
    else if (postType == "[text]")
        type = TEXT_POST;
    else if (postType == "[url]")
        type = LINK_POST;
    else
    {
        printf("No post type: %s exists.\n", postType.get_cstr());
        return;
    }
    if (userNickName == admin.get_nickname())
    {

        Post *post = posts.create_post(postData, &admin, type);
        posts.add_post(post);
        printf("Successfully created post %d.\n", post->get_id());
        return;
    }
    else
    {
        User *user = users.fetch_user(userNickName);
        if (user)
        {
            if (!user->is_blocked())
            {
                Post *post = posts.create_post(postData, user, type);
                posts.add_post(post);
                printf("Successfully created post %d.\n", post->get_id());
                return;
            }
            printf("%s cannot post because he's blocked.\n", userNickName.get_cstr());
            return;
        }
    }
    printf("Failed to create post. User %s does not exist.\n", userNickName.get_cstr());
}

/*
    Removes a post from the post list by given id if it exists.

    @params id - id of the post we'd like to remove.
 */
void FMIBook::remove_post(const String &userNickName, const unsigned long long id)
{
    Post *post = posts.fetch_post(id);

    if (userNickName == admin.get_nickname())
    {
        if (post)
        {
            posts.remove_post(id);
            printf("Removed post %llu.\n", id);
        }
        else
            printf("Post %llu does not exist.\n", id);
    }
    else
    {
        User *user = users.fetch_user(userNickName);
        if (user)
        {
            if (post)
            {
                if (post->get_creator() == user)
                {
                    posts.remove_post(id);
                    printf("Removed post %llu.\n", id);
                }
                else
                    printf("%s doesn't have permission to remove someone elses post.\n", userNickName.get_cstr());
            }
            else
                printf("Post %llu does not exist.\n", id);
        }
        else
            printf("Users %s does not exist.\n", userNickName.get_cstr());
    }
}

/*
    Generates an html file containing the post data with given id.

    @params id - id of the post we're looking for.
 */
void FMIBook::look_at_single_post(const unsigned int id)
{
    posts.generate_single_post_html(id);
}

/* 
    Generates an html file containing all the posts of a specific user.

    @params providerNickName - nickname of the user whose posts we're looking at. 
 */
void FMIBook::look_at_all_posts(const String &providerNickName)
{
    posts.generate_full_post_history(providerNickName);
}

//Administrator getter method.
Administrator &FMIBook::get_admin()
{
    return admin;
}