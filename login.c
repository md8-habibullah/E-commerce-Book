#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h> // Include sqlite3 header
#include "total.h"

// Define colors for a professional look
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define CYN "\x1B[36m"
#define RESET "\x1B[0m"

int login_user()
{
    char username[50], password[50];
    sqlite3_stmt *res; // Handle for the prepared statement
    int attempts = 3;

    // Header Design
    printf("\n\t\t" CYN "================================" RESET);
    printf("\n\t\t      SECURE USER LOGIN         ");
    printf("\n\t\t" CYN "================================" RESET "\n");

    printf("\t\t%-12s: ", "Username");
    scanf("%s", username);

    while (attempts > 0)
    {
        printf("\t\t%-12s: ", "Password");
        scanf("%s", password);

        // SQL Query to check for matching user
        const char *sql = "SELECT username FROM users WHERE username = ? AND password = ?;";

        // 1. Prepare the SQL statement
        if (sqlite3_prepare_v2(db, sql, -1, &res, 0) != SQLITE_OK)
        {
            printf("\n\t\t" RED "[!] Database Error: %s" RESET "\n", sqlite3_errmsg(db));
            return 0;
        }

        // 2. Bind inputs to placeholders
        sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(res, 2, password, -1, SQLITE_STATIC);

        // 3. Execute and check result
        int step = sqlite3_step(res);

        if (step == SQLITE_ROW)
        {
            // Success! Row found means credentials match.
            printf("\n\t\t" GRN "--------------------------------" RESET);
            printf("\n\t\t[+] Login successful!");
            printf("\n\t\tWelcome back, " YEL "%s" RESET "!", username);
            printf("\n\t\t" GRN "--------------------------------" RESET "\n");

            sqlite3_finalize(res); // Always finalize before returning

            printf("\n\t\tPress Enter to enter Dashboard...");
            getchar();
            getchar();

            userPage(username);
            return 1;
        }
        else
        {
            // No row found or error
            attempts--;
            if (attempts > 0)
            {
                printf("\n\t\t" YEL "[!] Incorrect credentials." RESET);
                printf("\n\t\tRemaining attempts: " RED "%d" RESET "\n\n", attempts);
            }
        }

        sqlite3_finalize(res); // Finalize after each attempt loop
    }

    // Lockout logic remains the same
    printf("\n\t\t" RED "********************************" RESET);
    printf("\n\t\t [!] ACCESS DENIED: LOCKOUT");
    printf("\n\t\t" RED "********************************" RESET "\n");

    char choice;
    printf("\n\t\t Do you want to recover your password? (y/n): ");
    getchar();
    scanf("%c", &choice);

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    if (choice == 'y' || choice == 'Y')
    {
        forget_pass();
    }
    else
    {
        printf("\n\t\t Returning to main menu...\n");
        return 0;
    }

    return 0;
}