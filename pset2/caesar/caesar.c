#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool check_valid_key(string t);

int main(int argc, string argv[])
{
     
    if (argc != 2 || !check_valid_key(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    
    for (int f = 0; f < strlen(plaintext); f++)
    {
        if (isalpha(plaintext[f]) && isupper(plaintext[f]))
        {
            printf("%c", ((((plaintext[f]) - 65) + key) % 26) + 65);
        }
        else if (isalpha(plaintext[f]) && islower(plaintext[f]))
        {
            printf("%c", ((((plaintext[f]) - 97) + key) % 26) + 97);
        }
        else
        {
            printf("%c", plaintext[f]);
        }
              
    } 
    printf("\n");
    return 0;
           
}           
bool check_valid_key(string t) 
{
    for (int i = 0; i < strlen(t); i++)
    {
        if (!isdigit(t[i]))
        {
            return false;
        }
          
    }
    return true;
}