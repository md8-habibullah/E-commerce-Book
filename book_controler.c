#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "total.h"

// nextBook_id() is REMOVED. SQLite handles IDs automatically.

void addBook()
{
        char name[50], author[50];
        float price;
        int quantity;
        sqlite3_stmt *res;

        printf("\n\t\t=========== ADD NEW BOOK ===========");
        printf("\n\t\tBook Title  : ");
        scanf(" %[^\n]", name);
        printf("\t\tAuthor Name : ");
        scanf(" %[^\n]", author);
        printf("\t\tUnit Price  : ");
        scanf("%f", &price);
        printf("\t\tInitial Qty : ");
        scanf("%d", &quantity);

        const char *sql = "INSERT INTO books (title, author, price, quantity) VALUES (?, ?, ?, ?);";

        if (sqlite3_prepare_v2(db, sql, -1, &res, 0) == SQLITE_OK)
        {
                sqlite3_bind_text(res, 1, name, -1, SQLITE_STATIC);
                sqlite3_bind_text(res, 2, author, -1, SQLITE_STATIC);
                sqlite3_bind_double(res, 3, price);
                sqlite3_bind_int(res, 4, quantity);

                if (sqlite3_step(res) == SQLITE_DONE)
                {
                        printf("\t\t[SUCCESS] Book added to database.\n");
                }
                sqlite3_finalize(res);
        }
}

void editBook()
{
        int bookId, choice;
        float newPrice;
        int newQty;
        char sql[256];

        showBookList(); // Show list so user knows IDs
        printf("\n\t\tEnter Book ID to Edit: ");
        scanf("%d", &bookId);

        printf("\t\t[1] Update Price  [2] Update Quantity\n\t\tChoice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
                printf("\t\tNew Price: ");
                scanf("%f", &newPrice);
                sprintf(sql, "UPDATE books SET price = %.2f WHERE id = %d;", newPrice, bookId);
        }
        else
        {
                printf("\t\tNew Quantity: ");
                scanf("%d", &newQty);
                sprintf(sql, "UPDATE books SET quantity = %d WHERE id = %d;", newQty, bookId);
        }

        // Optimization: Executing a single line update instead of rewriting the whole file
        if (sqlite3_exec(db, sql, 0, 0, 0) == SQLITE_OK)
        {
                printf("\t\t[SUCCESS] Book ID #%d updated.\n", bookId);
        }
        else
        {
                printf("\t\t[ERROR] Update failed.\n");
        }
}

void deleteBook()
{
        int bookId;
        char sql[128];

        showBookList();
        printf("\n\t\tEnter Book ID to REMOVE: ");
        scanf("%d", &bookId);

        // No more copying lines to temp.txt and deleting books.txt!
        sprintf(sql, "DELETE FROM books WHERE id = %d;", bookId);

        if (sqlite3_exec(db, sql, 0, 0, 0) == SQLITE_OK)
        {
                printf("\t\t[SUCCESS] Book removed permanently.\n");
        }
}
void showBookDetails(int targetId, char *username)
{
        sqlite3_stmt *res;
        const char *sql = "SELECT id, title, author, price, quantity FROM books WHERE id = ?;";

        if (sqlite3_prepare_v2(db, sql, -1, &res, 0) == SQLITE_OK)
        {
                sqlite3_bind_int(res, 1, targetId);

                if (sqlite3_step(res) == SQLITE_ROW)
                {
                        int id = sqlite3_column_int(res, 0);
                        const char *name = (const char *)sqlite3_column_text(res, 1);
                        const char *author = (const char *)sqlite3_column_text(res, 2);
                        float price = (float)sqlite3_column_double(res, 3);
                        int quantity = sqlite3_column_int(res, 4);

                        printf("\n\t\t--------- FULL BOOK DETAILS ---------");
                        printf("\n\t\t  BOOK ID    : %d", id);
                        printf("\n\t\t  TITLE      : %s", name);
                        printf("\n\t\t  AUTHOR     : %s", author);
                        printf("\n\t\t  PRICE      : $%.2f", price);
                        printf("\n\t\t  STOCK QTY  : %d units", quantity);
                        printf("\n\t\t-------------------------------------\n");

                        int orderChoice;
                        // printf("\t\t[1] Order Now  [0] Back to List\n");
                        printf("\t\t[1] Add to Cart  [0] Back to List\n");
                        printf("\t\tSelection: ");
                        scanf("%d", &orderChoice);

                        if (orderChoice == 1)
                        {
                                // This calls the refactored placeOrder in order.c
                                // placeOrder(username, id, (char *)name, price);
                                addToCart(username, id, (char *)name, price);
                        }
                }
                else
                {
                        printf("\n\t\t[!] Book with ID %d not found.\n", targetId);
                }
                sqlite3_finalize(res);
        }
        else
        {
                printf("\t\t[!] Database Error: %s\n", sqlite3_errmsg(db));
        }
}

void showBookList()
{
        sqlite3_stmt *res;
        const char *sql = "SELECT id, title, author FROM books;";

        printf("\n\t\t%-5s | %-20s | %-15s\n", "ID", "BOOK TITLE", "AUTHOR");
        printf("\t\t--------------------------------------------------\n");

        if (sqlite3_prepare_v2(db, sql, -1, &res, 0) == SQLITE_OK)
        {
                while (sqlite3_step(res) == SQLITE_ROW)
                {
                        // Retrieve data by column index
                        int id = sqlite3_column_int(res, 0);
                        const unsigned char *title = sqlite3_column_text(res, 1);
                        const unsigned char *author = sqlite3_column_text(res, 2);

                        printf("\t\t%-5d | %-20.20s | %-15.15s\n", id, title, author);
                }
                sqlite3_finalize(res);
        }
}