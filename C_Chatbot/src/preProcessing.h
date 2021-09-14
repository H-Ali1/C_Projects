#ifndef MAIN_C_PREPROCESSING_H
#define MAIN_C_PREPROCESSING_H
#include <stdio.h>

// Function parses users sentence and breaks it into an array of words
// Returns 1 if sentence was parsed correctly
// Otherwise returns 0
int tokenization(char *sentence, const int choice);


// Returns 1 if sentence was parsed correctly
// Otherwise returns 0

// Function removes commonly used phrases from the user sentence
// Returns 0 if no stop words are removed
// Otherwise returns integer greater 0
// Uses https://gist.github.com/sebleier/554280 as list of stop phrases
int removeStopWords();

// Function checks for validity of user input
// Returns 0 if the sentence is valid
// Otherwise returns 1
int validateUserInput(const char *sentence);

// User input is 2d array of chars that hold the processed user input
extern char userInput[100][200]; //holds the words of each
// Is the integer specifying how much of the 2d array is occupied by words
extern int lenUserInput;


#endif //MAIN_C_PREPROCESSING_H
