#ifndef MAIN_C_CHATBOTLOGIC_H
#define MAIN_C_CHATBOTLOGIC_H
#define maxSize 40


// Function runs the similarity for each sentence of the chosen corpus
// It finds the most matching sentence and prints it
// Returns 1 if there is a similarity found
// Otherwise returns 0
int runSimilarity(int option);

// Function compares the 2d array lists with each other
// Returns double value based on the similarity between the two sentences
// Returns 0 if there is no similarity found between the two
double cosineSimilarity(char sentence[maxSize][maxSize], int sizeArray);

// Function compares the 2d user array with general chat functions
// Prints most appropriate output based on user input if found
// Returns 1 if common word found in user sentence
// Otherwise returns 0
int runGeneralChat();


#endif //MAIN_C_CHATBOTLOGIC_H
