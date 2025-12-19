#include <stdio.h>
#include <string.h>
#include "total.h"

int main () {
    char response [10];
    printf("Do you have an account? Please Write yes or no\n");
    scanf("%s",response);
    if (strcmp(response, "yes") == 0) {
        login_user();
    } else {
        register_user();
    }

    
}
