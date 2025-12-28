#ifndef TOTAL_H
#define TOTAL_H

void adminPage();
void userPage(char *loggedInUser); // Updated
void addBook();
void editBook();
void deleteBook();
void showBookList();
void register_user();
int login_user();
void showBookDetails(int targetId, char *username); // Updated to accept username
int login_admin();

// Updated to match order.c definition
void placeOrder(char *username, int bookId, char *bookName, float price);
void forget_pass();

#endif