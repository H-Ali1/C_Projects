#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "user.h"

// global variables that are used in user functions
// Holds the user data from the text file
User *userlist[1000];
// Used to count each line when reading or read
int counter;
// Holds amount of users in the library
int amountOfUsers;
char* listofUsers[100];

int userPosition;

// Main function used to login into library account
// Compare inputted username and password with text file containing all user data
//

int getLogin(){
    // Allocates memory to usernames and password
    char *enterUsername = (char *)malloc(sizeof(char)*20);
    char *enterPassword = (char *)malloc(sizeof(char)*20);
    //acts a switch for while loop
    int boolSwitch = 0;

    while(boolSwitch == 0) {
        printf("Enter your username:");
        scanf("%s\0", enterUsername);

        for (int i = 0; i <= amountOfUsers; i++) {
            //check if user exists in the library system
            //compare input with list of users
            if (strcmp(userlist[i]->username, enterUsername) == 0)
            {
                // Once username confirmed, check password input
                printf("Please enter your password:");
                scanf("%s\0", enterPassword);
                if (strcmp(userlist[i]->password, enterPassword) == 0)
                {
                    printf("User logged in\n");
                    strcpy(currentUser, userlist[i]->username);
                    return 1;
                }
            }
        }
        // Check if admin has logged in
        if (strcmp("Librarian", enterUsername) == 0) {

            printf("please enter your password:");
            scanf("%s\0", enterPassword);
            if (strcmp("Librarian", enterPassword) == 0) {
                printf("Admin login approved\n");
                return 2;
            }
        }
        // Used to exit the while loop and go back to main menu
        else if(strcmp(enterUsername,"q") == 0)
        {
          printf("Returning to Main Menu\n");
            return 0;
        }

        else
        {
            printf("Please enter a correct username, or enter q to quit\n");
        }


    }
    return 0;
}


// Function used to register users. If the user is successfully regiestered
// Then function returns 1, otherwise returns 0
int getRegistered(){
  // switch for the while loop
    int flagged = 0;
    // Allocate memory for the user inputs
    char *enterName = (char *)malloc(sizeof(char)*20);
    char *enterUsername = (char *)malloc(sizeof(char)*20);
    char *enterPass = (char *)malloc(sizeof(char)*20);
    char *enterEmail = (char *)malloc(sizeof(char)*30);
    while(flagged == 0) {
        // Enter and validate name input
        printf("Enter your name:");
        scanf(" %[^\n]", enterName);
        if (validateUser(enterName) == 1) {
            // Enter and validate username input
            printf("Please enter a suitable username:");
            scanf(" %[^\n]", enterUsername);
             if (validateUsername(enterUsername) == 1) {
                 // Enter and validate email input
                 printf("Enter your email address:");
                 scanf(" %[^\n]", enterEmail);
                 if (validateEmail(enterEmail) == 1) {
                     // Enter and validate password input
                     printf("Enter a suitable password:");
                     scanf(" %[^\n]", enterPass);
                     if (validatePassword(enterPass) == 1) {

                         printf("\n");
                         printf("You have been registered\n");
                         // write new user into file system
                         writeUsers(amountOfUsers+1,enterName,enterUsername,enterEmail,enterPass);
                         return 1;

                     }
                     else
                     printf("Sorry invalid password\n");
                         return 0;
                 }
                 else
                     printf("Sorry invalid email address\n");
                     return 0;
             }
             else
                 printf("Username is invalid\n");
                 return 0;
        }
        else
            printf("Sorry invalid name\n");
            return 0;

    }

}

// Checks length of the user input and if there are any spaces
// If no spaces and name length 4 or more, then return 1 else, returns 0
int validateUser(char *name) {

    if(strlen(name) >= 4 && strlen(name) <= 20){
      for(int i = 0; i < strlen(name); i++){
        if(isspace(name[i])){
          return 0;
        }
      }
      return 1;
    }
    return 0;
}


// Validates username by checking if the username already exists
// Checks against user list and whether the name is same as Admins
// Returns 0 on invalid entries otherwise returns 1
int validateUsername(char *username){
    if(strlen(username) >= 4 && strlen(username) <= 20) {
      // check for spaces in the username
        for(int i=0; i <= strlen(username);i++){
            if(isspace(username[i])){
              return 0;
            }
        }
        // check whether the username exists
        for(int i=0; i <= amountOfUsers;i++){

            if(strcmp(userlist[i]->username,username) == 0){
                printf("sorry that username is taken\n");
                return 0;
            }
            else if(strcmp("Librarian", username) == 0){
                printf("Sorry that username is taken\n");
                return 0;
            }
        }
        return 1;
    }
    else {
        return 0;
    }
}

// Validate Email, checks for string length and @ symbol
// Returns 0 on invalid entries otherwise returns 1
int validateEmail(char *email){


    if(strlen(email) >= 5 && strlen(email) <= 40) {
        for (int i = 0; i < strlen(email); i++) {
            if(isspace(email[i])){
              return 0;
            }
        }
        for (int i = 0; i < strlen(email); i++) {
            if (email[i] == '@') {
                return 1;
            }
        }

    }
    return 0;
}

// Checks for capital letters and number input
// Returns 0 on invalid entries otherwise returns 1
int validatePassword(char *pass){
    int containCap = 0;
    int containNum = 0;

    if(strlen(pass) >= 5 && strlen(pass) <= 20) {

        for (int i = 0; i < strlen(pass); i++) {
            if(isspace(pass[i])){
              return 0;
            }
            else if(isdigit(pass[i])){
                containNum = 1;
            }

            else if(isupper(pass[i])){
                containCap = 1;
            }
        }
        if((containCap && containNum) == 1){
            return 1;
        }
    }
    return 0;
}

// Writes new users into the user.txt file
// Takes the 4 field of the User structure as parameters which are then written
// Returns 0 once the file has written
int writeUsers(int id, char *name, char *username, char *email, char *password){

    int num;
    FILE *outfile;

    // open file for writing
    outfile = fopen("../users.txt", "a");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // write struct to file

    fprintf(outfile,"%i\t%s;\t%s;\t%s;\t%s\n",id, name,username,email,password);


    // close file
    fclose (outfile);

    return 0;

}

// Loads users from the text file into the User List
// Returns 0 once the whole file is read
int loadUsers(){
    counter = 0;
    int c;
    FILE *infile;


    // Open file for reading user data
    infile = fopen ("../users.txt", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }


    // read file contents till end of file
    while((c = getc(infile)) != EOF){
        userlist[counter] = (User*) malloc(sizeof(User));

        fscanf(infile,"%i\t%[^;];\t%[^;];\t%[^;];\t%s/n",&userlist[counter]->id,userlist[counter]->name,userlist[counter]->username
               ,userlist[counter]->email,userlist[counter]->password);
        counter++;

    }
    amountOfUsers = counter-1;

    // close file
    fclose (infile);

    return 0;

}
