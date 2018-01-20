#include <iostream>
#include <string.h>
#include <stdlib.h>

#define MIN_EP_AMOUNT 3
#define MAX_EP_AMOUNT 7
#define EXCLS_AMOUNT 3
#define VERBS_AMOUNT 5
#define ENT_AMOUNT 5

struct entity
{
  public:
    char *word;
    bool is_object;
    bool is_subject;

  public:
    entity() = delete;
    entity(const char *rhs_word,
           bool rhs_is_obj,
           bool rhs_is_subj) : word(NULL),
                               is_object(rhs_is_obj),
                               is_subject(rhs_is_subj)
    {
        word = new char[strlen(rhs_word) + 1]();
        strcpy(word, rhs_word);
    }

    ~entity()
    {
        delete[] word;
    }
};

int main()
{
    try
    {
        const char *exclamations[] = {"SHOK", "Skandal", "Nechuvana naglost"};
        const char *verbs[] = {" sgazi", " zadiga", " namiga na", " precaka", " tarashi"};

        entity ent[] = {
            {" Ryapa", 1, 1},
            {" Baba", 1, 1},
            {" Kmet", 1, 1},
            {" Bager", 1, 1},
            {" Sklad", 0, 1}};

        unsigned int headings = 0;
        std::cin >> headings;

        unsigned int excl_ind = 0, excl_p = MIN_EP_AMOUNT, obj_ind = 0, verb_ind = 0, subj_ind = 0;

        unsigned int excl_len = 0, obj_len = 0, verb_len = 0, subj_len = 0;

        char *heading = NULL;

        for (size_t h = 0; h < headings; ++h)
        {
            excl_ind = rand() % EXCLS_AMOUNT;
            excl_p= rand() % MIN_EP_AMOUNT + MAX_EP_AMOUNT;
            do
            {
                obj_ind = rand() % ENT_AMOUNT;
            } while (!ent[obj_ind].is_object);

            do
            {
                subj_ind = rand() % ENT_AMOUNT;
            } while (!ent[subj_ind].is_subject);

            verb_ind = rand() % VERBS_AMOUNT;

            excl_len = strlen(exclamations[excl_ind]);
            obj_len = strlen(ent[obj_ind].word);
            verb_len = strlen(verbs[verb_ind]);
            subj_len = strlen(ent[subj_ind].word);

            heading = new char[excl_len +
                               excl_p +
                               obj_len +
                               verb_len +
                               subj_len + 1]();

            strcpy(heading, exclamations[excl_ind]);
            heading += excl_len;
            for (unsigned int e = 0; e < excl_p; ++e)
                *heading++ = '!';

            strcpy(heading, ent[obj_ind].word);
            heading += obj_len;

            strcpy(heading, verbs[verb_ind]);
            heading += verb_len;

            strcpy(heading, ent[subj_ind].word);
            heading[1] = tolower(heading[1]);

            heading -= (excl_len + excl_p + obj_len + verb_len);
            std::cout << heading << std::endl;

            delete[] heading;
            heading = NULL;
        }

        return 0;
    }
    catch (std::bad_alloc())
    {
        std::cout << "Failed to allocate enough memory.\n";
    }
}