#include <stdio.h>
#include "user.h"
#include <stdlib.h>
#include <string.h>
#include "book_management.h"
#include "loans.h"


// Main function that runs the library system

int main() {
    // Pre-requisite to loading the library system
    // Loads all books in library, books on loan and current user
    getBookOpen();
    loadUsers();
    readLoanedBook();
    int check = 1;
    // Get user input on their choice
    char *option = (char *)malloc(sizeof(char)*1);


    while(check!=150){
        printf("Enter your choice\n");
        printf("---------------------\n");
        printf("1. Login\n"
               "2. Register\n"
               "3. Search for books\n"
               "4. Display all books\n"
               "5. Quit\n");
        printf("---------------------\n");
        printf("\n");
        printf("Input:");
        scanf("%s\0", option);
        // Choice to login into the library
        if(strcmp(option,"1") == 0){
            int loginvalue;
            loginvalue = getLogin();
            if(loginvalue == 1) {
                displayUserMenu();
            }
            else if(loginvalue == 2) {
                admin_login();
            }
        }
        // Choice to register as a user
        else if(strcmp(option,"2") == 0){
            if(getRegistered() == 1){
              loadUsers();
            }


        }
        // Allows you to search for books
        else if(strcmp(option,"3") == 0){
            displaySearchMenu();
        }
        // Displays all the books in the library system
        else if(strcmp(option,"4") == 0){
            displayAllBooks();
        }
        // Quits the library program
        else if(strcmp(option,"5") == 0){
          // Stores all the books in the system into books.txt
            writeToFile("w", 1);
            free(option);
            exit(0);
        }
        else
            printf("No such command!\n");

    }


}
