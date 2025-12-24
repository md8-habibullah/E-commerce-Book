#include <stdio.h>
#include <string.h>

// actually we want add if forgot password , then read "user_database.txt" and read that user based on username 
// user_database.txt
// id,username,email,password
// 1,test,test@email,111
// 2,aaa,aaa@mail,1234
// 3,bbb,123,111
// 4,ttt,ttt@mail,234
// 6,lolita,lolita@mail,134
// 7,zihad,zihad@mail,1234
// 8,rrr,rrrr,rrr



void forget_pass()
{
    char username[50];
    char email[50];
    char file_username[50];
    char file_email[50];
    char file_password[50];
    int found = 0;

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your email: ");
    scanf("%s", email);

    FILE *file = fopen("users_database.txt", "r");
    if (file == NULL)
    {
        printf("Could not open user database.\n");
        return;
    }

    // Skip the header line
    char header[100];
    fgets(header, sizeof(header), file);

    while (fscanf(file, "%*d,%49[^,],%49[^,],%49s", file_username, file_email, file_password) != EOF)
    // EOL = End Of Line..
    // EOF = End Of File
    {
        if (strcmp(username, file_username) == 0 && strcmp(email, file_email) == 0)
        {
            printf("Your password is: %s\n", file_password);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("No matching user found.\n");
    }

    fclose(file);
}


