#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function prototypes
bool is_valid_key(string key);
void substitute_cipher(string key, string plaintext);

int main(int argc, string argv[])
{
    // Check if exactly one command-line argument is given
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Validate the key
    if (!is_valid_key(argv[1]))
    {
        printf("Key must contain 26 alphabetic characters and each letter exactly once.\n");
        return 1;
    }

    // Prompt for plaintext
    string plaintext = get_string("plaintext: ");

    // Encrypt the plaintext using the provided key
    substitute_cipher(argv[1], plaintext);

    return 0;
}

// Function to validate the key
bool is_valid_key(string key)
{
    // Check length of key
    if (strlen(key) != 26)
    {
        return false;
    }

    // Check for non-alphabetic characters and duplicate letters
    bool used[26] = {false}; // Array to track used letters
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        int index = tolower(key[i]) - 'a';
        if (index < 0 || index >= 26 || used[index])
        {
            return false;
        }
        used[index] = true;
    }
    return true;
}

// Function to perform substitution cipher encryption
void substitute_cipher(string key, string plaintext)
{
    // Output the ciphertext
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            // Determine if the letter is uppercase or lowercase
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int index = tolower(plaintext[i]) - 'a';
            char cipher_char = isupper(plaintext[i]) ? toupper(key[index]) : tolower(key[index]);
            printf("%c", cipher_char);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
