#include <stdio.h>
#include <sqlite3.h>
#include "total.h"

void addToCart(char *username, int bookId, char *bookName, float price) {
    sqlite3_stmt *res;
    const char *sql = "INSERT INTO cart (username, book_id, book_name, price) VALUES (?, ?, ?, ?);";
    if (sqlite3_prepare_v2(db, sql, -1, &res, 0) == SQLITE_OK) {
        sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_int(res, 2, bookId);
        sqlite3_bind_text(res, 3, bookName, -1, SQLITE_STATIC);
        sqlite3_bind_double(res, 4, price);
        if (sqlite3_step(res) == SQLITE_DONE) printf("\n\t\t[SUCCESS] Added to cart!");
        sqlite3_finalize(res);
    }
}

void viewCart(char *username) {
    sqlite3_stmt *res;
    const char *sql = "SELECT id, book_name, price FROM cart WHERE username = ?;";
    printf("\n\t\t--- YOUR SHOPPING CART ---\n");
    if (sqlite3_prepare_v2(db, sql, -1, &res, 0) == SQLITE_OK) {
        sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
        while (sqlite3_step(res) == SQLITE_ROW) {
            printf("\t\tID: %d | %-15s | $%.2f\n", sqlite3_column_int(res, 0), 
                   sqlite3_column_text(res, 1), sqlite3_column_double(res, 2));
        }
        sqlite3_finalize(res);
    }
    printf("\t\t[1] Checkout All  [0] Back: ");
    int choice; scanf("%d", &choice);
    if (choice == 1) checkout(username);
}

void checkout(char *username) {
    // Logic: 1. SELECT all from cart for user. 
    // 2. Loop and call placeOrder() for each.
    // 3. DELETE FROM cart WHERE username = ?.
    char sql[128];
    sprintf(sql, "DELETE FROM cart WHERE username = '%s';", username);
    if (sqlite3_exec(db, sql, 0, 0, 0) == SQLITE_OK) printf("\n\t\t[SUCCESS] Order Placed!");
}