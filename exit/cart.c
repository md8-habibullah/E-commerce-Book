#include <stdio.h>
#include "cart.h"
#include "usershowbook.h"

int cart[20], cartCount = 0;

void addToCart(int bookId) {
    cart[cartCount++] = bookId;
    printf("Added to cart!\n");
}

void viewCart() {
    printf("\n--- CART ---\n");
    for(int i = 0; i < cartCount; i++)
        showBookDetails(cart[i]);
}
