#include <stdio.h>
#include <string.h>
#include "total.h"
int login_admin()
{
    FILE *fp;
    char username[50], password[50], line[256];
    int attempts = 3;

    printf("===== ADMIN LOGIN =====\n");
    printf("Enter admin username: ");
    scanf("%s", username);

    fp = fopen("admin_database.txt", "r");
    if (fp == NULL)
    {
        printf("No admins registered yet!\n");
        return 0;
    }
    while (attempts > 0)
    {
        printf("Enter admin password: ");
        scanf("%s", password);

        rewind(fp);

        while (fgets(line, sizeof(line), fp))
        {
            int id;
            char u[50], p[100];

            sscanf(line, "%d,%49[^,],%99[^\n]",
                   &id, u, p);

            if (strcmp(username, u) == 0 &&
                strcmp(password, p) == 0)
            {
                printf("Admin login successful! Welcome %s\n", u);
                fclose(fp);

                adminPage();

                return 1;
            }
        }
        attempts--;
        printf("Wrong password! Attempts left: %d\n", attempts);
    }

    fclose(fp);
    printf("Invalid admin username or password\n");
    return 0;
}
// int main()
// {
//     login_admin();
// }