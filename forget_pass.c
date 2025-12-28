#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "total.h"

void forget_pass()
{
    char username[50], email[50];
    sqlite3_stmt *res;

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your email: ");
    scanf("%s", email);

    const char *sql = "SELECT password FROM users WHERE username = ? AND email = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &res, 0) == SQLITE_OK) {
        sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(res, 2, email, -1, SQLITE_STATIC);

        if (sqlite3_step(res) == SQLITE_ROW) {
            // Retrieve the password from the first column of the result
            const unsigned char *password = sqlite3_column_text(res, 0);
            printf("Your password is: %s\n", password);
        } else {
            printf("No matching user found.\n");
        }
        sqlite3_finalize(res);
    } else {
        printf("Database error.\n");
    }
}