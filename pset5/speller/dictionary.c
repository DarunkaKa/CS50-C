// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (LENGTH + 1) *'z';

// Hash table
int maxwords = 0;
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int numb = hash(word);
    node *cur = table[numb];
    while (cur != NULL)
    {
        if (strcasecmp(cur->word, word) == 0)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int math = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        math += tolower(word[i]);
    }
    return (math % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //відкриття словника
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    //читання одного слова у файл
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        //створення нової ноди
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
        {
            return false;
        }
        
        strcpy(newnode->word, word);
        newnode->next = NULL;
        
        //число для хешування
        int numb = hash(word);
        if (table[numb] == NULL)
        {
            table[numb] = newnode;
        }
        
        else 
        {
            newnode->next = table[numb];
            table[numb] = newnode;
        }
        maxwords++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return maxwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cur = head;
        node *timenode = head;
    
        while (cur != NULL)
        {
            cur = cur->next;
            free(timenode);
            timenode = cur;
        }
    }
    return true;
}
