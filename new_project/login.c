#include <stdio.h>
#include <string.h>
#include "total.h"
    
int login_user()
{
    FILE *fp;
    char username[50], password[50], line[256];
    int attempts = 3;

    printf("===== USER LOGIN =====\n");
    printf("Enter username: ");
    scanf("%s", username);

    fp = fopen("users_database.txt", "r");
    if (fp == NULL)
    {
        printf("No users registered yet!\n");
        return 0;
    }
    while (attempts > 0)
    {
        printf("Enter password: ");
        scanf("%s", password);

        rewind(fp);

        while (fgets(line, sizeof(line), fp))
        {
            int id;
            char u[50], e[100], p[50];

            sscanf(line, "%d,%49[^,],%99[^,],%49[^\n]",
                   &id, u, e, p);

            if (strcmp(username, u) == 0 &&
                strcmp(password, p) == 0)
            {
                printf("Login successful! Welcome %s\n", u);
                fclose(fp);

                userPage();

                return 1;
            }
        }
        attempts--;
        printf("Wrong password! Attempts left: %d\n", attempts);
    }

    fclose(fp);
    printf("Invalid username or password\n");
    return 0;
}

// int main()
// {
//     login_user();
// }