#include <stdio.h>
#include "total.h"
#include <string.h>

// void showBookDetails(int id);
void userPage()
{
    int choice;
    int bookId;
    char res[10];

    do
    {
        // --- DASHBOARD UI START ---
        printf("\n\t\t========================================");
        printf("\n\t\t           USER CONTROL PANEL           ");
        printf("\n\t\t========================================");
        printf("\n\t\t  [1] Browse Book List");
        printf("\n\t\t  [2] View My Orders");
        printf("\n\t\t  [3] Access Shopping Cart");
        printf("\n\t\t  [0] Logout Session");
        printf("\n\t\t----------------------------------------");
        printf("\n\t\tEnter choice: ");
        // --- DASHBOARD UI END ---

        if (scanf("%d", &choice) != 1)
        {
            printf("\n\t\t[!] Please enter a valid number.");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("\n\t\t--- LOADING BOOK GALLERY ---\n");
            showBookList();

            printf("\n\t\tDo you want to view Details? (Yes/No): ");
            scanf("%s", res);

            // Flexible check for "Yes" or "yes"
            if (strcmp(res, "Yes") == 0 || strcmp(res, "yes") == 0)
            {
                printf("\t\tEnter Book ID to inspect: ");
                scanf("%d", &bookId);
                showBookDetails(bookId);
            }
            break;

        case 2:
            printf("\n\t\t>> Opening Order History...\n");
            // order_list_function();
            break;

        case 3:
            printf("\n\t\t>> Opening Your Cart...\n");
            // cart_function();
            break;

        case 0:
            printf("\n\t\t[!] Logging out... Session ended safely.\n");
            break;

        default:
            printf("\n\t\t[!] Selection not recognized!\n");
        }

        if (choice != 0)
        {
            printf("\n\t\tPress Enter to return to Dashboard...");
            getchar();
            getchar(); // Wait for user input
        }

    } while (choice != 0);
}


// void showBookDetails(int id) {
//     FILE *fp = fopen("books.dat", "rb");
//     if(!fp) {
//         printf("No books available!\n");
//         return;
//     }

//     Book b;
//     int found = 0;

//     while(fread(&b, sizeof(Book), 1, fp)) {
//         if(b.id == id) {
//             printf("\n--- BOOK DETAILS ---\n");
//             printf("ID: %d\n", b.id);
//             printf("Title: %s\n", b.title);
//             printf("Author: %s\n", b.author);
//             printf("Price: %.2f\n", b.price);
//             printf("Quantity: %d\n", b.quantity);
//             found = 1;
//             break;
//         }
//     }

//     if(!found)
//         printf("Book not found!\n");

//     fclose(fp);
// }
