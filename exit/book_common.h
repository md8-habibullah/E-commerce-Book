#ifndef BOOK_COMMON_H
#define BOOK_COMMON_H

typedef struct {
    int id;
    char title[50];
    char author[50];
    float price;
    int quantity;
} Book;

#endif 
