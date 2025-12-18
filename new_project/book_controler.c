#include <stdio.h>
#include <string.h>
#include "total.h"

int next_id()
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
        int id = next_id();
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

void editBook()
{
        FILE *fp, *temp;
        int bookId, found = 0;

        showBookList();

        printf("\nEnter the Book ID to edit: ");
        scanf("%d", &bookId);

        fp = fopen("books.txt", "r");
        if (fp == NULL)
        {
                printf("No books available.\n");
                return;
        }

        temp = fopen("temp.txt", "w");
        if (temp == NULL)
        {
                printf("Error creating temp file.\n");
                fclose(fp);
                return;
        }

        char line[200];

        while (fgets(line, sizeof(line), fp))
        {
                int id;
                char name[50], author[50];
                float price;
                int quantity;

                sscanf(line, "%d,%49[^,],%49[^,],%f,%d",
                       &id, name, author, &price, &quantity);

                if (id == bookId)
                {
                        found = 1;

                        printf("\nEditing Book ID %d\n", id);

                        printf("New book name: ");
                        scanf(" %[^\n]", name);

                        printf("New author name: ");
                        scanf(" %[^\n]", author);

                        printf("New price: ");
                        scanf("%f", &price);

                        printf("New quantity: ");
                        scanf("%d", &quantity);

                        fprintf(temp, "%d,%s,%s,%.2f,%d\n",
                                id, name, author, price, quantity);
                }
                else
                {
                        fprintf(temp, "%s", line);
                }
        }

        fclose(fp);
        fclose(temp);

        remove("books.txt");
        rename("temp.txt", "books.txt");

        if (found)
                printf("\nBook updated successfully!\n");
        else
                printf("\nBook ID not found.\n");
}

// void deleteBook() {

// }
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