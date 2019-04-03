#include <vector>

#ifndef WORDNODE_H
#define WORDNODE_H 1

class WordNode{
public:
    char prefix;
    char suffix;
    std::vector <std::string> wordlist;
    int word_count;
    int word_use;
};

#endif