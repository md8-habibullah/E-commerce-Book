#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "total.h"

// Define the global database pointer declared in total.h
sqlite3 *db;

void display_menu()
{
    
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("==========================================\n");
    printf("        WELCOME TO E-Commerce Book        \n");
    printf("==========================================\n");
    printf("  [1] Login to Account                   \n");
    printf("  [2] Create New Account                 \n");
    printf("  [3] Login as Admin                     \n");
    printf("  [0] Exit                               \n");
    printf("------------------------------------------\n");
    printf("Please select an option (1-3): ");
}

int main()
{
    // 1. Open the database connection
    int rc = sqlite3_open("ecommerce.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    int choice;
    while (1)
    {
        display_menu();
        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter a number.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            login_user();
            break;
        case 2:
            register_user();
            break;
        case 3:
            login_admin();
            break;
        case 0:
            printf("\nExiting... Goodbye!\n");
            // 2. Close the database connection before exiting
            sqlite3_close(db);
            return 0;
        default:
            printf("\nOption not recognized. Try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
    return 0;
}