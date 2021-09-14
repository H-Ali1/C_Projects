
#ifndef MAIN_C_LOANS_H
#define MAIN_C_LOANS_H

// Structure holds the current book that is being loaned by specific user
 struct loanedBook
{
    unsigned int bookID; //ID of the book being borrowed
    char username[20]; //username of the loaned book
};

// List of all users who have currently borrowed a book
extern struct loanedBook *booklist[50];

// Functions used to implement Loans.c
// Function displays the user menu after they have logged in
// Returns 0 when the user wants to Logout
int displayUserMenu();

// Function borrows the book the user wants by using Book ID
// Returns 1 if the book is borrowed and is added to the loaned text file
// Otherwise Returns 0 if unsuccessful
int borrowBook();

// Function used to validate the Book ID entered is a valid number and exists
// Returns 1 if the book is valid, otherwise returns 0 if not
int validateLoanBook();

// Function is used to return the book borrowed back, removes the book
// from the loans text file by checking if it is the loanedBook list
// Returns 0 once complete
int returnBook();

// Loads the loaned books from text file into the loanedBook list
// Returns 0 once the text file is loaded into the library system
int readLoanedBook();

// Adds the newly borrowed book by the user to the text file
// Takes the book to be borrowed as a parameter
// Returns 0 once completed
int addToFile(struct loanedBook book);

// Removes the requested book by the user from the text file
// Takes the book to be returned as a parameter
// Returns 0 once completed
int removeFile(struct loanedBook book);

// Displays the books that are currently borrowed by the user
// Returns 0 if the user has no books currently on loanedBook
// Otherwise returns 1 after displaying all the loaned books
int showCurrentBorrowed();

// Function is used to check whether the book is currently on loan
// This is used to make sure the book is not removed if it is loaned
// Returns 1 if the book is on loan
// Otherise returns 0
int ifOnLoan(int id);

typedef struct loanedBook loanedBook;

#endif //MAIN_C_LOANS_H
