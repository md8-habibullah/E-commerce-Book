#include <stdio.h>
#include <string.h>
#include "total.h"

void manageOrders();
void adminPage()
{
    int choice;
    do
    {
        printf("\n===== ADMIN PANEL =====\n");
        printf("1. Add Book\n");
        printf("2. Edit Book\n");
        printf("3. Delete Book\n");
        printf("4. Show Book List\n");
        printf("5. Manage Orders (Status)\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook();
            break;

        case 2:
            editBook();
            break;

        case 3:
            deleteBook();
            break;

        case 4:
            showBookList();
            break;
        case 5:
            manageOrders();
            break;

        case 0:
            printf("Exiting admin panel...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 0);
}


void manageOrders() {
    sqlite3_stmt *res;
    const char *sql = "SELECT id, username, book_name, status, delivery_address FROM orders;";
    
    printf("\n%-5s | %-10s | %-15s | %-10s | %s\n", "ID", "USER", "BOOK", "STATUS", "ADDRESS");
    if (sqlite3_prepare_v2(db, sql, -1, &res, 0) == SQLITE_OK) {
        while (sqlite3_step(res) == SQLITE_ROW) {
            printf("%-5d | %-10s | %-15s | %-10s | %s\n", 
                sqlite3_column_int(res, 0), sqlite3_column_text(res, 1),
                sqlite3_column_text(res, 2), sqlite3_column_text(res, 3),
                sqlite3_column_text(res, 4));
        }
        sqlite3_finalize(res);
    }

    int orderId, statusChoice;
    printf("\nEnter Order ID to change status (0 to cancel): ");
    scanf("%d", &orderId);
    if(orderId == 0) return;

    printf("[1] Delivered  [2] Cancelled  [3] Pending: ");
    scanf("%d", &statusChoice);
    
    char *status = (statusChoice == 1) ? "Delivered" : (statusChoice == 2) ? "Cancelled" : "Pending";
    char updateSql[128];
    sprintf(updateSql, "UPDATE orders SET status = '%s' WHERE id = %d;", status, orderId);
    
    if (sqlite3_exec(db, updateSql, 0, 0, 0) == SQLITE_OK) {
        printf("[SUCCESS] Status updated to %s\n", status);
    }
}