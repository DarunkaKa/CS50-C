#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) 
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            for (int i = 0; i < strlen(argv[1]); i++)
            {
                if (!isalpha(argv[1][i]))
                {
                    printf("Key must contain 26 characters.\n");
                    return 1;
                }
                for (int j = i + 1; j < strlen(argv[1]); j++)
                {
                    if (toupper(argv[1][j]) == toupper(argv[1][i]))
                    {
                        printf("Key must not contain repeated alphabets.\n");
                        return 1;
                    }
                }
            }
            
            string abetka = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            string plaintext = get_string("plaintext: ");
            printf("ciphertext: ");
            
            for (int k = 0; k < strlen(plaintext); k++)
            {
                if (isalpha(plaintext[k]) && isupper(plaintext[k]))
                {
                    for (int d = 0; d < strlen(abetka); d++)
                    {
                        if (plaintext[k] == toupper(abetka[d]))
                        {
                            printf("%c", toupper(argv[1][d]));
                        }
                    }
                }
                else if (isalpha(plaintext[k]) && islower(plaintext[k]))
                {
                    for (int d = 0; d < strlen(abetka); d++)
                    {
                        if (plaintext[k] == tolower(abetka[d]))
                        {
                            printf("%c", tolower(argv[1][d]));
                        }
                    }
                }
                else
                {
                    printf("%c", plaintext[k]);
                }
            }
        }
    }
    printf("\n");
    return 0;
}
