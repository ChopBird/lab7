
#include "evilhangman.h"
#include <iostream>
#include <map>
int calculateWordScore(std::string word, char c);


int evilhangman::promptLength(){
    bool validNum = false;
    int chosenNum;
    std::cout << "How long should the word be?" << std::endl;
    
    while(true){
        std::cin >> chosenNum;
        for (auto word : dictionary){
            if (word.length() == chosenNum) return chosenNum;
         }
        std::cout <<"that was invalid idk \n";
    }
}
void evilhangman::play(){
        //dictionary from: https://github.com/jonbcard/scrabble-bot/blob/master/src/dictionary.txt
    dictionary = loadDictionary("dictionary.txt");

    wordlength = promptLength();
    
    initWordList();
    currBoard = std::string(wordlength,'_');
   
    while(!hasLost){
        std::cout<<"words left: "<< possibleWords.size() <<std::endl;
        std::cout << "tries left: " << numGuesses << "\n";
        update(handleInput());
        if (possibleWords.size() == 1 && possibleWords[0] == currBoard) break;
    }
    if(hasLost) 
    std::cout << "you lose :(" <<std::endl;
    else 
    std::cout << "YOU WIN :D"<<std::endl;
    std::cout << possibleWords[0]<<std::endl;
}
void evilhangman::initWordList(){
    for (auto w : dictionary){
        if (w.length() == wordlength) possibleWords.push_back(w);
    }
}
std::map<long,std::vector<std::string>> evilhangman::computeFamilies(char c){
    std::map<long,std::vector<std::string>> ret;
    int curWordscore;
    for(auto word : possibleWords){
        //checks if word family exists, if not create, if add word to family vec
        auto score = calculateWordScore(word,c);
        if (auto search = ret.find(score); search!= ret.end())
            search->second.push_back(word);
        else if(score == 0) continue;
        else ret.insert(std::pair<long,std::vector<std::string>>{score,std::vector<std::string>{word}});
    }
    return ret;
}
/*Calculates family of word wrt a particular char 
by adding 2^index where c is at index which should
give a unique family based on position*/
int calculateWordScore(std::string word, char c){
    int score = 0;
    for (int i = 0; i<word.size(); i++){
        score += (word[i]==c)*(2<<i);
    }
    return score;
}
void evilhangman::update(char c){
    auto families = computeFamilies(c);
    int biggestKey = 0;
    int biggestSize = 0;
    if (families.empty()){
        numGuesses--;
        std::cout <<"No family :( \n";
        if (numGuesses==0) hasLost = true;
        displayBoard();
        return;
    }
    for (auto pair : families){
        if (pair.second.size()>biggestSize){
            biggestKey = pair.first;
            biggestSize = pair.second.size();
        }
    }
    possibleWords = families.find(biggestKey)->second;
    
    for (int i = 0; i < wordlength;i++){
    
    if (possibleWords[0][i] == c){
        currBoard[i] = c;
    } 
    
}
    //std::cout << families.find(biggestKey)->second[0];
    possibleWords = families.find(biggestKey)->second;
    displayBoard();

}
evilhangman::evilhangman():Hangman()
{
    
}

evilhangman::~evilhangman()
{
}
