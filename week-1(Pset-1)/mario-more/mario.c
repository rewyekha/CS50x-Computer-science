#include <cs50.h>
#include <stdio.h>

int get_positive_int(string prompt);

int main(void)
{
    int number = get_positive_int("Height: ");

    for (int height = 0; height < number; height++) // height and number of pyramid lines
    {
        for (int spaces = number - height - 1; spaces > 0; spaces--) // print spaces
        {
            printf(" ");
        }
        for (int blocks = 0; blocks <= height; blocks++) // left pyramid
        {
            printf("#");
        }
        printf("  ");
        for (int blocks = 0; blocks <= height; blocks++) // right pyramid
        {
            printf("#");
        }
        printf("\n");
    }
}

int get_positive_int(string prompt) // def func.
{
    int number;
    do
    {
        number = get_int("%s", prompt);
    }
    while (number < 1 || number > 8); // range between 1 to 8
    return number;
}
