#include <stdio.h>
#include "adminBook.h"  
#include "book_common.h"
void adminPage() {
    int choice;
 do {
        printf("\n===== ADMIN PANEL =====\n");
        printf("1. Add Book\n");
        printf("2. Edit Book\n");
        printf("3. Delete Book\n");
        printf("4. Show Book List\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
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
                printf("Exiting admin panel...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 5);
}
