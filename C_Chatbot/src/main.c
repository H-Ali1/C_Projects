#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "preProcessing.h"
#include "fileReadWrite.h"
#include "chatbotLogic.h"


// Main function that runs the program
int main() {
    // Loads the chat bot corpus into the program
    loadPre();
    int check=0;
    // Runs the user interface indefinitely until user quits program
    while(check!=1){

        char *userChoice = (char *) malloc(sizeof(char) * 1);
        char *inputUser = (char *) malloc(sizeof(char) * 200);

        // Prints user interface
        printf("---------------------\n");
        printf("1. Room Service\n"
               "2. Hotel Booking\n"
               "3. Quit\n");
        printf("---------------------\n");
        printf("\n");
        printf("Please enter your the number for your Enquiry:");
        scanf("%s\0", userChoice);

        // Are the choices based on users choice input
        if (strcmp(userChoice, "1") == 0) {
            printf("You have selected: Room Service\nEnter your Query:");
            scanf(" %[^\n]", inputUser);
            if(validateUserInput(inputUser) == 0){
                tokenization(inputUser,0);
                removeStopWords();
                if(runGeneralChat() == 0){
                    runSimilarity(2);
                }
            }
        }
        else if (strcmp(userChoice, "2") == 0) {
            printf("You have selected: Hotel Booking\nEnter your Query:");
            scanf(" %[^\n]", inputUser);
            if(validateUserInput(inputUser) == 0) {
                tokenization(inputUser, 0);
                removeStopWords();

                runSimilarity(1);
                runGeneralChat();
            }
        }
        else if (strcmp(userChoice, "3") == 0) {
            free(inputUser);
            exit(0);
        }
    }
}


