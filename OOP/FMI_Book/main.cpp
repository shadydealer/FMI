#include <stdio.h>

#include "String.h"
#include "User.h"
#include "Moderator.h"
#include "Administrator.h"

#include "PicturePost.h"
#include "LinkPost.h"
#include "TextPost.h"

#include "UserController.h"
#include "PostController.h"
#include "typeinfo"

void RunTests();

int main()
{
    RunTests();
    return 0;
}

void RunTests()
{
    UserController users;
    String figString = "Fig";
    Moderator fig(figString, 2);
    users.add_user(&fig);
    User *temp = users.fetch_user(figString);
    printf("%s %d\n", temp->get_nickname().get_cstr(), temp->get_age());
    printf("%s\n", typeid(*temp).name());

    String randomPath(" /home/shadydealer/Desktop/city_by_dabana-d5nwexv.jpg");
    PostController posts;
    PicturePost pp(randomPath, temp);
    posts.add_post(&pp);
    posts.add_post(&pp);
    posts.add_post(&pp);
    posts.add_post(&pp);
    posts.generate_single_post_html(fig.get_nickname(), 1);
    posts.generate_full_post_history(fig.get_nickname(),fig.get_nickname());
    users.remove_user(figString);
    temp = users.fetch_user(figString);
}