#include <cs50.h> // include libraries - CS50
#include <stdio.h>

int main(void)
{
    string name = get_string("What is your name?\n"); // get user input
    printf("Hello, %s\n", name);                      // print hello, user input
}
