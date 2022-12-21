#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    for (int line = 0; line < height; line++)
    {
        for (int space = 1; space < height - line; space++)
        {
            printf(" ");
        }
        for (int thorp = 0; thorp <= line; thorp++)
        {
            printf("#");
        }
        printf("  ");
        
        for (int thorp = 0; thorp <= line; thorp++)
        {
            printf("#");
        }
        printf("\n");
    }
}