#include <stdio.h>

#include "String.h"
#include "User.h"
#include "Moderator.h"
#include "Administrator.h"

#include "PicturePost.h"
#include "LinkPost.h"
#include "TextPost.h"

void RunTests();

int main()
{ 
    RunTests();
    return 0;
}

void RunTests()
{
    Administrator god("God");
    User * pleb = god.add_user("Pleb");
    User * demigod = god.add_moderator("Perseus");

    Moderator * dem = dynamic_cast<Moderator *>(demigod);
    
    if(demigod)
    {
        dem->block(*pleb);
        printf("Pleb: %d\n", pleb->is_blocked());
        dem->unblock(*pleb);
        printf("Pleb: %d\n", pleb->is_blocked());
    }

    delete pleb;
    delete demigod;

    PicturePost tits("tits.jpeg", demigod);
    LinkPost shits("shits.com", "shits", demigod);
    TextPost pits("pits", demigod);

    printf("%s\n", tits.generate_html_string().get_cstr());
    printf("%s\n", shits.generate_html_string().get_cstr());
    printf("%s\n", pits.generate_html_string().get_cstr());


}