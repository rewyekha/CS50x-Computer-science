#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Make sure program was run with exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check if every character in argv[1] is a digit
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from a string to an integer
    int k = atoi(argv[1]);

    // Get plaintext from user
    string plaintext = get_string("plaintext: ");

    // Print ciphertext
    printf("ciphertext: ");

    // Encrypt the plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        printf("%c", rotate(plaintext[i], k));
    }
    printf("\n");

    return 0;
}

// Function to check if a string contains only digits
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// Function to rotate a character by n positions
char rotate(char c, int n)
{
    if (isupper(c))
    {
        return (char) ((((c - 'A') + n) % 26 + 26) % 26 + 'A');
    }
    else if (islower(c))
    {
        return (char) ((((c - 'a') + n) % 26 + 26) % 26 + 'a');
    }
    else
    {
        return c;
    }
}

// This is Reyas khan & Thanks - CS50
