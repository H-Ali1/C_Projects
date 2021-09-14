#include "unity.h"
#include <string.h>
#include <stdlib.h>
#include "preProcessing.h"
#include "fileReadWrite.h"
#include "chatbotLogic.h"
#include <math.h>

// Unit Test: checks for valid inputs of the user
// Returns 0 if the sentence is valid
// Otherwise returns 1
void test_validateUserInput_create(void){
    // Uses a variable to hold the test cases
    char inputSentence[70];
    // Normal Cases
    // Test: Valid Sentence
    strcpy(inputSentence, "This is a sentence");
    TEST_ASSERT_EQUAL(0, validateUserInput(inputSentence));

    // Test: Check if passes for a longer string
    strcpy(inputSentence, "Call me Ishmael. Some years ago—never mind how long precisely");
    TEST_ASSERT_EQUAL(0, validateUserInput(inputSentence));

    // Edge cases
    // Test: Check if catches number
    strcpy(inputSentence, "12432 sentence check");
    TEST_ASSERT_EQUAL(1, validateUserInput(inputSentence));
    strcpy(inputSentence, "");
    // Test: Check if catches invalid sentence length
    TEST_ASSERT_EQUAL(1, validateUserInput(inputSentence));

}
// Unit Test: checks whether sentence is tokenized by checking length
// Returns 1 if the sentence is valid
// Otherwise returns 0
void test_tokenization_create(void){
    // Uses a variable to hold the test cases
    char inputSentence[40];
    strcpy(inputSentence, "This is a sentence");
    // Normal Cases
    // Test: Valid Sentence
    TEST_ASSERT_EQUAL(1, tokenization(inputSentence,0));

    // Edge Cases:
    // Test: Invalid sentence length
    TEST_ASSERT_EQUAL(0, tokenization("",0));
    // Test: Invalid sentence input, contains numbers
    TEST_ASSERT_EQUAL(0,tokenization("1212", 0));

}
// Unit Test: Test to check whether stop words are removed
// Returns 0 if no stop words are removed
// Otherwise returns integer greater 0
// Uses https://gist.github.com/sebleier/554280 as list of stop phrases
void test_removeStopWords_create(void){
    // Function requires the corpus to be loaded into the program to run
    loadPre();
    // Uses a variable to hold the test cases
    char *inputUser = (char *) malloc(sizeof(char) * 200);

    // Normal Cases
    // Test: Contains 0 stop phrases
    strcpy(inputUser, "Sentence without stop phrases");
    tokenization(inputUser, 0);
    TEST_ASSERT_EQUAL(0,removeStopWords());

    // Test: Contains 3 stop phrases
    strcpy(inputUser, "this is a normal sentence");
    tokenization(inputUser, 0);
    TEST_ASSERT_EQUAL(3,removeStopWords());

    // Test: Contains 2 stop phrases
    strcpy(inputUser, "I would like to book a room");
    tokenization(inputUser, 0);
    TEST_ASSERT_EQUAL(2,removeStopWords());

    // Edge Cases
    // Test: Check for invalid inputs
    strcpy(inputUser, "");
    tokenization(inputUser, 0);
    TEST_ASSERT_EQUAL(0,removeStopWords());

    free(inputUser);
}

// Unit Test: Test to check whether corpus is loaded into program correctlt
// Returns 0 if corpus loaded correctly
// Otherwise returns 1
void test_load_corpus_create(void){
    TEST_ASSERT_EQUAL(0, load_corpus());
}

void test_cosineSimilarity_create(void){
    // Defines sentence which will be used to test cases
    char sentence[maxSize][maxSize];
    char *inputUser = (char *) malloc(sizeof(char) * 200);
    // Add words to each index of the the sentence array
    strcpy(sentence[0], "I");
    strcpy(sentence[1], "want");
    strcpy(sentence[2], "to");
    strcpy(sentence[3], "book");
    strcpy(sentence[4], "a");
    strcpy(sentence[5], "room");

    // Fills User Input with same sentence to compare whether cosineSimilarity
    // checks if the sentence are the same or not
    strcpy(inputUser, "I want to book a room");
    tokenization(inputUser, 0);
    const int arraySize = 6;
    // Test: check whether it can confirm sentences are exactly equal to each other
    // Converts returned value to 2dp so can compare more easily
    TEST_ASSERT_EQUAL_FLOAT(1.0, floorf(cosineSimilarity(sentence, arraySize)*100) / 100);

    // Test: check for 83% similarity
    strcpy(sentence[2], "hate");
    TEST_ASSERT_EQUAL_FLOAT(0.83, floorf(cosineSimilarity(sentence, arraySize)*100) / 100);

    // Test: check for 66% similarity
    strcpy(sentence[3], "them");
    TEST_ASSERT_EQUAL_FLOAT(0.66, floorf(cosineSimilarity(sentence, arraySize)*100) / 100);

    // Test: check for 50% similarity
    strcpy(sentence[4], "bathrobe");
    TEST_ASSERT_EQUAL_FLOAT(0.5, floorf(cosineSimilarity(sentence, arraySize)*100) / 100);

    // Test: check for 33% similarity
    strcpy(sentence[5], "heartily");
    TEST_ASSERT_EQUAL_FLOAT(0.33, floorf(cosineSimilarity(sentence, arraySize)*100) / 100);

    free(inputUser);
}


void setUp() {
    //this function is called before each test, it can be empty

}

void tearDown() {
    //this function is called after each test, it can be empty
}


// Main Function which runs all the tests
int main() {
    UNITY_BEGIN();

    // Runs all Unit Tests
    RUN_TEST(test_tokenization_create);
    RUN_TEST(test_validateUserInput_create);
    RUN_TEST(test_removeStopWords_create);
    RUN_TEST(test_load_corpus_create);
    RUN_TEST(test_cosineSimilarity_create);

    return UNITY_END();
}