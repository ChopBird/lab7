#include "hangman.h"
#include <map>
#ifndef evilhangman_h
#define evilhangman_h

class evilhangman:public Hangman
{
private:
    std::vector<std::string> possibleWords;
    std::map<long,std::vector<std::string>> families;

public:
   void play();
       int promptLength();
   void initWordList();
   std::map<long,std::vector<std::string>> computeFamilies(char c);

   void update(char c);

   evilhangman(/* args */);
   ~evilhangman();
};


#endif