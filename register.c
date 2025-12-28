#include <stdio.h>
#include <string.h>
#include "total.h"

int next_id()
{
    FILE *fp = fopen("users_database.txt", "r");
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
    // Adding 1 because if there are 0 lines, the first user is ID 1
    return count + 1; 
}

void register_user()
{
    FILE *fp;
    int id = next_id();
    char username[50], password[50], email[100];

    // --- BEAUTIFIED DESIGN START ---
    printf("\n\t\t----------------------------\n");
    printf("\t\t USER REGISTRATION PORTAL \n");
    printf("\t\t----------------------------\n");
    
    printf("\t\t%-15s: ", "Username");
    scanf("%s", username);
    
    printf("\t\t%-15s: ", "Email Address");
    scanf("%s", email);

    printf("\t\t%-15s: ", "Password");
    scanf("%s", password);
    // --- BEAUTIFIED DESIGN END ---

    fp = fopen("users_database.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%d,%s,%s,%s\n", id, username, email, password);
        fclose(fp);
        
        printf("\t\t----------------------------\n");
        printf("\t\t[SUCCESS] Registered!\n");
        printf("\t\tYour User ID is: %d\n", id);
        printf("\t\t----------------------------\n");
    } else {
        printf("\t\t[ERROR] Could not open database!\n");
    }
}