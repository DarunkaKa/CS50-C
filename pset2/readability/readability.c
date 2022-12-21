#include <math.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");
    
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }
    }
   
    
    int  words = 1;
    for (int k = 0; k < strlen(text); k++)
    {
        if (text[k] == ' ')
        {
            words++;
        }
    }
    
    int sentences = 0;
    for (int p = 0; p < strlen(text); p++)
    {
        if (text[p] == '!' || text[p] == '?' || text[p] == '.')
        {
            sentences++;
        }
    }
    
    float L = (letters / (float) words) * 100;
    float S = (sentences / (float) words) * 100;
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}