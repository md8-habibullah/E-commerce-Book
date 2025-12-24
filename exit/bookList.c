#include <stdio.h>
#include <string.h>
#include "adminBook.h"

void addBook() {
    Book b;
    FILE *fp = fopen("books.dat", "ab");
    if(!fp) {
        printf("File error!\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    b.id = (ftell(fp) / sizeof(Book)) + 1;

    printf("Enter Title: ");
    scanf(" %[^\n]", b.title);

    printf("Enter Author: ");
    scanf(" %[^\n]", b.author);

    printf("Enter Price: ");
    scanf("%f", &b.price);

    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    fwrite(&b, sizeof(Book), 1, fp);
    fclose(fp);

    printf("Book added successfully!\n");
}

void editBook() {
    int id;
    printf("Enter Book ID to edit: ");
    scanf("%d", &id);

    FILE *fp = fopen("books.dat", "rb+");
    if(!fp) {
        printf("File error!\n");
        return;
    }

    Book b;
    int found = 0;

    while(fread(&b, sizeof(Book), 1, fp)) {
        if(b.id == id) {
            printf("New Title: ");
            scanf(" %[^\n]", b.title);

            printf("New Author: ");
            scanf(" %[^\n]", b.author);

            printf("New Price: ");
            scanf("%f", &b.price);

            printf("New Quantity: ");
            scanf("%d", &b.quantity);

            fseek(fp, -sizeof(Book), SEEK_CUR);
            fwrite(&b, sizeof(Book), 1, fp);

            found = 1;
            printf("Book updated!\n");
            break;
        }
    }

    if(!found)
        printf("Book not found!\n");

    fclose(fp);
}

void deleteBook() {
    int id;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen("books.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if(!fp || !temp) {
        printf("File error!\n");
        return;
    }

    Book b;
    int found = 0;

    while(fread(&b, sizeof(Book), 1, fp)) {
        if(b.id != id) {
            fwrite(&b, sizeof(Book), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if(found) {
        remove("books.dat");
        rename("temp.dat", "books.dat");
        printf("Book deleted!\n");
    } else {
        remove("temp.dat");
        printf("Book not found!\n");
    }
}

void showBookList() {
    FILE *fp = fopen("books.dat", "rb");
    if(!fp) {
        printf("No books available!\n");
        return;
    }

    Book b;
    printf("\n--- BOOK LIST ---\n");

    while(fread(&b, sizeof(Book), 1, fp)) {
        printf("%d. %s by %s | %.2f | Qty: %d\n",
               b.id, b.title, b.author, b.price, b.quantity);
    }

    fclose(fp);
}
