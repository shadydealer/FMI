#include <iostream>
#include "LinkedList.h"

int main ()
{
    LinkedList a;

    LinkedList::Iterator it = a.beg();

    a.insert_after(it, "tits");
    ++it;
    a.insert_after(it, "tits2");
    ++it;
    a.insert_after(it, "tits3");
    ++it;
    a.insert_after(it, "tits4");
    ++it;
    a.insert_after(it, "tits5");

    a.remove_at(it);
    ++it;
    ++it;
    std::cout << (*it)->url << std::endl;
    it = a.beg();
    for(; it != a.end(); ++it)
    {
        std::cout <<(*it)->url << std::endl;
    }
    return 0;
}