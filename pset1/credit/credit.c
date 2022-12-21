#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    long card = get_long("Number: ");
    long proto1 = card;
    int i = 0;
    //длина карточки
    while (proto1 > 0)
    {
        proto1 = proto1 / 10;
        i++;
    }
    //по длині карточки визначаємо чи дійсна картка
    if (i != 13 && i != 15 && i != 16)
    {
        printf("INVALID\n");
        return 0;
    }
    int sum1 = 0;
    int sum2 = 0;
    long proto2 = card;
    int mod1 = 0;
    int mod2 = 0;
    int d1;
    int d2;
    do
    {
        //беремо останню цифру і додаємо до sum1 - сума неперемножених на 2
        mod1 = proto2 % 10;
        proto2 = proto2 / 10;
        sum1 = sum1 + mod1;
        
        //беремо передостанню цифру
        mod2 = proto2 % 10;
        proto2 = proto2 / 10;
        
        //умножить на 2 передостанню цифру і додати до sum2
        mod2 = mod2 * 2;
        d1 = mod2 % 10;
        d2 = mod2 / 10;
        sum2 = sum2 + d1 + d2;
    }
    while (proto2 > 0);
    int sum = sum1 + sum2;
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    long proto3 = card;
    do
    {
        proto3 = proto3 / 10;
    }
    while (proto3 > 100);
    if ((proto3 / 10 == 5) && (proto3 % 10 == 1 || proto3 % 10 == 2 || proto3 % 10 == 3 || proto3 % 10 == 4 || proto3 % 10 == 5))
    {
        printf("MASTERCARD\n");
    }
    else if ((proto3 / 10 == 3) && (proto3 % 10 == 4 || proto3 % 10 == 7))
    {
        printf("AMEX\n");
    }
    else if (proto3 / 10 == 4)
    {
        printf("VISA\n"); 
    }
    else
    {
        printf("INVALID\n");
    }
}