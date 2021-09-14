#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "chatbotLogic.h"
#include "fileReadWrite.h"
#include "preProcessing.h"

// Function runs the similarity for each sentence of the chosen corpus
// It finds the most matching sentence and prints it
// Returns the index of the sentence of corpus for which
int runSimilarity(const int option) {
    // local variables used within this function
    int sizeArray = 0;
    int similarSizeArray = 0;
    char similarSentence[maxSize][maxSize];
    double similarity = 0;
    double previous_similarity = 0;


    // Runs the similarity for the hotel corpus
    if (option == 1) {
        for (int i = 0; i < elementInCorpusHotel; i++) {
            sizeArray = arrayHotelBooking[i]->arraySizeId;
            char tempChar[maxSize][maxSize];
            // Takes out each sentence from corpus array
            for (int j = 0; j < sizeArray; j++) {
                strcpy(tempChar[j], arrayHotelBooking[i]->tokensentence[j]);

            }
            //get cosine similarity of that sentence
            similarity = cosineSimilarity(tempChar, sizeArray);

            // store the most similar sentence and overwrite if more similar sentence is found

            if(similarity > previous_similarity){
                similarSizeArray = sizeArray;
                for (int x = 0; x < sizeArray; x++) {
                    strcpy(similarSentence[x], tempChar[x]);
                }
                previous_similarity = similarity;
            }

        }
        // Prints the most similar sentence
        if(previous_similarity > 0) {
            for (int i = 0; i < similarSizeArray; i++) {
                printf("%s ", similarSentence[i]);
            }
            printf("\n");
        }
        else{
            printf("Sorry I didn't understand your query\n");
        }
        return 1;

    }
    // Run for room service
    else {
        for (int i = 0; i < elementInCorpusRoom; i++) {
            sizeArray = arrayRoomService[i]->arraySizeId;
            char tempChar[maxSize][maxSize];

            for (int j = 0; j < sizeArray; j++) {
                // take out each sentence
                strcpy(tempChar[j], arrayRoomService[i]->tokensentence[j]);
            }

            //get cosine similarity of that sentence
            similarity = cosineSimilarity(tempChar, sizeArray);
            // store the most similar sentence and overwrite if find a more similar sentence
            if(similarity > previous_similarity){
                similarSizeArray = sizeArray;
                for (int x = 0; x < sizeArray; x++) {
                    strcpy(similarSentence[x], tempChar[x]);
                }
                previous_similarity = similarity;
            }
        }
        if(previous_similarity > 0) {
            for (int i = 0; i < similarSizeArray; i++) {
                printf("%s ", similarSentence[i]);
            }
            printf("\n");
        }
        else{
            printf("Sorry I didn't understand your query\n");
        }

        return 1;
        }

}

// Function compares the 2d array lists with each other
// Returns double value based on the similarity between the two sentences
// Returns 0 if there is no similarity found between the two
double cosineSimilarity(char sentence[maxSize][maxSize], const int sizeArray){

    // Local variables used within this function
    int dotproduct = 0;
    double similarity = 0;
    // Size of the two sentencea arrays are stored in here
    int magnitudeA = lenUserInput;
    int magnitudeB = sizeArray ;

    // Determine the larger list of words
    // If user input is greater than use as outer loop,
    // so we dont get index error
    if(lenUserInput >= sizeArray){
        for(int i = 0; i < lenUserInput; i++)
        {
            for(int j = 0; j < sizeArray; j++)
            {
                //printf("%s : %s\n",userInput[i], sentence[j]);
                // if it is contained within both lists
                if(strcmp(userInput[i], sentence[j]  ) == 0)
                {

                    dotproduct++;
                }
            }
        }
    }
    else{

        for(int i = 0; i < sizeArray; i++)
        {
            for(int j = 0; j < lenUserInput; j++)
            {
                //printf("%s : %s\n",userInput[i], sentence[j]);
                if(strcmp(userInput[j], sentence[i]) == 0)
                {
                    dotproduct++;
                }
            }
        }
    }
    // Cosine similarity calculation
    similarity = (double) dotproduct / (sqrt(magnitudeA) * sqrt(magnitudeB));

    return similarity;
}

// Function compares the 2d user array with general chat functions
// Prints most appropriate output based on user input if found
// Returns 1 if common word found in user sentence
// Otherwise returns 0
int runGeneralChat(){
    char *userChoice = (char *) malloc(sizeof(char) * 200);
    // Checks for common word phrases in the user sentence
    for(int i = 0; i < lenUserInput;i++){
        if((strcmp(userInput[i], "thanks") == 0) || (strcmp(userInput[i], "Thank") == 0)){
            printf("Your Welcome!\n");
            printf("\n");
            printf("Would you like to exit?\n");
            scanf("%s\0", userChoice);
            if(strcmp(userChoice, "yes") == 0){
                exit(0);
            }
            return 1;
        }
        else if((strcmp(userInput[i], "Hi") == 0) || (strcmp(userInput[i], "Hello") == 0)){
            printf("Hi! How can I help?\n");
            return 1;
        }
    }
    free(userChoice);
    return 0;
}