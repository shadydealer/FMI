#include "Trie.h"
#include <iostream>

#define LETTERS 53

Node::~Node()
{
    delete next;
}

TrieNode::TrieNode() : alphabet(new Node[LETTERS])
{
    alphabet[0].letter = ' ';
    alphabet[0].counter = 0;
    alphabet[0].next = NULL;

    char curr_letter = 'A';
    unsigned int index = 1;

    while (curr_letter != ('Z' + 1))
    {
        alphabet[index].letter = curr_letter++;
        alphabet[index].counter = 0;
        alphabet[index++].next = NULL;
    }

    curr_letter = 'a';

    while (curr_letter != ('z' + 1))
    {
        alphabet[index].letter = curr_letter++;
        alphabet[index].counter = 0;
        alphabet[index++].next = NULL;
    }
}

TrieNode::~TrieNode()
{
    delete[] alphabet;
}

Trie::Trie() : root(new TrieNode)
{
}

Trie::~Trie()
{
    delete root;
}

const unsigned int map_char(const char c)
{
    unsigned int result = 32;
    if (c >= 'A' && c <= 'Z')
        result = 64;
    else if (c >= 'a' && c <= 'z')
        result = 70;
    return result;
}
void Trie::add(const std::string &rhs_str)
{
    std::string::const_iterator i = rhs_str.begin();
    unsigned int shift = 0;
    TrieNode *curr = root;

    for (; i != rhs_str.end(); ++i)
    {
        shift = map_char(*i);
        if (curr)
        {
            if (i + 1 == rhs_str.end())
            {
                curr->alphabet[*i - shift].counter += 1;
                return;
            }

            curr = (curr->alphabet[*i - shift].next) ? curr->alphabet[*i - shift].next : curr->alphabet[*i - shift].next = new TrieNode();
        }
    }
}

std::vector<std::string> Trie::sort()
{
    std::vector<std::string> result;
    std::stack<Node *> dfsStack;
    std::string currString;

    int count = 0;
    Node *curr = NULL;

    for (int n = 52; n >= 0; --n)
    {
        if (root->alphabet[n].next || 
            root->alphabet[n].counter)
            dfsStack.push(&(root->alphabet[n]));
    }

    while (!dfsStack.empty())
    {
        curr = dfsStack.top();
        dfsStack.pop();

        currString.append(1, curr->letter);

        count = curr->counter;
        for (int c = 0; c < count; ++c)
            result.push_back(currString);

        if (!curr->next)
        {
            currString.erase(currString.length() - 1);
            if (curr->letter == 'z')
                currString.erase(currString.length() - 1);
        }
        else
        {
            for (int n = 52; n >= 0; --n)
                    dfsStack.push(&(curr->next->alphabet[n]));
        }
    }

    return result;
}