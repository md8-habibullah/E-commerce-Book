#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>
#include "total.h"

// nextOrder_id() is REMOVED. SQLite AUTOINCREMENT handles this.

void placeOrder(char *username, int bookId, char *bookName, float price)
{
    sqlite3_stmt *res;
    char address[100], phone[20], date[20];

    // Get Date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // New: Ask for Delivery Details
    printf("\n\t\t[DELIVERY INFO]");
    printf("\n\t\tEnter Delivery Address: ");
    scanf(" %[^\n]", address); // Allows spaces
    printf("\t\tEnter Phone Number: ");
    scanf("%s", phone);

    const char *sql_order = "INSERT INTO orders (username, book_id, book_name, price, order_date, delivery_address, phone_number) VALUES (?, ?, ?, ?, ?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql_order, -1, &res, 0) == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_int(res, 2, bookId);
        sqlite3_bind_text(res, 3, bookName, -1, SQLITE_STATIC);
        sqlite3_bind_double(res, 4, price);
        sqlite3_bind_text(res, 5, date, -1, SQLITE_STATIC);
        sqlite3_bind_text(res, 6, address, -1, SQLITE_STATIC); // Bind Address
        sqlite3_bind_text(res, 7, phone, -1, SQLITE_STATIC);   // Bind Phone

        sqlite3_step(res);
        sqlite3_finalize(res);
    }

    // SQL 2: Update stock quantity (Robust logic)
    const char *sql_stock = "UPDATE books SET quantity = quantity - 1 WHERE id = ? AND quantity > 0;";
    sqlite3_stmt *stock_res;
    if (sqlite3_prepare_v2(db, sql_stock, -1, &stock_res, 0) == SQLITE_OK)
    {
        sqlite3_bind_int(stock_res, 1, bookId);
        sqlite3_step(stock_res);
        sqlite3_finalize(stock_res);
    }
}
void viewOrderHistory(char *currentUser)
{
    sqlite3_stmt *res;

    // Fetch the new columns: delivery_address, phone_number, and status
    const char *sql = "SELECT id, book_name, price, order_date, delivery_address, phone_number, status "
                      "FROM orders WHERE username = ?;";

    printf("\n\t\t========================= YOUR VAST ORDER HISTORY =========================\n");
    printf("\t\t%-5s | %-15s | %-8s | %-12s | %-10s | %-15s\n", 
           "ID", "BOOK NAME", "PRICE", "DATE", "STATUS", "PHONE");
    printf("\t\t---------------------------------------------------------------------------\n");

    if (sqlite3_prepare_v2(db, sql, -1, &res, 0) == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, currentUser, -1, SQLITE_STATIC);

        int found = 0;
        while (sqlite3_step(res) == SQLITE_ROW)
        {
            found = 1;
            int id = sqlite3_column_int(res, 0);
            const char *name = (const char *)sqlite3_column_text(res, 1);
            float price = (float)sqlite3_column_double(res, 2);
            const char *date = (const char *)sqlite3_column_text(res, 3);
            const char *address = (const char *)sqlite3_column_text(res, 4);
            const char *phone = (const char *)sqlite3_column_text(res, 5);
            const char *status = (const char *)sqlite3_column_text(res, 6);

            // Main Row
            printf("\t\t#%-4d | %-15.15s | $%-7.2f | %-12s | %-10s | %-15s\n",
                   id, name, price, date, status, phone);
            
            // Sub-row for Address (to keep the table clean)
            printf("\t\t      >> Delivery To: %s\n", address);
            printf("\t\t---------------------------------------------------------------------------\n");
        }

        if (!found)
        {
            printf("\t\t                No orders found for your account.                   \n");
        }
        sqlite3_finalize(res);
    }
}