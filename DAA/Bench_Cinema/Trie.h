#pragma once
#include <vector>
#include <string>
#include <stack>

class TrieNode;

struct Node
{
    char letter;
    unsigned int counter;
    TrieNode * next;
    ~Node();
};

struct TrieNode
{
    Node * alphabet;
    TrieNode();
    ~TrieNode();
};

class Trie
{
    private:
    TrieNode * root;
    
    public:
    Trie();
    std::vector<std::string> sort();
    void add(const std::string &);
    ~Trie();
};