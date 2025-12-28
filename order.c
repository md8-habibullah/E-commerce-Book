#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>
#include "total.h"

// nextOrder_id() is REMOVED. SQLite AUTOINCREMENT handles this.

void placeOrder(char *username, int bookId, char *bookName, float price)
{
    sqlite3_stmt *res;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[20];
    sprintf(date, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    const char *sql = "INSERT INTO orders (username, book_id, book_name, price, date) VALUES (?, ?, ?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &res, 0) == SQLITE_OK) {
        sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_int(res, 2, bookId);
        sqlite3_bind_text(res, 3, bookName, -1, SQLITE_STATIC);
        sqlite3_bind_double(res, 4, price);
        sqlite3_bind_text(res, 5, date, -1, SQLITE_STATIC);

        if (sqlite3_step(res) == SQLITE_DONE) {
            printf("\n\t\t[SUCCESS] Order placed for %s\n", username);
        }
        sqlite3_finalize(res);
    }
}

void viewOrderHistory(char* currentUser) {
    sqlite3_stmt *res;
    // Optimization: The database filters the records for us
    const char *sql = "SELECT id, book_name, price, date FROM orders WHERE username = ?;";

    printf("\n\t\t================ YOUR ORDER HISTORY ================\n");
    printf("\t\t%-8s | %-15s | %-8s | %-10s\n", "ORDER ID", "BOOK NAME", "PRICE", "DATE");
    printf("\t\t----------------------------------------------------\n");

    if (sqlite3_prepare_v2(db, sql, -1, &res, 0) == SQLITE_OK) {
        sqlite3_bind_text(res, 1, currentUser, -1, SQLITE_STATIC);
        
        int found = 0;
        while (sqlite3_step(res) == SQLITE_ROW) {
            found = 1;
            printf("\t\t#%-7d | %-15.15s | $%-7.2f | %-10s\n", 
                   sqlite3_column_int(res, 0),
                   sqlite3_column_text(res, 1),
                   sqlite3_column_double(res, 2),
                   sqlite3_column_text(res, 3));
        }

        if (!found) {
            printf("\t\t          No orders found for your account.         \n");
        }
        sqlite3_finalize(res);
    }
    printf("\t\t----------------------------------------------------\n");
}