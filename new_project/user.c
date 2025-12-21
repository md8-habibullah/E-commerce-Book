#include <stdio.h>
#include "total.h"
#include <string.h>

void userPage(char *loggedInUser)
{
    // REMOVED: placeOrder(loggedInUser, id, name, price); 
    // This was an error because id, name, and price are unknown here.

    int choice;
    int bookId;

    do {
        printf("\n\t\t========================================");
        printf("\n\t\t           USER CONTROL PANEL           ");
        printf("\n\t\t========================================");
        printf("\n\t\t  [1] Browse Book List");
        printf("\n\t\t  [2] View My Orders");
        printf("\n\t\t  [0] Logout Session");
        printf("\n\t\t----------------------------------------");
        printf("\n\t\tEnter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\n\t\t[!] Invalid input.");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                showBookList();
                printf("\n\t\tEnter Book ID to view full details: ");
                if (scanf("%d", &bookId) == 1) {
                    // Pass the loggedInUser here so the next function can use it
                    showBookDetails(bookId, loggedInUser);
                }
                break;
            case 2:
                viewOrderHistory(loggedInUser);
                break;
            case 0:
                printf("\n\t\t[!] Logging out...\n");
                break;
            default:
                printf("\n\t\t[!] Selection not recognized!\n");
        }

        if (choice != 0) {
            printf("\n\t\tPress Enter to return to Dashboard...");
            getchar(); getchar();
        }
    } while (choice != 0);
}