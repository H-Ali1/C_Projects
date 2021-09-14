#include <stdlib.h>
#include "fileReadWrite.h"
#include "preProcessing.h"

// Arrays that hold the corpus data
stopWord *arrayofStopWord[130];
corpusHotelBooking *arrayHotelBooking[100];
corpusRoomService *arrayRoomService[100];

// Integers used to traverse the array of structs of corpus
int lenStopWordCorpus;
int elementInCorpusHotel;
int elementInCorpusRoom;

// Function is used as the main for loading all corpus into the program
// Is called upon at the start of the program running
// Doesn't return anything
void loadPre(){
    FILE *infile;

    // open file for reading
    infile = fopen("../stopWords.txt", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }
    loadStopWords(infile);

    fclose(infile);
    load_corpus();
}

// Reads the stop word corpus into the program
// Takes in the file name as the parameter
// Returns 0 if the file is opened successfully otherwise returns 1
// Corpus is taken from https://gist.github.com/sebleier/554280
static int loadStopWords(FILE *file){

    int c;
    int i = 0;
    // read in the books using a while loop by iterating each line
    while((c = getc(file)) != EOF)
    {
        arrayofStopWord[i] = (stopWord *) malloc(sizeof(stopWord));

        fscanf(file,"%s", arrayofStopWord[i]->stopPhrase);
        arrayofStopWord[i]->id = i+1;
        i++;
    }

    lenStopWordCorpus = i - 1;

    return 0;
}

// Reads the corpus into the program
// Returns 0 if the files were opened successfully otherwise returns 1
// Loads hotel and room corpus into the system
int load_corpus() {
    FILE *infile;
    int loadHotel = 0;
    int loadRoom = 0;

    // open file for reading
    infile = fopen("../hotelBookingCorpus.txt", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    loadHotel = load_hotelbooking(infile);
    fclose(infile);

    // Opens room service corpus
    infile = fopen("../roomServiceCorpus.txt", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }
    loadRoom = load_roomservice(infile);
    fclose(infile);


    // Returns 0 if the files are opened correctly
    // Otherwise returns 0
    if(loadRoom == 0 && loadHotel == 0){
        return 0;
    }
    return 1;

}

// Reads the hotel corpus into the program
// Takes in the file name as the parameter
// Returns 0 if the file is opened successfully otherwise returns 1
static int load_hotelbooking(FILE *file){
    //holds each line of
    char tempCharArray[50];
    int c;
    elementInCorpusHotel = 0;
    // goes through each sentence
    int i = 0;
    // goes through each word in sentence
    int j = 0;
    // read in the books using a while loop by iterating each line
    while((c = getc(file)) != EOF)
    {
        arrayHotelBooking[i] = (corpusHotelBooking *) malloc(sizeof(corpusHotelBooking));
        // Read in the hotel corpus data into Temp Array of Chars
        fscanf(file,"%[^;];", tempCharArray);
        arrayHotelBooking[i]->arraySizeId = 0;

        // Tokenize the inputted corpus into an array of words
        tokenization(tempCharArray, 1);
        arrayHotelBooking[i]->id = i+1;

        i++;
        elementInCorpusHotel++;
    }

    // records amount of stop phrases
    if(elementInCorpusHotel < 1) {
        return 1;
    }
    return 0;
}

// Reads the room corpus into the program
// Takes in the file name as the parameter
// Returns 0 if the file is opened successfully otherwise returns 1
static int load_roomservice(FILE *file)
{
    //holds each line of
    static char tempCharArray[50];
    int c;
    elementInCorpusRoom = 0;
    // goes through each sentence
    int i = 0;
    // read in the books using a while loop by iterating each line
    while((c = getc(file)) != EOF)
    {
        arrayRoomService[i] = (corpusRoomService *) malloc(sizeof(corpusRoomService));
        // Read in the hotel corpus data into Temp Array of Chars
        fscanf(file,"%[^;];", tempCharArray);
        arrayRoomService[i]->arraySizeId = 0;
        // Tokenize the inputted corpus into an array of words
        tokenization(tempCharArray, 2);
        arrayRoomService[i]->id = i+1;

        i++;
        elementInCorpusRoom++;
    }

    // records amount of stop phrases
    if(elementInCorpusRoom < 1) {
        return 1;
    }
    return 0;
}
