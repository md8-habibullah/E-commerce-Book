#include <stdio.h>
#include <string.h>
// #include "total.h"

int next_id();
void register_user();

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
    return count;
}

int main () {
    register_user();
   
}

void register_user(){
    FILE *fp;
    int id = next_id();
    char username[50], password[50], email[100];

    printf("===== USER REGISTRATION =====\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter email: ");
    scanf("%s", email);

    printf("Enter password: ");
    scanf("%s", password);
    

    fp = fopen("users_database.txt", "a");
    fprintf(fp, "%d,%s,%s,%s\n", id, username, password, email);
    fclose(fp);
    printf("Registration successful! Your user ID is %d \n", id);
}

