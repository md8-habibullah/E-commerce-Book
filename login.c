#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "total.h"

// Define colors for a professional look
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define CYN "\x1B[36m"
#define RESET "\x1B[0m"

int login_user()
{
    FILE *fp;
    char username[50], password[50], line[256];
    int attempts = 3;

    // Header Design
    printf("\n\t\t" CYN "================================" RESET);
    printf("\n\t\t      UNSECURE USER LOGIN         ");
    printf("\n\t\t" CYN "================================" RESET "\n");

    printf("\t\t%-12s: ", "Username");
    scanf("%s", username);

    fp = fopen("users_database.txt", "r");
    if (fp == NULL)
    {
        printf("\n\t\t" RED "[!] Error: No database found." RESET "\n");
        return 0;
    }

    while (attempts > 0)
    {
        printf("\t\t%-12s: ", "Password");
        scanf("%s", password);

        rewind(fp);
        int found = 0;

        while (fgets(line, sizeof(line), fp))
        {
            int id;
            char u[50], e[100], p[50];

            // Parsing the CSV format
            sscanf(line, "%d,%49[^,],%99[^,],%49[^\n]", &id, u, e, p);

            if (strcmp(username, u) == 0 && strcmp(password, p) == 0)
            {
                printf("\n\t\t" GRN "--------------------------------" RESET);
                printf("\n\t\t[+] Login successful!");
                printf("\n\t\tWelcome back, " YEL "%s" RESET "!", u);
                printf("\n\t\t" GRN "--------------------------------" RESET "\n");

                fclose(fp);

                // Add a small pause before clearing screen for userPage
                printf("\n\t\tPress Enter to enter Dashboard...");
                getchar();
                getchar();

                userPage(u);
                return 1;
            }
        }

        attempts--;
        if (attempts > 0)
        {
            printf("\n\t\t" YEL "[!] Incorrect password." RESET);
            printf("\n\t\tRemaining attempts: " RED "%d" RESET "\n\n", attempts);
        }
    }

    fclose(fp);
    printf("\n\t\t" RED "********************************" RESET);
    printf("\n\t\t [!] ACCESS DENIED: LOCKOUT");
    printf("\n\t\t" RED "********************************" RESET "\n");
    //  we will shift user in forgot password function;
    //  but first if else ask he want go or not?

    char choice;
    printf("\n\t\t Do you want to recover your password? (y/n): ");

    getchar();
    scanf("%c", &choice);
    system("clear");

    if (choice == 'y' || choice == 'Y')
    {
        forget_pass();
    }
    else
    {
        printf("\n\t\t Returning to main menu...\n");
        return 0;
    }

    printf("\n\t\t" RED "********************************" RESET "\n");

    return 0;
}