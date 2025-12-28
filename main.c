#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "total.h"

void display_menu()
{
    system("clear");

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
            printf("\n--- Redirecting to Login ---\n");
            login_user();
            break;
        case 2:
            printf("\n--- Opening Registration ---\n");
            register_user();
            break;
        case 3:
            printf("\n--- Opening as Admin ---\n");
            login_admin();
            break;

        case 0:
            printf("\nExiting... Goodbye!\n");
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