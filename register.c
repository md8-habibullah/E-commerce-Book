#include <stdio.h>
#include <string.h>
#include <sqlite3.h> // Include sqlite3 header
#include "total.h"

// The next_id() function is REMOVED entirely. 
// SQLite's PRIMARY KEY AUTOINCREMENT handles this automatically.

void register_user()
{
    char username[50], password[50], email[100];
    sqlite3_stmt *res; // Handle for the prepared statement

    printf("\n\t\t----------------------------\n");
    printf("\t\t USER REGISTRATION PORTAL \n");
    printf("\t\t----------------------------\n");
    
    printf("\t\t%-15s: ", "Username");
    scanf("%s", username);
    
    printf("\t\t%-15s: ", "Email Address");
    scanf("%s", email);

    printf("\t\t%-15s: ", "Password");
    scanf("%s", password);

    // SQL Query to insert data. '?' are placeholders to prevent SQL injection.
    const char *sql = "INSERT INTO users (username, email, password) VALUES (?, ?, ?);";

    // 1. Prepare the SQL statement
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc != SQLITE_OK) {
        printf("\t\t[ERROR] Failed to prepare database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // 2. Bind the user input to the '?' placeholders
    sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(res, 2, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(res, 3, password, -1, SQLITE_STATIC);

    // 3. Execute the statement
    rc = sqlite3_step(res);

    if (rc == SQLITE_DONE) {
        printf("\t\t----------------------------\n");
        printf("\t\t[SUCCESS] Registered successfully!\n");
        // sqlite3_last_insert_rowid gets the ID created by AUTOINCREMENT
        printf("\t\tYour User ID is: %lld\n", sqlite3_last_insert_rowid(db));
        printf("\t\t----------------------------\n");
    } else {
        printf("\t\t[ERROR] Registration failed: %s\n", sqlite3_errmsg(db));
    }

    // 4. Clean up the prepared statement
    sqlite3_finalize(res);
}