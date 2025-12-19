#include <stdio.h>
#include <string.h>
#include "total.h"


// int next_id()
 int nextBook_id()
{
        FILE *fp = fopen("books.txt", "r");
        if (fp == NULL)
        {
                return 1;
        }
        int count = 0;
        char ch;
        while ((ch = fgetc(fp)) != EOF)
        {
                if (ch == '\n')
                {
                        count++;
                }
        }
        fclose(fp);
        return count;
}

void addBook()
{
        FILE *fp;
        int id = nextBook_id();
        char name[50];
        char author[50];
        float price;
        int quantity;

        printf("===== ADD NEW BOOK =====\n");
        printf("Enter book name: ");
        scanf(" %[^\n]", name);
        printf("Enter author name: ");
        scanf(" %[^\n]", author);
        printf("Enter book price: ");
        scanf("%f", &price);
        printf("Enter book quantity: ");
        scanf("%d", &quantity);

        fp = fopen("books.txt", "a");
        fprintf(fp, "%d,%s,%s,%.2f,%d\n", id, name, author, price, quantity);
        fclose(fp);
        printf("Book added successfully! Book ID is %d \n", id);
}

// Function to delete a book by ID
void editBook()
{
        FILE *fp = fopen("books.txt", "r");
        FILE *temp = fopen("temp.txt", "w");

        if (fp == NULL)
        {
                printf("No books available.\n");
                return;
        }

        int bookId, found = 0;
        char line[200];

        showBookList();
        printf("\nEnter the Book ID to edit: ");
        scanf("%d", &bookId);

        while (fgets(line, sizeof(line), fp))
        {
                int id, quantity;
                char name[50], author[50];
                float price;

                sscanf(line, "%d,%49[^,],%49[^,],%f,%d",
                       &id, name, author, &price, &quantity);

                if (id == bookId)
                {
                        found = 1;
                        int choice;

                        printf("\nEditing Book ID %d\n", id);
                        printf("1. Name\n2. Author\n3. Price\n4. Quantity\nChoose: ");
                        scanf("%d", &choice);

                        if (choice == 1)
                        {
                                printf("Enter new name: ");
                                scanf(" %[^\n]", name);
                        }
                        else if (choice == 2)
                        {
                                printf("Enter new author: ");
                                scanf(" %[^\n]", author);
                        }
                        else if (choice == 3)
                        {
                                printf("Enter new price: ");
                                scanf("%f", &price);
                        }
                        else if (choice == 4)
                        {
                                printf("Enter new quantity: ");
                                scanf("%d", &quantity);
                        }
                        else
                        {
                                printf("Invalid choice. No changes made.\n");
                        }
                }

                fprintf(temp, "%d,%s,%s,%.2f,%d\n",
                        id, name, author, price, quantity);
        }

        fclose(fp);
        fclose(temp);

        remove("books.txt");
        rename("temp.txt", "books.txt");

        if (found)
                printf("Book updated successfully.\n");
        else
                printf("Book ID not found.\n");
}

// Function to delete a book
void deleteBook()
{
        FILE *fp = fopen("books.txt", "r");
        FILE *temp = fopen("temp.txt", "w");

        if (fp == NULL)
        {
                printf("No books available.\n");
                return;
        }

        int bookId, found = 0;
        char line[200];

        showBookList();
        printf("\nEnter the Book ID to delete: ");
        scanf("%d", &bookId);

        while (fgets(line, sizeof(line), fp))
        {
                int id, quantity;
                char name[50], author[50];
                float price;

                sscanf(line, "%d,%49[^,],%49[^,],%f,%d",
                       &id, name, author, &price, &quantity);

                if (id == bookId)
                {
                        found = 1;
                        continue;
                }

                fprintf(temp, "%d,%s,%s,%.2f,%d\n",
                        id, name, author, price, quantity);
        }

        fclose(fp);
        fclose(temp);

        remove("books.txt");
        rename("temp.txt", "books.txt");

        if (found)
                printf("Book deleted successfully.\n");
        else
                printf("Book ID not found.\n");
}

// Function to display the list of books
void showBookList()
{
        FILE *fp = fopen("books.txt", "r");
        if (fp == NULL)
        {
                printf("No books available.\n");
                return;
        }
        char line[200];
        printf("===== BOOK LIST =====\n");
        printf("ID | Name | Author | Price | Quantity\n");
        printf("---------------------------------------\n");
        while (fgets(line, sizeof(line), fp))
        {
                int id;
                char name[50];
                char author[50];
                float price;
                int quantity;
                sscanf(line, "%d,%49[^,],%49[^,],%f,%d", &id, name, author, &price, &quantity);
                printf("%d | %s | %s | %.2f | %d\n", id, name, author, price, quantity);
        }
        fclose(fp);
}