#include <string>
#include <vector>
#ifndef hangman_h
#define hangman_h
class Hangman {
public:    
int numGuesses = 3;
int maxGuesses = 5;
int wordlength;
std::string word;
std::string currBoard;
std::vector<std::string> dictionary;
bool hasLost = false;

std::vector<std::string> loadDictionary(std::string filename);
void displayBoard();
void handleInput();
void update(char c);
void play();
bool isCorrect();
std::vector<char> lettersGuessed;
std::string tolower(std::string &s);
Hangman();

private:

};



#endif