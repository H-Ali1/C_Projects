#ifndef MAIN_C_FILEREADWRITE_H
#define MAIN_C_FILEREADWRITE_H
#include <stdio.h>

// Function is used as the main for loading all corpus into the program
// Is called upon at the start of the program running
// Doesn't return anything
void loadPre();

// Reads the stop word corpus into the program
// Takes in the file name as the parameter
// Returns 0 if the file is opened successfully otherwise returns 1
// Corpus is taken from https://gist.github.com/sebleier/554280
static int loadStopWords(FILE *file);

// Reads the corpus into the program
// Returns 0 if the files were opened successfully otherwise returns 1
// Loads hotel and room corpus into the system
int load_corpus();

// Reads the hotel corpus into the program
// Takes in the file name as the parameter
// Returns 0 if the file is opened successfully otherwise returns 1
static int load_hotelbooking(FILE *file);

// Reads the room corpus into the program
// Takes in the file name as the parameter
// Returns 0 if the file is opened successfully otherwise returns 1
static int load_roomservice(FILE *file);

// Struct stopWord for each stop word in the corpus text file
// Contains Id and the stop phrase
typedef struct
{
    int id;	              // id of the word
    char stopPhrase[30];  // the word itself

} stopWord;

// Struct corpusHotelBooking: hotel corpus is loaded into this particular struct
// Contains Id and the stop phrase aswell as array size for each sentence in the text file
typedef struct
{
    int id;	                       // id of the sentence
    int arraySizeId;               // Holds the length of that particular sentence
    char tokensentence[100][200];  // 2d array holds each word in sentence

} corpusHotelBooking;

// Struct corpusRoomService: room service corpus is loaded into this particular struct
// Contains Id and the stop phrase aswell as array size for each sentence in the text file
typedef struct
{
    int id;	                       // id of the sentence
    int arraySizeId;               // Holds the length of that particular sentence
    char tokensentence[100][200];  // 2d array holds each word in sentence

} corpusRoomService;

// Are the particular array of structs which the corpus is held in
extern stopWord *arrayofStopWord[130];
extern corpusHotelBooking *arrayHotelBooking[100];
extern corpusRoomService *arrayRoomService[100];

// Holds the length of the corpus for each array
extern int elementInCorpusHotel;
extern int elementInCorpusRoom;
extern int lenStopWordCorpus;

#endif //MAIN_C_FILEREADWRITE_H
