
#include <string.h>
#include <ctype.h>
#include "preProcessing.h"
#include "fileReadWrite.h"


int lenUserInput;
static int lenHotelCorpus;
static int lenRoomCorpus;
char userInput[100][200];

// Function parses users sentence and breaks it into an array of words
// Returns 1 if sentence was parsed correctly
// Otherwise returns 0
int tokenization(char *sentence, const int choice){
    for(int i = 0; i < lenUserInput; i++){
        strcpy(userInput[i], " ");
    }
    lenUserInput = 0;
    lenHotelCorpus = 0;
    lenRoomCorpus = 0;

    // replace all punctuation with spaces, since we use space as delimiter
    for(int i = 0; i < strlen(sentence); i++)
    {
        if(ispunct(sentence[i]))
        {
            sentence[i] = ' ';
        }
    }
    // adds each word to the tokenized array of words
    // by using space as a delimiter
    for(int i = 0; i < strlen(sentence); i++)
    {
        if(sentence[i] == ' ') {
            char *token = strtok(sentence, " ");

            while( token != NULL )
            {
                // Tokenizes corpus as well as user input using if statements
                if(choice == 0)
                {
                    strcpy(userInput[lenUserInput], token);
                    token = strtok(NULL, " ");
                    lenUserInput++;
                }
                else if(choice == 1)
                {
                    strcpy(arrayHotelBooking[elementInCorpusHotel]->tokensentence[lenHotelCorpus], token);
                    token = strtok(NULL, " ");
                    arrayHotelBooking[elementInCorpusHotel]->arraySizeId +=1;
                    lenHotelCorpus++;

                }
                else if (choice == 2)
                {
                    strcpy(arrayRoomService[elementInCorpusRoom]->tokensentence[lenRoomCorpus], token);
                    token = strtok(NULL, " ");
                    arrayRoomService[elementInCorpusRoom]->arraySizeId +=1;
                    lenRoomCorpus++;
                }
            }
        }
    }
    // Final check to confirm whether sentence was tokenized
    // and added to the array of words
    if(lenUserInput > 0){
        return 1;
    }
    return 0;
}

// Function removes commonly used phrases from the user sentence
// that will not help computer in "understanding" user input
// Returns void as we work on a global variable
int removeStopWords(){

    int switchCheck = 0;
    int removesStopPhrases = 0;
    int counter = 0;

    // will be used to hold userArray but without the stop phrases
    char tempArray[100][200];
    // need to add to new token stream, not including the stop phrases
    for(int i = 0; i < lenUserInput; i++)
    {
        for(int j = 0; j < lenStopWordCorpus; j++)
        {
            //checks if user Input contains a stop phrase, read from fileReadWrite.h
            if(strcmp(userInput[i], arrayofStopWord[j]->stopPhrase) == 0)
            {
                removesStopPhrases++;
                switchCheck = 1;
            }
        }
        if(switchCheck == 0){
            strcpy(tempArray[counter], userInput[i]);
            counter++;
        }
        switchCheck = 0;
    }
    // replace User input but without the stop words
    for(int i = 0; i < lenUserInput; i++)
    {
        strcpy(userInput[i], tempArray[i]);
    }

    // Returns the amount of phrases that are removed
    // Used to aid with unit testing the function
    for(int i = 0; i < counter; i++){
        strcpy(tempArray[i], " ");
    }
    memset(tempArray, 0, sizeof(tempArray));
    if(removesStopPhrases  > 0){
        return removesStopPhrases;
    }

    return 0;

}
// Function checks users input for invalidity
// Checks for digits and uppercases letters
// Returns 0 if the sentence is correct otherwise returns 1
int validateUserInput(const char *sentence){
    int countDigits = 0;
    int countUpperLetter = 0;

    if(strlen(sentence) >= 1) {
        for (int i = 0; i < strlen(sentence); i++)
        {
            if (isdigit(sentence[i])) {
                countDigits++;
            }

            else if(isupper(sentence[i])) {
                countUpperLetter++;
            }
        }
    }
    else{
        return 1;
    }

    if(countUpperLetter > 0.5*strlen(sentence) || countDigits > 2){
        return 1;
    }
    return 0;
}