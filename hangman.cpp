#include "hangman.h"
#include <string> 
#include <iostream>
#include <fstream>

/*return lower case version of s*/
std::string Hangman::tolower(std::string &s){
    for (int i = 0; i < s.length();i++){
        s[i] = std::tolower(s[i]);
    }
    return s;
}

Hangman::Hangman(){}
void Hangman::displayBoard(){
    std::cout<< currBoard << std::endl;
}
void Hangman::handleInput(){
char input = 0;
std::cout << "enter character" << std::endl;
std::cin >> input;

update(input);
}

void Hangman::update(char c){
bool correct = false;
for (int i = 0; i < wordlength;i++){
    if (word[i] == c){
        currBoard[i] = c;
        correct = true;
    } 
    
}
if (!correct) numGuesses--;
if (numGuesses == 0) hasLost = true;
displayBoard();
}



std::vector<std::string> Hangman::loadDictionary(std::string filename){
    std::ifstream fs;
    std::vector<std::string> ret;
    std::string word;
    char worder[30];
    fs.open(filename);
    while (!fs.eof()){
    getline(fs,word);
    ret.push_back(this->tolower(word));
    }
    fs.close();
    return ret;
}
void Hangman::play(){
    
    //dictionary from: https://github.com/jonbcard/scrabble-bot/blob/master/src/dictionary.txt
    dictionary = loadDictionary("dictionary.txt");

    
    word = dictionary[rand()%dictionary.size()];
    wordlength = word.size();
    currBoard = std::string(word.length(),'_');
    std::cout<<"word is: "<< word <<std::endl;
    while(!hasLost){
        handleInput();
        if (word == currBoard) break;
    }
    std::cout<<"YOU WIN\n";
}
