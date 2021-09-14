#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loans.h"
#include "user.h"
#include "book_management.h"

// global variables used throughout loans.c
int borrowCount = 0;
loanedBook *booklist[50];
int amountBooks;

// Function is used at start to load in all data of borrowed books
// Returnss 0 once function completes
int readLoanedBook(){
    amountBooks = 0;
    int c;
    int i = 0;
    FILE  *file;
    // open loans file
    file = fopen("../loans.txt", "r");
    if (file == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    // read each line of the text file and store in list of loanedBook
    while((c = getc(file)) != EOF){
        booklist[i] = (loanedBook*) malloc(sizeof(struct loanedBook));
        fscanf(file,"%s\t%u", booklist[i]->username, &booklist[i]->bookID);
        i++;
    }
    amountBooks = i - 1;
    fclose(file);

    return 0;
}

// Displays the User Menu
int displayUserMenu(){

    //acts a switch for the while loop
    int boolSwitch = 0;
    char *choice = (char *) malloc(sizeof(char) * 1);
    while(boolSwitch != 1) {
      // Refreshes the list of loaned book
        readLoanedBook();
        printf("---------------------\n");
        printf("1. Borrow a book\n"
               "2. Return a book\n"
               "3. Search for books\n"
               "4. Display all books\n"
               "5. Logout\n");
        printf("---------------------\n");
        printf("Input:");
        scanf("%s\0", choice);
        // Borrows the book by calling upon function borrowBook
        if (strcmp(choice, "1") == 0) {
            int checkBorrowBook;
            checkBorrowBook = borrowBook();
            if(checkBorrowBook){
                printf("The book has been successfully borrowed\n");
            }

        }
        // Returns book, calls function returnBook
        else if(strcmp(choice, "2") == 0) {
            int checkReturnBook;
            checkReturnBook = showCurrentBorrowed();
            if(checkReturnBook == 1) {
                returnBook();
            }
        }
        // Displays search menu from book management
        else if(strcmp(choice, "3") == 0) {
            if(displaySearchMenu() == 0){
                printf("Please enter the correct book format\n");
            }
        }
        // Display the list of current books in the library
        else if((strcmp(choice, "4") == 0)) {
            displayAllBooks();
        }
        // Logs the user out of their account
        else if((strcmp(choice, "5") == 0)) {
            return 0;
        }
    }

}


// gets user to input Book ID
// creates a loanedBook structure which is then fed into addFile
int borrowBook(){

    borrowCount += 1;
    Book* booktemp = (Book*) malloc(sizeof(Book));

    //loanList.array = (Book*) malloc(sizeof(struct Book));
    //loanList.array = realloc((loanList.array), sizeof(struct Book)*(borrowCount));
    int bookID;
    printf("Enter the book ID you would like the borrow");
    scanf("%i",&bookID);
    printf("\n");
    if(validateLoanBook(currentUser,bookID) == 1) {
        //finds the ID of the book and stores it in variable
        *booktemp = find_book_by_id(bookID);
        //store username and book ID in the loanedBook struct
        loanedBook *borrowedBook = (loanedBook *) malloc(sizeof(loanedBook));

        borrowedBook->bookID = booktemp->id;

        strcpy(borrowedBook->username, currentUser);

        addToFile(*borrowedBook);

        return 1;
    }
    else if(validateLoanBook(currentUser,bookID) == 2){
        printf("The book does not exist\n");

    }
    else
        printf("The book has already been borrowed\n");

    return 0;
}

// Finds the book ID in list of loans and removes from the file
// Returns 0 once completed
int returnBook(){
    int userBookID;
    printf("Please enter the ID of the book you would like to return:");
    scanf("%i", &userBookID);
    for(int i = 0; i < amountBooks; i++){
        if(booklist[i]->bookID == userBookID){
            removeFile(*booklist[i]);
            break;
        }
    }
    return 0;
}

// Checks if the book is on loan and retunrs 1 if it is,
// otherwise returns 0
int ifOnLoan(int loanID){
    for(int i = 0; i < amountBooks; i++){
        if(booklist[i]->bookID == loanID){
            return 1;
        }
    }
    return 0;
}


// Validates whether the book to borrow is valid
// Checks if book exists and performs ID validation
// Returns 0 if the validation does not pass
// Otherwise returns 1
int validateLoanBook(char *user, int id){
    Book* booktemp = (Book*) malloc(sizeof(Book));
    for(int i = 0; i < amountBooks; i++){
        if((strcmp(booklist[i]->username, user) == 0)){
            if(booklist[i]->bookID == id){
                return 0;
            }
        }
        else if(id > 500 || id < 0){
            return 0;
        }
    }
    *booktemp = find_book_by_id(id);
    if(booktemp->id == 99){
        return 2;
    }
    return 1;
}

// Adds the borrowed book to the loan file
// Returns 0 once complete
int addToFile(struct loanedBook book){

    FILE  *file;
    file = fopen("../loans.txt", "a");
    if (file == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    fprintf(file,"%s\t%u\n", book.username, book.bookID);

    fclose(file);
    return 0;
}

// Shows the books that have been currently borrowed by the username
// Prints the books to console, if no books are borrowed
// Then returns 0 otherwise returns 1
int showCurrentBorrowed(){
    int hasReturns = 0;
    Book* booktemp = (Book*) malloc(sizeof(Book));
    printf("%s\t%-40s%-40s\t%s\t%s\n","ID","Title","Authors","Year", "Copies");
    for(int i = 0 ; i < amountBooks; i ++){
        if(strcmp(booklist[i]->username,currentUser) == 0 ){
            hasReturns = 1;
            *booktemp = find_book_by_id(booklist[i]->bookID);
            printf("%i\t  %-40s%-40s\t  %u\t  %u\n",booktemp->id,booktemp->title, booktemp->authors,
                   booktemp->year, booktemp->copies);
        }
    }
    if(hasReturns == 0) {
        printf("You have no books to return\n");
        return 0;
    }
    else
        return 1;

}

// Removes the book that has been returned from loan file
// Overwrites the loan file without the book that has been returned
// Returns 0 once completed
int removeFile(struct loanedBook book){

    printf("the id of the book is: %u\n",book.bookID);
    FILE  *file;
    file = fopen("../loans.txt", "w");
    if (file == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    fprintf(file, "\n");
    for(int i=0; i < amountBooks; i++)
    {

        if((booklist[i]->bookID != book.bookID) || (strcmp(booklist[i]->username, currentUser) != 0))
        {
            fprintf(file, "%s\t%u\n", booklist[i]->username, booklist[i]->bookID);
        }
    }
    fclose(file);
    printf("The book has been returned\n");

    return 0;
}
