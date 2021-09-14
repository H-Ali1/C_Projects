#ifndef MAIN_C_USER_H
#define MAIN_C_USER_H

//structure to store the details of a user
typedef struct
{
    int id; //User ID
    char name[20]; // Name of the user
    char username[20]; // Username of the user
    char email[30]; // Email of the user
    char password[20]; // Password of the user
} User;



// List of User Struct that will hold all user data from the file
extern User *userlist[1000]; //array of users


//Global variable that stores currentUser logged in
char currentUser[20];

// functions

// Function is used to register a new user
// Returns 1 if the registration is successful, otherwise returns 0
int getRegistered();
// Function used to login already existing users into the library
// Also used to login admin into the system
// Returns 0 if login failed or user quits the login Function
// Returns 1 if a user logs in otherwise
// Returns 2 if an admin logins into library system
int getLogin();
// Functions that validate the user inputs for registration
// Function used to validate the name of the user
int validateUser(char* name);
// Function used to validate the username of the user
// Returns 0 if the validation does not pass
// Returs 1 if the validation passes
int validateUsername(char *userName);
// Function used to validate the email of the user by testing
// If it contains @ and spaces
// Returns 0 if the validation does not pass
// Returs 1 if the validation passes
int validateEmail(char *enterEmail);
// Function used to validate the password of the user
// Returns 0 if the validation does not pass
// Returs 1 if the validation passes
int validatePassword(char *enterPass);

// Function writes the new user into the file containing all users.
// Takes as parameters the newly validated inputs of the user
// Returns 0 once completed
int writeUsers(int id, char *name, char *username, char *email, char *password);
// Function loads the user data into a list of struct Users by reading the file
// This function is used to login users into the system and for validation
//Returns 0 once completed
int loadUsers();


#endif //MAIN_C_USER_H
