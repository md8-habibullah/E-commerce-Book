#include <stdio.h>
#include <string.h>
#include "total.h"

int nextBook_id()
{
        FILE *fp = fopen("books.txt", "r");
        if (fp == NULL)
                return 1;
        int count = 0;
        char ch;
        while ((ch = fgetc(fp)) != EOF)
        {
                if (ch == '\n')
                        count++;
        }
        fclose(fp);
        return count + 1; // ID starts from 1
}

void addBook()
{
        FILE *fp;
        int id = nextBook_id();
        char name[50], author[50];
        float price;
        int quantity;

        printf("\n\t\t========================================");
        printf("\n\t\t           ADD NEW INVENTORY            ");
        printf("\n\t\t========================================\n");

        printf("\t\t%-15s: ", "Book Title");
        scanf(" %[^\n]", name);
        printf("\t\t%-15s: ", "Author Name");
        scanf(" %[^\n]", author);
        printf("\t\t%-15s: ", "Unit Price");
        scanf("%f", &price);
        printf("\t\t%-15s: ", "Initial Qty");
        scanf("%d", &quantity);

        fp = fopen("books.txt", "a");
        fprintf(fp, "%d,%s,%s,%.2f,%d\n", id, name, author, price, quantity);
        fclose(fp);

        printf("\t\t----------------------------------------\n");
        printf("\t\t[SUCCESS] Book ID #%d stored in database.\n", id);
}

void editBook()
{
        FILE *fp = fopen("books.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        if (fp == NULL)
        {
                printf("\t\t[!] Error: No database found.\n");
                return;
        }

        int bookId, found = 0;
        char line[200];

        showBookList();
        printf("\n\t\tEnter Target Book ID to Edit: ");
        scanf("%d", &bookId);

        while (fgets(line, sizeof(line), fp))
        {
                int id, quantity;
                char name[50], author[50];
                float price;

                sscanf(line, "%d,%49[^,],%49[^,],%f,%d", &id, name, author, &price, &quantity);

                if (id == bookId)
                {
                        found = 1;
                        int choice;
                        printf("\n\t\t--- EDITING: %s ---\n", name);
                        printf("\t\t[1] Name  [2] Author  [3] Price  [4] Quantity\n");
                        printf("\t\tChange Choice: ");
                        scanf("%d", &choice);

                        if (choice == 1)
                        {
                                printf("\t\tNew Name: ");
                                scanf(" %[^\n]", name);
                        }
                        else if (choice == 2)
                        {
                                printf("\t\tNew Author: ");
                                scanf(" %[^\n]", author);
                        }
                        else if (choice == 3)
                        {
                                printf("\t\tNew Price: ");
                                scanf("%f", &price);
                        }
                        else if (choice == 4)
                        {
                                printf("\t\tNew Qty: ");
                                scanf("%d", &quantity);
                        }
                }
                fprintf(temp, "%d,%s,%s,%.2f,%d\n", id, name, author, price, quantity);
        }
        fclose(fp);
        fclose(temp);
        remove("books.txt");
        rename("temp.txt", "books.txt");

        if (found)
                printf("\t\t[SUCCESS] Database record updated.\n");
        else
                printf("\t\t[ERROR] ID #%d not found.\n", bookId);
}

void deleteBook()
{
        FILE *fp = fopen("books.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        if (fp == NULL)
        {
                printf("\t\t[!] Database Empty.\n");
                return;
        }

        int bookId, found = 0;
        char line[200];

        showBookList();
        printf("\n\t\tEnter Book ID to REMOVE: ");
        scanf("%d", &bookId);

        while (fgets(line, sizeof(line), fp))
        {
                int id, quantity;
                char name[50], author[50];
                float price;
                sscanf(line, "%d,%49[^,],%49[^,],%f,%d", &id, name, author, &price, &quantity);

                if (id == bookId)
                {
                        found = 1;
                        continue;
                }
                fprintf(temp, "%d,%s,%s,%.2f,%d\n", id, name, author, price, quantity);
        }
        fclose(fp);
        fclose(temp);
        remove("books.txt");
        rename("temp.txt", "books.txt");

        if (found)
                printf("\t\t[SUCCESS] Book removed permanently.\n");
        else
                printf("\t\t[ERROR] Record not found.\n");
}

void showBookList()
{
        FILE *fp = fopen("books.txt", "r");
        if (fp == NULL)
        {
                printf("\t\t[!] No books available.\n");
                return;
        }
        char line[200];

        printf("\n\t\t%-5s | %-20s | %-15s\n", "ID", "BOOK TITLE", "AUTHOR");
        printf("\t\t--------------------------------------------------\n");
        while (fgets(line, sizeof(line), fp))
        {
                int id;
                char name[50], author[50];
                // Read the first 3 fields from CSV
                sscanf(line, "%d,%49[^,],%49[^,]", &id, name, author);
                printf("\t\t%-5d | %-20.20s | %-15.15s\n", id, name, author);
        }
        fclose(fp);
}

// ... other functions ...

void showBookDetails(int targetId, char *username) // Accept username here
{
        FILE *fp = fopen("books.txt", "r");
        if (fp == NULL)
        {
                printf("\t\t[!] Error opening database.\n");
                return;
        }

        char line[200];
        int found = 0;

        while (fgets(line, sizeof(line), fp))
        {
                int id, quantity;
                char name[50], author[50];
                float price;

                sscanf(line, "%d,%49[^,],%49[^,],%f,%d", &id, name, author, &price, &quantity);

                if (id == targetId)
                {
                        found = 1;
                        printf("\n\t\t--------- FULL BOOK DETAILS ---------");
                        printf("\n\t\t  BOOK ID    : %d", id);
                        printf("\n\t\t  TITLE      : %s", name);
                        printf("\n\t\t  AUTHOR     : %s", author);
                        printf("\n\t\t  PRICE      : $%.2f", price);
                        printf("\n\t\t  STOCK QTY  : %d units", quantity);
                        printf("\n\t\t-------------------------------------\n");

                        int orderChoice;
                        printf("\t\t[1] Order Now  [0] Back to List\n");
                        printf("\t\tSelection: ");
                        scanf("%d", &orderChoice);

                        if (orderChoice == 1)
                        {
                                // Now passing the username correctly to order.c
                                placeOrder(username, id, name, price);
                        }
                        break;
                }
        }
        if (!found)
                printf("\n\t\t[!] Book with ID %d not found.\n", targetId);
        fclose(fp);
}