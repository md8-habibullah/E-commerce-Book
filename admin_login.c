#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "total.h"

int login_admin()
{
    char username[50], password[50];
    sqlite3_stmt *res;
    int attempts = 3;

    printf("===== ADMIN LOGIN =====\n");
    printf("Enter admin username: ");
    scanf("%s", username);

    while (attempts > 0)
    {
        printf("Enter admin password: ");
        scanf("%s", password);

        // SQL query to check admin credentials
        const char *sql = "SELECT username FROM admins WHERE username = ? AND password = ?;";

        if (sqlite3_prepare_v2(db, sql, -1, &res, 0) != SQLITE_OK) {
            printf("Database error: %s\n", sqlite3_errmsg(db));
            return 0;
        }

        sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(res, 2, password, -1, SQLITE_STATIC);

        if (sqlite3_step(res) == SQLITE_ROW) {
            printf("Admin login successful! Welcome %s\n", username);
            sqlite3_finalize(res);
            adminPage();
            return 1;
        }

        attempts--;
        sqlite3_finalize(res);
        printf("Wrong password! Attempts left: %d\n", attempts);
    }

    printf("Invalid admin username or password\n");
    return 0;
}