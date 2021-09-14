#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "book_management.h"
#include "loans.h"


BookArray allBooks;
BookArray newBook;
int amountOfBooks = 0;

// store books into text file when user quits library system
// opens books.txt in "w" format
// first line written is the amount of books in the library system
// after first line, we write the struct BookArray into the text file by using for loop
int store_books(FILE *file){


    // open file for writing

    //Error exception if file can't be opened
    if (file == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // write amount of books in BookArray
    fprintf(file,"%i/n\n", (amountOfBooks));
    fprintf(file, "\n");
    // write struct of books to file
    for(int i=0; i < allBooks.length-1; i++)
    {
        fprintf(file,"%i\t%s;\t%s;\t%u\t%u\n",allBooks.array[i].id,allBooks.array[i].title, allBooks.array[i].authors,
                allBooks.array[i].year, allBooks.array[i].copies);
    }

    // close file
    fclose (file);

    return 0;
};

// read text file into the library system
// we allocate memory to Array of Books to hold the text file data
// we allocate memory size based on integer at first line of text file (amount of books)
int load_books(FILE *file){

    int c;
    int numOfBooks;
    int i = 0;
    char buf[4];

    // take in amount of books
    fscanf(file,"%i/n", &numOfBooks);
    //read in empty space after the integer
    fgets(buf, 4, file);
    //allocate memory to each book in the library
    allBooks.array = (Book*) malloc(sizeof(struct Book)* (numOfBooks + 1));
    allBooks.length = 0;

    // read in the books using a while loop by iterating each line
    while((c = getc(file)) != EOF)
    {
        allBooks.array[i].title = (char*) malloc(sizeof(char)*40);
        allBooks.array[i].authors = (char*) malloc(sizeof(char)*40);

        fscanf(file,"%i\t%[^;];\t%[^;];%u\t%u/n",&allBooks.array[i].id,allBooks.array[i].title, allBooks.array[i].authors,
                &allBooks.array[i].year, &allBooks.array[i].copies);
        allBooks.length+=1;
        i++;
    }

    amountOfBooks = i - 1;

    return 0;
}


// Add book to file
int add_book(struct Book book){
  FILE *file;
  // open book.txt file in write mode so we can
    file = fopen("../books.txt", "w");
    if (file == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    fprintf(file,"%i/n\n", (amountOfBooks-1));
    fprintf(file, "\n");
    // write struct to file
    for(int i=0; i < allBooks.length-1; i++)
    {
        fprintf(file,"%i\t%s;\t%s;\t%u\t%u\n",allBooks.array[i].id,allBooks.array[i].title, allBooks.array[i].authors,
                allBooks.array[i].year, allBooks.array[i].copies);
    }

    fprintf(file,"%i\t%s;\t%s;\t%u\t%u\n",book.id,book.title, book.authors,
            book.year, book.copies);


    // close file
    fclose (file);

    return 0;
}

// Removes book from the struct and the files
// Takes in book struct that needs removing, as a parameter
// Returns 0 once function is complete
int remove_book(struct Book book){
    // remove struct by writing file without that book
    // open file for writing
    FILE *file;
    file = fopen("../books.txt", "w");
    if (file == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    // write struct to file

    // Reduce number of books by 1
    amountOfBooks -= 1;

    // write the new number of books in library
    fprintf(file,"%i/n\n", (amountOfBooks));
    fprintf(file, "\n");
    //Writes all the books except the book that is removed into the file
    for(int i=0; i < allBooks.length-1; i++)
    {
        if(allBooks.array[i].id != book.id)
        {
            fprintf(file, "%i\t%s;\t%s;\t%u\t%u\n", allBooks.array[i].id, allBooks.array[i].title,
                    allBooks.array[i].authors,
                    allBooks.array[i].year, allBooks.array[i].copies);
        }
    }
    // close file
    fclose (file);
    return 0;
}

// Shows the menu for the admin and links the supporting functions
int admin_login() {

    int boolSwitch = 1;
    char *choice = (char *) malloc(sizeof(char) * 1);
    while (boolSwitch != 150) {
      //Prints the menu for the admin menu
        printf("---------------------\n");
        printf("1. Add a book\n"
               "2. Remove a book\n"
               "3. Search for a book\n"
               "4. Display all books\n"
               "5. Log Out\n");
        printf("---------------------\n");
        printf("\n");
        printf("Input:");
        scanf("%s\0", choice);
        // choice for adding book
        if (strcmp(choice, "1") == 0) {
            if(getBooks() == 1){
                getBookOpen();
            }
        // choice for removing a book
        } else if (strcmp(choice, "2") == 0) {
            int bookID;
            printf("Please search a book to remove\n");
            displaySearchMenu();
            printf("Enter ID of the book:");
            scanf("%i", &bookID);
            //check if book is on loan
            if(ifOnLoan(bookID) == 0) {
                for (int i = 0; i < allBooks.length - 1; i++) {
                    if (allBooks.array[i].id == bookID) {
                      // calls remove book function if book not on loan
                        remove_book(allBooks.array[i]);
                        break;
                    }
                }
                getBookOpen();
            }
            else
                printf("The book is on loan, sorry\n");
        // choice for searching for books
        } else if (strcmp(choice, "3") == 0) {
            if(displaySearchMenu() != 1){
                printf("Please enter the correct book format");
            }
        // choice for displaying books
        } else if (strcmp(choice, "4") == 0) {
           displayAllBooks();
        // Logs out of the admin menu
        } else if (strcmp(choice, "5") == 0) {
          printf("Logging out...\n");
            return 2;
        }
        // Prints out if choice is invalid
        else
        {
            printf("There is no such command\n");
        }

    }
    return 1;
  }

// Function gets admin input for adding new book
// Takes four inputs and returns 1 if successfully
// Otherwise 0 if not.
int getBooks(){

    int flagged = 0;
    char getAuthors[40];
    char getTitle[40];
    char getYear[40];
    char getCopies[40];

    // Take input from console
    printf("Enter book title:");
    scanf(" %[^\n]", getTitle);
    printf("Enter authors:");
    scanf(" %[^\n]", getAuthors);
    printf("Enter book year:");
    scanf(" %[^\n]", getYear);
    printf("Enter book copies:");
    scanf(" %[^\n]", getCopies);
    // Check if the inputs are valid
    if(validateBook(getTitle, getAuthors, getYear, getCopies) == 1){

        Book* aTempBook = (Book*) malloc(sizeof(Book));
        // Creates a temporary book structure
        aTempBook = tempBook(getTitle, getAuthors, getYear, getCopies);
        // Calls add book to add temporary book to structure and file
        add_book(*aTempBook);
        free(aTempBook);
        return 1;
    }
    else
        printf("Invalid book type\n");


    return 0;
}

// Function creates a temporary book using the inputs from the console
// Casts parameters to correct format
// Which then returns the structure
Book* tempBook(char *title, char*authors, char *year, char* copies){

    Book* booktemp = (Book*) malloc(sizeof(Book));
    unsigned int n_Year;
    unsigned int n_Copies;
    char *ptr;
    char *sqr;
    //Convert year and copies to unsigned ints
    n_Year = strtol(year,&ptr,10);
    n_Copies = strtol(copies,&sqr,10);
    amountOfBooks += 2;

    //check ID is not taken by any other book:
    int largestID = 0;
    for(int i = 0; i < amountOfBooks; i++){
        if(allBooks.array[i].id > largestID){
            largestID = allBooks.array[i].id;
        }
    }

    booktemp->id = largestID + 1;
    booktemp->title = title;
    booktemp->authors = authors;
    booktemp->year = n_Year;
    booktemp->copies = n_Copies;

    return booktemp;
};


// Validates the user inputs using string length and digits
// The function returns 0 if the validation fails otherwise 1 if passes all the tests
int validateBook(char *title, char *authors, char *year, char *copies) {

    long yearNum;
    char *stringForYears;
    char *stringForCopies;
    long copyNum;

    if (strlen(title) > 4 && strlen(title) < 40) {
        for (int i = 0; i < strlen(title); i++) {
            if (isdigit(title[i])) {
                return 0;
            }
        }


        if (strlen(authors) > 4 && strlen(authors) < 30) {
            for (int i = 0; i < strlen(authors); i++) {
                if (isdigit(authors[i])) {
                    return 0;
                }
            }


            if ((strlen(year) == 4)) {
                yearNum = strtol(year, &stringForYears, 10);
                if (yearNum > 1900 && yearNum < 2021) {

                    if (strlen(copies) <= 3) {
                        copyNum = strtol(copies, &stringForCopies, 10);
                        if ((copyNum > 0 && copyNum <= 999)) {

                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// Displays all the books in the book structure
void displayAllBooks(){
    //find maximum length for each column

    printf("%s\t%-40s%-40s\t%s\t%s\n","ID","Title","Authors","Year", "Copies");
    for(int i = 0; i < allBooks.length-1; i++){
        printf("%i\t  %-40s%-40s\t  %u\t  %u\n",allBooks.array[i].id,allBooks.array[i].title, allBooks.array[i].authors,
        allBooks.array[i].year, allBooks.array[i].copies);
    }
}

// Opens the books.txt and then calls load_books
// Closes file after loading the books
int getBookOpen(){
    FILE *infile;

    // open file for reading
    infile = fopen("../books.txt", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    load_books(infile);

    fclose(infile);
}


// Used to either store all books or update amount of books in the system
// char option: used to determine file opening format (either write or read)
// int type: used to switch between store_books and updateAmountofBooks
int writeToFile(char *option, int type){
    FILE *outfile;

    // open file for storing books
    outfile = fopen("../books.txt", option);
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    if(type == 1) {
        store_books(outfile);
    }

    return 0;

}


// Search for the books based on title
struct BookArray find_book_by_title (const char *title){

    newBook.length = 0;
    newBook.array = (Book*) malloc(sizeof(struct Book));
    int counter = 0;
    for(int z=0; z < amountOfBooks; z++) {
        if(strcmp(allBooks.array[z].title, title) == 0){
            counter +=1;
            newBook.array = realloc((newBook.array), sizeof(struct Book)*(counter));
            newBook.array[counter-1].title = (char*) malloc(sizeof(char)*40);
            newBook.array[counter-1].authors = (char*) malloc(sizeof(char)*40);
            newBook.array[counter-1] = allBooks.array[z];
            newBook.length += 1;
        }
    }

    return newBook;

}
// Search for books based on authors
struct BookArray find_book_by_author (const char *author){
    newBook.length = 0;
    newBook.array = (Book*) malloc(sizeof(struct Book));
    int counter = 0;
    for(int z=0; z < amountOfBooks; z++) {
        if(strcmp(allBooks.array[z].authors, author) == 0){
            counter +=1;
            newBook.array = realloc((newBook.array), sizeof(struct Book)*(counter));
            newBook.array[counter-1].title = (char*) malloc(sizeof(char)*40);
            newBook.array[counter-1].authors = (char*) malloc(sizeof(char)*40);
            newBook.array[counter-1] = allBooks.array[z];
            newBook.length += 1;
        }
    }
    return newBook;

}

// Search for books based on year
struct BookArray find_book_by_year (unsigned int year){
    newBook.length = 0;
    newBook.array = (Book*) malloc(sizeof(struct Book));
    int counter = 0;
    for(int z=0; z < amountOfBooks; z++) {
        if(allBooks.array[z].year == year){
            counter +=1;
            newBook.array = realloc((newBook.array), sizeof(struct Book)*(counter));
            newBook.array[counter-1].title = (char*) malloc(sizeof(char)*40);
            newBook.array[counter-1].authors = (char*) malloc(sizeof(char)*40);
            newBook.array[counter-1] = allBooks.array[z];
            newBook.length += 1;
        }
    }
    return newBook;


}

// Finds the book based on ID
// Used to remove and borrow books
struct Book find_book_by_id (int bookID){

    Book* booktemp = (Book*) malloc(sizeof(struct Book));
    int counter = 0;

    for(int z=0; z < amountOfBooks; z++) {
        if(allBooks.array[z].id == bookID){
            booktemp->title = (char*) malloc(sizeof(char)*40);
            booktemp->authors = (char*) malloc(sizeof(char)*40);
            booktemp = &allBooks.array[z];
            return *booktemp;
        }
    }
    booktemp->id = 99;
    return *booktemp;

}

// Displays search book menu
// Returns 0 if validation fails for title, author or year,
// otherwise returns 1.
int displaySearchMenu(){
    int boolSwitch = 0;
    char searchFor[40];
    char *choice = (char *) malloc(sizeof(char) * 1);
    while (boolSwitch != 150) {

        printf("loading search menu\n");
        printf("---------------------\n");
        printf("1. Find a book by title\n"
               "2. Find book by author\n"
               "3. Find book by year\n");
        printf("---------------------\n");
        printf("Input:");
        scanf("%s\0", choice);
        // Choice 1: Find book by title
        if (strcmp(choice, "1") == 0) {
            printf("Enter title of the book:");
            scanf(" %[^\n]", searchFor);
            // check if the title meets length requirements
            if (strlen(searchFor) > 4 && strlen(searchFor) < 40) {
                for (int i = 0; i < strlen(searchFor); i++) {
                  // No digits in the title of the book
                    if (isdigit(searchFor[i])) {
                        return 0;
                    }
                }
            }
            find_book_by_title(searchFor);
            displaySearchedBooks(newBook);
            return 1;
        }
        // Choice 1: Find book by authors
        else if (strcmp(choice, "2") == 0) {
            printf("Enter author of the book:");
            scanf(" %[^\n]", searchFor);
            // check if author meets length requirements
            if (strlen(searchFor) > 4 && strlen(searchFor) < 40) {
                for (int i = 0; i < strlen(searchFor); i++) {
                  // No digits in the author of the book
                    if (isdigit(searchFor[i])) {
                      printf("Input contains a number\n");
                      printf("\n");
                        return 0;
                    }
                }
            }
            find_book_by_author(searchFor);
            displaySearchedBooks(newBook);
            return 1;
        }
        // Choice 1: Find book by years
        else if (strcmp(choice, "3") == 0) {
            unsigned int searchYear;
            printf("Enter year of the book:");
            scanf(" %[^\n]", searchFor);
            // convert inputted year into an integer
            char *ptr;
            searchYear = strtol(searchFor,&ptr,10);
            if ((strlen(searchFor) == 4) ) {
                if (searchYear > 1900 && searchYear < 2021) {
                    find_book_by_year(searchYear);
                    displaySearchedBooks(newBook);
                    return 1;
                }
                else
                    printf("Invalid entry for year\n");
                    printf("\n");
                    return 0;
            }
            else
                printf("Invalid entry for year\n");
                printf("\n");
                return 0;
        }
        else
            printf("Invalid choice\n");
            printf("\n");
    }
}


// Displays searched books based on searched results
// Prints "No records found" if there are no books based on current search
void displaySearchedBooks(struct BookArray searchBook)
{
    printf("\n");
    if(searchBook.length == 0)
    {
        printf("Sorry no records were found\n");
    }
    else {
        printf("%s\t%-40s%-40s\t%s\t%s\n","ID","Title","Authors","Year", "Copies");
        for(int i = 0; i < searchBook.length; i++){
            printf("%i\t%-40s%-40s\t%u\t%u\n",searchBook.array[i].id,searchBook.array[i].title, searchBook.array[i].authors,
                   searchBook.array[i].year, searchBook.array[i].copies);
        }
    }
    printf("\n");
}
