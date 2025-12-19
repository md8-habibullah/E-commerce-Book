#include <stdio.h>
#include <string.h>
#include "total.h"

void adminPage();
void userPage();
void showBookList();

int main() {
    char username[50], password[50];
    int loginSuccess = 0;

    // Admin credentials
    char adminUser[] = "admin";
    char adminPass[] = "admin123";
    // int admin=0;
    // User credentials
    char userUser[] = "user";
    char userPass[] = "user123";

    printf("===== BOOK SHOP LOGIN =====\n");

    do {
        printf("\nEnter Username: ");
        scanf("%s", username);

        printf("Enter Password: ");
        scanf("%s", password);

        // Admin login
        if (strcmp(username, adminUser) == 0 && strcmp(password, adminPass) == 0) {
            printf("\nAdmin Login Successful!\n");
            adminPage();
            loginSuccess = 1;
        }
        // User login
        else if (strcmp(username, userUser) == 0 && strcmp(password, userPass) == 0) {
            printf("\nUser Login Successful!\n");
            userPage();
            loginSuccess = 1;
        }
        else {
            printf("\nInvalid Username or Password. Try Again.\n");
        }

    } while (loginSuccess == 0);

    return 0;
}



